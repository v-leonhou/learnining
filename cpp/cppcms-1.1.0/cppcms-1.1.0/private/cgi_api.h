///////////////////////////////////////////////////////////////////////////////
//                                                                             
//  Copyright (C) 2008-2012  Artyom Beilis (Tonkikh) <artyomtnk@yahoo.com>     
//                                                                             
//  See accompanying file COPYING.TXT file for licensing details.
//
///////////////////////////////////////////////////////////////////////////////
#ifndef CPPCMS_IMPL_CGI_API_H
#define CPPCMS_IMPL_CGI_API_H

#include <booster/noncopyable.h>
#include <booster/shared_ptr.h>
#include <booster/enable_shared_from_this.h>
#include <booster/aio/buffer.h>
#include <vector>
#include <map>
#include <booster/callback.h>
#include <booster/system_error.h>
#include <cppcms/http_context.h>

#include <cppcms/defs.h>
#include <cppcms/config.h>
#include "string_map.h"

namespace booster {
	namespace aio { 
		class io_service;
		class acceptor;
		class stream_socket;
	}
}


namespace cppcms {
	class service;
	class application;
	namespace http {
		class context;
		class request;
		class response;
	}


namespace impl {
	class multipart_parser;
namespace cgi {

	typedef booster::callback<void(booster::system::error_code const &e)> handler;
	typedef booster::callback<void(booster::system::error_code const &e,size_t)> io_handler;
	typedef booster::callback<void()> callback;
	typedef cppcms::http::context::handler ehandler;

	class connection;
	class acceptor : public booster::noncopyable {
	public:
		virtual void async_accept() = 0;
		virtual booster::aio::acceptor &socket() = 0;
		#ifndef CPPCMS_WIN32
		virtual booster::shared_ptr<cppcms::http::context> accept(int fd) = 0;
		#endif
		virtual void stop() = 0;
		virtual ~acceptor(){}
	};

	class CPPCMS_API connection : 
		public booster::noncopyable,
		public booster::enable_shared_from_this<connection>
	{
	public:
		connection(cppcms::service &srv);
		virtual ~connection();
		cppcms::service &service();
	
		void async_prepare_request(	http::context *context,
						ehandler const &on_post_data_ready);

		void async_write_response(	http::response &response,
						bool complete_response,
						ehandler const &on_response_written);
		
		void aync_wait_for_close_by_peer(callback const &on_eof);

		std::string getenv(std::string const &key)
		{
			return env_.get_safe(key.c_str());
		}
		char const *cgetenv(char const *key)
		{
			return env_.get_safe(key);
		}
		std::string getenv(char const *key) 
		{
			return env_.get_safe(key);
		}
		virtual std::map<std::string,std::string> const &getenv()
		{
			if(map_env_.empty() && env_.begin()!=env_.end()) {
				for(string_map::iterator p=env_.begin();p!=env_.end();++p) {
					map_env_[p->key]=p->value;
				}
			}
			return map_env_;
		}
		bool is_reuseable();
	
		std::string last_error();
	

		/****************************************************************************/

		// These are abstract member function that should be implemented by
		// actual protocol like FCGI, SCGI, HTTP or CGI
	public:
		bool has_pending();
		virtual bool nonblocking_write(booster::aio::const_buffer const &buf,bool eof,booster::system::error_code &e);
		virtual void async_write(booster::aio::const_buffer const &buf,bool eof,handler const &h);
		virtual bool write(booster::aio::const_buffer const &buf,bool eof,booster::system::error_code &e);

		virtual void on_async_write_start() = 0;
		virtual void on_async_write_progress(bool completed) = 0;
		virtual void do_eof() = 0;
		virtual booster::aio::const_buffer format_output(booster::aio::const_buffer const &in,bool completed,booster::system::error_code &e) = 0;
		virtual bool write_to_socket(booster::aio::const_buffer const &in,booster::system::error_code &e);
		virtual booster::aio::io_service &get_io_service() = 0;
	protected:
		void append_pending(booster::aio::const_buffer const &new_data);

		virtual booster::aio::stream_socket &socket() = 0;


		virtual void async_read_headers(handler const &h) = 0;
		virtual bool keep_alive() = 0;

		// Concept implementation headers		
		
		virtual void async_read_some(void *,size_t,io_handler const &h) = 0;
		virtual void on_async_read_complete() {}
		virtual void async_read_eof(callback const &h) = 0;

		/****************************************************************************/

	protected:
		
		string_pool pool_;
		string_map env_;
		std::vector<char> pending_output_;

		booster::shared_ptr<connection> self();
		void async_read(void *,size_t,io_handler const &h);
	private:

		struct reader;
		struct cgi_forwarder;
		struct async_write_binder;
		struct async_write_handler;

		friend struct reader;
		friend struct writer;
		friend struct async_write_binder;
		friend struct async_write_handler;
		friend struct cgi_forwarder;

		void set_error(ehandler const &h,std::string s);
		void on_headers_read(booster::system::error_code const &e,http::context *,ehandler const &h);
		void load_content(http::context *,ehandler const &h);
		void on_some_content_read(booster::system::error_code const &e,size_t n,http::context *,ehandler const &h);
		void handle_eof(callback const &on_eof);
		void handle_http_error(int code,http::context *context,ehandler const &h);
		void handle_http_error_eof(booster::system::error_code const &e,int code,ehandler const &h); 

		cppcms::service *service_;
		std::string async_chunk_;
		std::string error_;
		bool request_in_progress_;

		std::map<std::string,std::string> map_env_;

		booster::intrusive_ptr<async_write_binder> cached_async_write_binder_;

	};


} // cgi
} // impl
} // cppcms

#endif
