///////////////////////////////////////////////////////////////////////////////
//                                                                             
//  Copyright (C) 2008-2012  Artyom Beilis (Tonkikh) <artyomtnk@yahoo.com>     
//                                                                             
//  See accompanying file COPYING.TXT file for licensing details.
//
///////////////////////////////////////////////////////////////////////////////
#define CPPCMS_SOURCE
#include <cppcms/rpc_json.h> 
#include <cppcms/http_context.h>
#include <cppcms/http_request.h>
#include <cppcms/http_response.h>
#include <cppcms/http_content_type.h>

#include <sstream>
#include <booster/nowide/fstream.h>
#include <booster/log.h>
#include <streambuf>

namespace cppcms {
namespace rpc {

    call_error::call_error(std::string const &m) : cppcms_error(m) {} 
	struct json_call::_data {};

	json_call::json_call(http::context &c) 
	{
		http::content_type ct = c.request().content_type_parsed();
		std::string type = ct.type();
		std::string subtype = ct.subtype();
		if(type != "application" || (subtype!="json" && subtype!="jsonrequest" && subtype!="json-rpc"))
			throw call_error("Invalid content type"); 
		if(c.request().request_method()!="POST")
			throw call_error("Invalid request method"); 
		std::pair<void *,size_t> post_data = c.request().raw_post_data();
		std::istringstream ss(std::string(reinterpret_cast<char const *>(post_data.first),post_data.second));
		json::value request;
		if(!request.load(ss,true))
			throw call_error("Invalid JSON");
		if(	request.type("method")!=json::is_string 
			|| request.type("params")!=json::is_array
			|| request.type("id")==json::is_undefined)
		{
			throw call_error("Invalid JSON-RPC");
		}
		if(request.type("id")==json::is_null) {
			notification_ = true;
		}
		else {
			notification_ = false;
			id_.swap(request["id"]);
		}
		params_.swap(request["params"].array());
		method_ = request.get<std::string>("method");
	}

	json_call::~json_call()
	{
	}
	
	void json_call::return_result(http::context &c,json::value const &result)
	{
		c.response().set_content_header("application/json");
		c.response().out() <<
			"{\"id\":"<<id_<<",\"error\":null,\"result\":"<<result<<"}";
	}
	void json_call::return_error(http::context &c,json::value const &error)
	{
		c.response().set_content_header("application/json");
		c.response().out() <<
			"{\"id\":"<<id_<<",\"error\":"<<error<<",\"result\":null}";
	}

	http::context &json_call::context()
	{
		if(!context_.get())
			throw cppcms_error("No context assigned to rpc::json_call");
		return *context_;
	}
	void json_call::return_result(json::value const &v)
	{
		check_not_notification();
		return_result(context(),v);
		context().response().finalize();
		context().async_complete_response();
	}
	void json_call::return_error(json::value const &e)
	{
		check_not_notification();
		return_error(context(),e);
		context().response().finalize();
		context().async_complete_response();
	}

	void json_call::check_not_notification()
	{
		if(notification())
			throw call_error("Notification method should not return response");
	}

	std::string json_call::method()
	{
		return method_;
	}
	bool json_call::notification()
	{
		return notification_;
	}
	json::array const &json_call::params()
	{
		return params_;
	}

	void json_call::attach_context(booster::shared_ptr<http::context> c)
	{
		context_ = c;
	}
	
	struct json_rpc_server::_data{};

	json_rpc_server::json_rpc_server(cppcms::service &srv) :
		application(srv)
	{	
	}
	json_rpc_server::~json_rpc_server()
	{
	}
	void json_rpc_server::smd(json::value const &v)
	{
		std::ostringstream ss;
		ss<<v;
		smd_=ss.str();
	}
	void json_rpc_server::smd_raw(std::string const &v)
	{
		smd_=v;
	}
	void json_rpc_server::smd_from_file(std::string const &file)
	{
		booster::nowide::ifstream smd(file.c_str());
		if(!smd)
			throw cppcms_error("Failed to open:" + file);
		smd_.reserve(1024);
		smd_.assign(	std::istreambuf_iterator<char>(smd),
				std::istreambuf_iterator<char>());
	}

	void json_rpc_server::main(std::string /*unused*/)
	{
		if(!smd_.empty() && request().request_method()=="GET") {

			response().set_content_header("application/json");
			response().out() << smd_;

			if(is_asynchronous())
				release_context()->async_complete_response();
			return;
		}

		try {
			current_call_.reset(new json_call(context()));
			BOOSTER_DEBUG("cppcms") << "JSON-RPC Method call:" << method();
			methods_map_type::iterator p=methods_.find(method());
			if(p==methods_.end()) {
				if(!notification())
					return_error("Method not found");
				return;
			}
			if(p->second.role == notification_role && !notification()) {
				return_error("The request should be notification");
				return;
			}
			if(p->second.role == method_role && notification()) {
				// No way to respond according to protocol
				return;
			}
			try {
				p->second.method(params());
			}
			catch(json::bad_value_cast const &e) {
				if(current_call_.get() && !notification())
					return_error("Invalid parameters");
				return;
			}
			catch(call_error const &e) {
				if(current_call_.get() && !notification())
					return_error(e.what());
				return;
			}
			catch(std::exception const &e) {
				if(current_call_.get() && !notification())
					return_error("Internal Service Error");
				return;
			}
		}
		catch(call_error const &e)
		{
			response().set_content_header("text/plain");
			response().out()<< e.what() << std::endl;
		}
	}

	void json_rpc_server::bind(std::string const &name,method_type const &method,role_type role)
	{
		method_data data;
		data.method=method;
		data.role=role;
		methods_[name]=data;
	}
	bool json_rpc_server::notification()
	{
		check_call();
		return current_call_->notification();
	}
	json::array const &json_rpc_server::params()
	{
		check_call();
		return current_call_->params();
	}
	void json_rpc_server::return_result(json::value const &r)
	{
		check_call();
		current_call_->return_result(context(),r);
	}
	void json_rpc_server::return_error(json::value const &e)
	{
		check_call();
		current_call_->return_error(context(),e);
	}
	booster::shared_ptr<json_call> json_rpc_server::release_call()
	{
		check_call();
		current_call_->attach_context(release_context());
		booster::shared_ptr<json_call> call = current_call_;
		current_call_.reset();
		return call;
	}
	std::string json_rpc_server::method()
	{
		check_call();
		return current_call_->method();
	}
	void json_rpc_server::check_call()
	{
		if(current_call_.get()==0)
			throw cppcms_error("JSON-RPC Request is not assigned to class");
	}


} // rpc
} // cppcms
