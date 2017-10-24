///////////////////////////////////////////////////////////////////////////////
//                                                                             
//  Copyright (C) 2008-2012  Artyom Beilis (Tonkikh) <artyomtnk@yahoo.com>     
//                                                                             
//  See accompanying file COPYING.TXT file for licensing details.
//
///////////////////////////////////////////////////////////////////////////////
#ifndef CPPCMS_RPC_JSON_OBJECT_H
#define CPPCMS_RPC_JSON_OBJECT_H

#include <cppcms/application.h>
#include <booster/function.h>
#include <cppcms/json.h>
#include <cppcms/cppcms_error.h>

namespace cppcms {
///
/// \brief This namespace holds API for implementing various RPC APIs, like JsonRPC
///
namespace rpc {

	///
	/// \brief The error thrown in case of bad call - parameters mismatch or 
	/// invalid request.
	///
	/// User should may throw it case of a error as invalid request inside the
	/// method. However return_error() is preferred.
	///
	class CPPCMS_API call_error : public cppcms_error {
	public:	
		///
		/// Define error message
		///
		call_error(std::string const &message);
	};

	class json_rpc_server;

	///
	/// \brief This class represents single call of json-rpc method.
	/// 
	/// It is used
	/// for handling asynchronous responses only. Similar API is provided
	/// in json_rpc_server class for synchronous methods.
	///
	class CPPCMS_API json_call : public booster::noncopyable {
	public:

		///
		/// Destructor. Automatically deletes appropriate context as once it given to user it owns it.
		///
		~json_call();

		///
		/// Get the name of method that was called
		///
		std::string method();

		///
		/// Check if method call is notification only. You should not return a value.
		///
		/// Note: if you do not add restriction when binding json-rpc method on the role of the call
		/// you should always check this value. Otherwise trying to call return_result or return_error
		/// would throw.
		///
		bool notification();

		///
		/// Get call parameters as json::array (vector of json::value)
		///
		json::array const &params();

		///
		/// Get context associated with the call. This you may wait on events like async_on_peer_reset
		/// of http::context via this member.
		///
		http::context &context();

		///
		/// Complete method response with a result. Throws call_error if the method was called as notification
		///
		void return_result(json::value const &);
		///
		/// Complete method response with a error. Throws call_error if the method was called as notification
		///
		void return_error(json::value const &);
	
	private:


		json_call(http::context &context);
		friend class json_rpc_server;
		void return_result(http::context &,json::value const &);
		void return_error(http::context &,json::value const &);
		void attach_context(booster::shared_ptr<http::context> context);

		void check_not_notification();
		booster::shared_ptr<http::context> context_;
		json::value  id_;
		json::array params_;
		std::string method_;
		bool notification_;

		struct _data;
		booster::hold_ptr<_data> d;
	};

	///
	/// \brief JSON-RPC service application.
	///
	/// User is expected to derive his own objects from this class in order to implement Json-RPC calls
	/// similarly to how cppcms::application is used.
	///
	class CPPCMS_API json_rpc_server : public application {
	public:
		///
		/// The role of the method - receives notification, returns result or any one of them
		///
		typedef enum {
			any_role,		///< Method may receive notification and return result
			method_role,		///< Method can't be used with notification calls
			notification_role	///< Method should be used with notification calls only
		} role_type;

		///
		/// Generic type of JSON-RPC method
		///
		typedef booster::function<void(json::array const &)> method_type;

		///
		/// Bind method JSON-RPC method with name \a name
		///
		void bind(std::string const &name,method_type const &,role_type type = any_role);

		///
		/// Specify service SMD
		///
		void smd(json::value const &);

		///
		/// Specify service SMD as raw text rather then JSON value
		///
		void smd_raw(std::string const &);
		///
		/// Take service SMD as raw text from file
		///
		void smd_from_file(std::string const &);

		///
		/// Main function that dispatches JSON-RPC service calls
		///
		virtual void main(std::string);

