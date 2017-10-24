//
//  Copyright (C) 2009-2012 Artyom Beilis (Tonkikh)
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOSTER_SHARED_OBJECT_H
#define BOOSTER_SHARED_OBJECT_H

#include <booster/config.h>
#include <booster/noncopyable.h>
#include <booster/hold_ptr.h>
#include <booster/backtrace.h>
#include <booster/cstdint.h>
#include <string>

namespace booster {
	///
	/// \brief Class that allows loading dynamic libraries: shared objects and dlls.
	///
	class BOOSTER_API shared_object : public booster::noncopyable {
	public:
		static const int load_lazy 	= 1; /// Pass RTLD_LAZY to dlopen
		static const int load_now  	= 2; /// Pass RTLD_NOW to dlopen
		static const int load_global 	= 4; /// Pass RTLD_GLOBAL to dlopen
		static const int load_local	= 8; /// Pass RTLD_LOCAL to dlopen
		///
		/// Create an empty shared object
		///
		shared_object();
		///
		/// If the shared object was open unloads it, If private copy of DLL was made it is removed from
		/// the file system
		///
		~shared_object();
		///
		/// Create shared object and load it, \see open(std::string const&,bool);
		///
		/// \param file_name - the name of the file, UTF-8 encoded under Windows
		/// \params flags - load flags: one of load_lazy, load_now, load_local, load_global - ignored on Windows
		///
		/// \throws booster::system::system_error if it is impossible to load it
		/// \ver{v1_2}
		shared_object(std::string const &file_name,int flags);
		///
		/// Create shared object and load it, \see open(std::string const&,bool);
		///
		/// \param file_name - the name of the file, UTF-8 encoded under Windows
		///
		/// \throws booster::system::system_error if it is impossible to load it
		///
		shared_object(std::string const &file_name);
		///
		/// Check if the shared object was loaded
		///
		bool is_open() const;
		///
		/// Load shared object or dll
		///
		/// \param file_name - the name of the file, UTF-8 encoded under Windows
		/// \return true if the shared object was loaded
		///
		bool open(std::string const &file_name);
		///
		/// Load shared object or dll
		///
		/// \param file_name - the name of the file, UTF-8 encoded under Windows
		/// \param error_message - the error message 
		/// \return true if the shared object was loaded
		///
		bool open(std::string const &file_name,std::string &error_message);
		///
		/// Load shared object or dll
		///
		/// \param file_name - the name of the file, UTF-8 encoded under Windows
		/// \params flags - load flags: one of load_lazy, load_now, load_local, load_global - ignored on Windows
		/// \return true if the shared object was loaded
		///
		/// \ver{v1_2}
		bool open(std::string const &file_name,int flags);
		///
		/// Load shared object or dll
		///
		/// \param file_name - the name of the file, UTF-8 encoded under Windows
		/// \params flags - load flags: one of load_lazy, load_now, load_local, load_global - ignored on Windows
		/// \param error_message - the error message 
		/// \return true if the shared object was loaded
		///
		/// \ver{v1_2}
		bool open(std::string const &file_name,std::string &error_message,int flags);
		///
		///
		/// Unload the shared object
		///
		void close();

		///
		/// Resolve symbol in the shared object dll. If it can't be resolved, NULL is returned
		///
		/// If the shared object was not opened, it would throw booster::runtime_error
		///
		void *resolve_symbol(std::string const &name) const;

		///
		/// Resolve symbol in the shared object dll. If it can't be resolved booster::runtime_error
		/// is thrown
		///
		template<typename T>
		void symbol(T &s,std::string const &name) const
		{
			void *p = resolve_symbol(name);
			if(!p) {
				throw booster::runtime_error("booster::shared_object:failed to resolve symbol:" + name);
			}
			s = reinterpret_cast<T>(reinterpret_cast<size_t>(p));
		}

		///
		/// Format the OS specific name  name of the library according to its name. Uses CMake convensions.
		///
		/// For example library "foo" is converted to the name
		///
		/// - libfoo.so under Linux, FreeBSD, Solaris
		/// - libfoo.dylib under Darwin/Mac OS X
		/// - libfoo.dll under Windows using gcc/mingw
		/// - foo.dll under Windows using MSVC
		/// - cygfoo.dll under Cygwin
		///
		static std::string name(std::string const &module);
		///
		/// Format the OS specific name  name of the library according to its name and its soversion.
		/// Uses CMake convensions.
		///
		/// For example library "foo" and soversion "1" is converted to the name
		///
		/// - libfoo.so.1 under Linux, FreeBSD, Solaris
		/// - libfoo.1.dylib under Darwin/Mac OS X
		/// - libfoo-1.dll under Windows using gcc/mingw
		/// - foo-1.dll under Windows using MSVC
		/// - cygfoo-1.dll under Cygwin
		///
		static std::string name(std::string const &module,std::string const &soversion);
	private:
		struct data;
		hold_ptr<data> d;
	};
}

#endif

