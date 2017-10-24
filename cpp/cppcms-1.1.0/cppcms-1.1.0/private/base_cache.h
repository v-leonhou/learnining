///////////////////////////////////////////////////////////////////////////////
//                                                                             
//  Copyright (C) 2008-2012  Artyom Beilis (Tonkikh) <artyomtnk@yahoo.com>     
//                                                                             
//  See accompanying file COPYING.TXT file for licensing details.
//
///////////////////////////////////////////////////////////////////////////////
#ifndef BASE_CACHE_H
#define BASE_CACHE_H

#include <string>
#include <set>
#include <cppcms/defs.h>
#include <booster/intrusive_ptr.h>
#include <cppcms/cstdint.h>
#include <cppcms/base_cache_fwd.h>
#include <time.h>

namespace cppcms {
	namespace impl {
		class base_cache {
		public:
			inline bool fetch(std::string const &key,std::string &a,std::set<std::string> *tags=0) 
			{
				return fetch(key,&a,tags);
			}
			virtual bool fetch(std::string const &key,std::string *a=0,std::set<std::string> *tags=0,time_t *timeout_out=0,uint64_t *gen=0) = 0; 
			virtual void store(std::string const &key,std::string const &b,std::set<std::string> const &triggers,time_t timeout,uint64_t const *gen=0) = 0;
			virtual void rise(std::string const &trigger) = 0;
			virtual void remove(std::string const &key) = 0;
			virtual void clear() = 0;
			virtual void stats(unsigned &keys,unsigned &triggers) = 0;
			virtual void add_ref() = 0;
			virtual bool del_ref() = 0;
			virtual ~base_cache()
			{
			}
		};
		inline void intrusive_ptr_add_ref(cppcms::impl::base_cache *ptr)
		{
			ptr->add_ref();
		}
		inline void intrusive_ptr_release(cppcms::impl::base_cache *ptr)
		{
			if(ptr && ptr->del_ref())
				delete ptr;
		}
	} // impl
} //cppcms
#endif
