///////////////////////////////////////////////////////////////////////////////
//                                                                             
//  Copyright (C) 2008-2012  Artyom Beilis (Tonkikh) <artyomtnk@yahoo.com>     
//                                                                             
//  See accompanying file COPYING.TXT file for licensing details.
//
///////////////////////////////////////////////////////////////////////////////
#ifndef CPPCMS_SESSION_STORAGE_H
#define CPPCMS_SESSION_STORAGE_H

#include <cppcms/defs.h>
#include <booster/noncopyable.h>
#include <booster/shared_ptr.h>
#include <string>

namespace cppcms {
namespace json {
	class value;
}
namespace sessions {

	///
	/// \brief session_server_storage is an abstract class that allows user to implements
	/// custom session storage device like, database storage device
	///
	/// Note: if the member functions save/load/remove are thread safe -- can be called
	/// from different threads, than you may create a single session and return \a shared_ptr
	/// to a single instance, otherwise you have to create multiple instances of object
	///
	
	class session_storage : public booster::noncopyable
	{
	public:
		///
		/// Save session with end of life time at \a timeout using session id \a sid and content \a in
		///
	
		virtual void save(std::string const &sid,time_t timeout,std::string const &in) = 0;

		///
		/// Load session with \a sid, put its end of life time to \a timeout and return its
		/// value to \a out
		///
		virtual bool load(std::string const &sid,time_t &timeout,std::string &out) = 0;
		
		///
		/// Remove a session with id \a sid  from the storage
		///
		
		virtual void remove(std::string const &sid) = 0;

		///
		/// Return true of the save or load operations can be blocking
		///
		virtual bool is_blocking() = 0;	
	

		///
		/// Destroy an object
		///
		virtual ~session_storage()
		{
		}
	};

	///
	/// \brief The factory is an interface to a factory that creates session_storage objects, it should be thread safe.
	///
	class session_storage_factory {
	public:
		///
		/// Get a pointer to session_storage. Note if the returned pointer is same for different calls
		/// session_storage implementation should be thread safe.
		///
		virtual booster::shared_ptr<session_storage> get() = 0;

		///
		/// Return true if session_storage requires garbage collection - removal of expired session time-to-time
		///
		virtual bool requires_gc() = 0;
		///
		/// Actual garbage collection job (if required). If requires_gc returns true it will be called once-in-a-while to remove
		/// all expired objects from the DB.
		///
		virtual void gc_job() {}
		///
		/// Delete the object, cleanup
		///
		virtual ~session_storage_factory() {}
	};

	extern "C" {
		typedef session_storage_factory *(*cppcms_session_storage_generator_type)(cppcms::json::value const &options);
	}


} // sessions
} // cppcms


#endif