		///
		/// Release json_call for asynchronous responses. Calls release_context() and
		/// assignes it to json_call object.
		///
		booster::shared_ptr<json_call> release_call();
		
		json_rpc_server(cppcms::service &srv);
		~json_rpc_server();

		
		///
		/// Get the name of method that was called
		///
		std::string method();
		///
		/// Check if method call is notification only. You should not return a value.
		///
		/// Note: if you do not add restriction when binding json-rpc method on the role of the call
		/// you should always check this value. Otherwise trying to call return_result or return_error
		/// would throw.
		///
		bool notification();
		///
		/// Get call parameters as json::array (vector of json::value)
		///
		json::array const &params();
		///
		/// Complete method response with a result. Throws call_error if the method was called as notification
		///
		void return_result(json::value const &);
		///
		/// Complete method response with a error. Throws call_error if the method was called as notification
		///
		void return_error(json::value const &);
	private:
		void check_call();
		struct method_data {
			method_type method;
			role_type role;
		};
		typedef std::map<std::string,method_data> methods_map_type;
		methods_map_type methods_;
		booster::shared_ptr<json_call> current_call_;

		std::string smd_;
		
		struct _data;
		booster::hold_ptr<_data> d;
	};

	/// \cond INTERNAL

	namespace details {

		template<typename T> struct fw_ret { typedef T type; };
		template<typename T> struct fw_ret<T const &> { typedef T type; };
		template<typename T> struct fw_ret<T const> { typedef T type; };
		
		template<> struct fw_ret<json::value>  { typedef json::value const &type; };
		template<> struct fw_ret<json::object> { typedef json::object const &type; };
		template<> struct fw_ret<json::array>  { typedef json::array const &type; };
		template<> struct fw_ret<std::string>  { typedef std::string const &type; };
		
		template<> struct fw_ret<json::value const &>  { typedef json::value const &type; };
		template<> struct fw_ret<json::object const &> { typedef json::object const &type; };
		template<> struct fw_ret<json::array const &>  { typedef json::array const &type; };
		template<> struct fw_ret<std::string const &>  { typedef std::string const &type; };

		template<> struct fw_ret<json::value const>  { typedef json::value const &type; };
		template<> struct fw_ret<json::object const> { typedef json::object const &type; };
		template<> struct fw_ret<json::array const>  { typedef json::array const &type; };
		template<> struct fw_ret<std::string const>  { typedef std::string const &type; };


		template<typename T>
		struct fw_ret_handle {
			static typename fw_ret<T>::type extract(json::value const &v)
			{
				return v.get_value<typename fw_ret<T>::type>();
			}
		};

		template<>
		struct fw_ret_handle<json::value const &>
		{
			static json::value const &extract(json::value const &v)
			{
				return v;
			}
		};

		template<>
		struct fw_ret_handle<json::array const &>
		{
			static json::array const &extract(json::value const &v)
			{
				return v.array();
			}
		};

		template<>
		struct fw_ret_handle<json::object const &>
		{
			static json::object const &extract(json::value const &v)
			{
				return v.object();
			}
		};

		template<>
		struct fw_ret_handle<std::string const &>
		{
			static std::string const &extract(json::value const &v)
			{
				return v.str();
			}
		};


		template <typename T>
		inline typename fw_ret<T>::type forward_value(json::value const &v) 
		{
			typedef typename fw_ret<T>::type return_type;
			return fw_ret_handle<return_type>::extract(v);
		}

	}

