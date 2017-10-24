#define BOOSTER_SOURCE
#include <booster/shared_object.h>
#include <booster/backtrace.h>
#include <booster/build_config.h>
#include <booster/nowide/convert.h>

#ifdef BOOSTER_WIN_NATIVE
#include <windows.h>
#include <booster/system_error.h>
#else
#include <dlfcn.h>
#endif
#include <iostream>

namespace booster {
	#ifdef BOOSTER_WIN_NATIVE
	struct shared_object::data {
		HMODULE handle; 
		data() : handle(0) {}
		~data()
		{
			if(handle) 
				FreeLibrary(handle);
		}
	};
	shared_object::shared_object() : d(new data())
	{
	}
	shared_object::~shared_object()
	{
	}
	shared_object::shared_object(std::string const &name,int) : d(new data())
	{
		std::string err;
		if(!open(name,err)) {
			throw booster::runtime_error("booster::shared_object: failed to load shared library " + name +": " + err);
		}
	}
	shared_object::shared_object(std::string const &name) : d(new data())
	{
		std::string err;
		if(!open(name,err)) {
			throw booster::runtime_error("booster::shared_object: failed to load shared library " + name +": " + err);
		}
	}
	void shared_object::close()
	{
		if(d->handle) {
			FreeLibrary(d->handle);
			d->handle = 0;
		}
	}
	bool shared_object::is_open() const
	{
		return d->handle != 0;
	}
	bool shared_object::open(std::string const &file_name,int)
	{
		return open(file_name);
	}
	bool shared_object::open(std::string const &file_name)
	{
		close();
		d->handle = LoadLibraryW(booster::nowide::convert(file_name).c_str());
		return d->handle != 0;		
	}
	bool shared_object::open(std::string const &file_name,std::string &error_message,int)
	{
		return open(file_name,error_message);
	}
	bool shared_object::open(std::string const &file_name,std::string &error_message)
	{
		if(open(file_name)) 
			return true;
		booster::system::error_code e(GetLastError(),booster::system::system_category);
		error_message = e.message();
		return false;
	}
	void *shared_object::resolve_symbol(std::string const &name) const
	{
		if(!is_open())
			throw booster::runtime_error("booster::shared_object::resolve_symbol: the shared_object is not open!");
		return reinterpret_cast<void*>(GetProcAddress(d->handle,name.c_str()));
	}
	#else
	struct shared_object::data {
		void *handle;
		data() : handle(0) {}
		~data()
		{
			if(handle) 
				dlclose(handle);
		}
	};
	shared_object::shared_object() : d(new data())
	{
	}
	shared_object::~shared_object()
	{
	}
	shared_object::shared_object(std::string const &name,int flags) : d(new data())
	{
		std::string err;
		if(!open(name,err,flags)) {
			throw booster::runtime_error("booster::shared_object: failed to load shared library " + name +": " + err);
		}
	}
	shared_object::shared_object(std::string const &name) : d(new data())
	{
		std::string err;
		if(!open(name,err)) {
			throw booster::runtime_error("booster::shared_object: failed to load shared library " + name +": " + err);
		}
	}
	void shared_object::close()
	{
		if(d->handle) {
			dlclose(d->handle);
			d->handle = 0;
		}
	}
	bool shared_object::is_open() const
	{
		return d->handle != 0;
	}
	bool shared_object::open(std::string const &file_name)
	{
		return open(file_name,load_lazy);
	}
	bool shared_object::open(std::string const &file_name,int flags)
	{
		std::string msg;
		return open(file_name,msg,flags);
	}
	bool shared_object::open(std::string const &file_name,std::string &error_message)
	{
		return open(file_name,error_message,load_lazy);
	}
	bool shared_object::open(std::string const &file_name,std::string &error_message,int flags)
	{
		close();
		int dlflags = 0;
		if(flags & load_lazy)
			dlflags |= RTLD_LAZY;
		if(flags & load_now)
			dlflags |= RTLD_NOW;
		if(flags & load_global)
			dlflags |= RTLD_GLOBAL;
		if(flags & load_local)
			dlflags |= RTLD_LOCAL;
		d->handle = dlopen(file_name.c_str(),dlflags);
		if(!d->handle) {
			error_message = dlerror();
			return false;
		}
		return true;
	}
	void *shared_object::resolve_symbol(std::string const &name) const
	{
		if(!is_open())
			throw booster::runtime_error("booster::shared_object::resolve_symbol: the shared_object is not open!");
		return dlsym(d->handle,name.c_str());
	}
	#endif

	#ifndef BOOSTER_LIBRARY_PREFIX
	#define BOOSTER_LIBRARY_PREFIX ""
	#endif

	std::string shared_object::name(std::string const &module)
	{
		return BOOSTER_LIBRARY_PREFIX + module + BOOSTER_LIBRARY_SUFFIX;
	}
	std::string shared_object::name(std::string const &module,std::string const &soversion)
	{

		#if defined __APPLE__
		return BOOSTER_LIBRARY_PREFIX + module + "." + soversion + BOOSTER_LIBRARY_SUFFIX;
		#elif defined BOOSTER_WIN32
		return BOOSTER_LIBRARY_PREFIX + module + "-" + soversion + BOOSTER_LIBRARY_SUFFIX;
		#else
		return BOOSTER_LIBRARY_PREFIX + module + BOOSTER_LIBRARY_SUFFIX + "." + soversion;
		#endif
	}
} // booster