	#define CPPCMS_JSON_RPC_BINDER(N)						\
	namespace details {								\
		template<typename Class,typename Ptr CPPCMS_TEMPLATE_PARAMS>		\
		struct binder##N {							\
			Ptr object;							\
			void (Class::*member)(CPPCMS_FUNC_PARAMS);			\
			void operator()(json::array const &a) const			\
			{								\
				if(a.size()!=N) 					\
					throw call_error("Invalid parametres number");	\
				((*object).*member)(CPPCMS_CALL_PARAMS);		\
			}								\
		};									\
	}										\
	template<typename Class,typename Ptr CPPCMS_TEMPLATE_PARAMS>			\
	details::binder##N<Class,Ptr CPPCMS_BINDER_PARAMS> 				\
	json_method(void (Class::*m)(CPPCMS_FUNC_PARAMS),Ptr p)				\
	{ details::binder##N<Class,Ptr CPPCMS_BINDER_PARAMS> tmp={p,m}; return tmp; }	\

	#define CPPCMS_TEMPLATE_PARAMS
	#define CPPCMS_FUNC_PARAMS
	#define CPPCMS_CALL_PARAMS
	#define CPPCMS_BINDER_PARAMS
	CPPCMS_JSON_RPC_BINDER(0)
	#undef CPPCMS_TEMPLATE_PARAMS
	#undef CPPCMS_FUNC_PARAMS
	#undef CPPCMS_CALL_PARAMS
	#undef CPPCMS_BINDER_PARAMS

	#define CPPCMS_TEMPLATE_PARAMS ,typename P1
	#define CPPCMS_FUNC_PARAMS P1
	#define CPPCMS_CALL_PARAMS forward_value<P1>(a[0])
	#define CPPCMS_BINDER_PARAMS ,P1
	CPPCMS_JSON_RPC_BINDER(1)
	#undef CPPCMS_TEMPLATE_PARAMS
	#undef CPPCMS_FUNC_PARAMS
	#undef CPPCMS_CALL_PARAMS
	#undef CPPCMS_BINDER_PARAMS
	
	#define CPPCMS_TEMPLATE_PARAMS ,typename P1,typename P2
	#define CPPCMS_FUNC_PARAMS P1,P2
	#define CPPCMS_CALL_PARAMS forward_value<P1>(a[0]), forward_value<P2>(a[1])
	#define CPPCMS_BINDER_PARAMS ,P1,P2
	CPPCMS_JSON_RPC_BINDER(2)
	#undef CPPCMS_TEMPLATE_PARAMS
	#undef CPPCMS_FUNC_PARAMS
	#undef CPPCMS_CALL_PARAMS
	#undef CPPCMS_BINDER_PARAMS

	#define CPPCMS_TEMPLATE_PARAMS ,typename P1,typename P2,typename P3
	#define CPPCMS_FUNC_PARAMS P1,P2,P3
	#define CPPCMS_CALL_PARAMS forward_value<P1>(a[0]), forward_value<P2>(a[1]), forward_value<P3>(a[2])
	#define CPPCMS_BINDER_PARAMS ,P1,P2,P3
	CPPCMS_JSON_RPC_BINDER(3)
	#undef CPPCMS_TEMPLATE_PARAMS
	#undef CPPCMS_FUNC_PARAMS
	#undef CPPCMS_CALL_PARAMS
	#undef CPPCMS_BINDER_PARAMS

	#define CPPCMS_TEMPLATE_PARAMS ,typename P1,typename P2,typename P3,typename P4
	#define CPPCMS_FUNC_PARAMS P1,P2,P3,P4
	#define CPPCMS_CALL_PARAMS forward_value<P1>(a[0]), forward_value<P2>(a[1]), forward_value<P3>(a[2]), forward_value<P4>(a[3])
	#define CPPCMS_BINDER_PARAMS ,P1,P2,P3,P4
	CPPCMS_JSON_RPC_BINDER(4)
	#undef CPPCMS_TEMPLATE_PARAMS
	#undef CPPCMS_FUNC_PARAMS
	#undef CPPCMS_CALL_PARAMS
	#undef CPPCMS_BINDER_PARAMS

	#undef CPPCMS_JSON_RPC_BINDER

	/// \endcond

} // rpc
} // cppcms



#endif
