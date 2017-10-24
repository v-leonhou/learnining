#ifndef BOOSTER_SMART_PTR_DETAIL_SP_COUNTED_BASE_SPIN_HPP_INCLUDED
#define BOOSTER_SMART_PTR_DETAIL_SP_COUNTED_BASE_SPIN_HPP_INCLUDED

//
//  detail/sp_counted_base_spin.hpp - spinlock pool atomic emulation
//
//  Copyright (c) 2001, 2002, 2003 Peter Dimov and Multi Media Ltd.
//  Copyright 2004-2008 Peter Dimov
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

#include <booster/config.h>
#include <booster/smart_ptr/sp_typeinfo.h>

#ifndef BOOSTER_WIN32
#include <pthread.h>
#endif

namespace booster
{

    namespace detail
    {

        typedef union sp_counted_base_atomic {
            int i;
            unsigned int ui;
            long int li;
            unsigned long int uli;
            long long int lli;
            unsigned long long int ulli;
            char at_least[8];
        } sp_counted_base_atomic_type;

        
        class BOOSTER_API sp_counted_base
        {
        private:

            sp_counted_base( sp_counted_base const & );
            sp_counted_base & operator= ( sp_counted_base const & );

            typedef sp_counted_base_atomic_type atomic_type;

            mutable atomic_type use_count_;        // #shared
            mutable atomic_type weak_count_;       // #weak + (#shared != 0)
#ifndef BOOSTER_WIN32
            mutable pthread_mutex_t lock_;
#endif

        public:

            sp_counted_base();
            virtual ~sp_counted_base(); // nothrow

            // dispose() is called when use_count_ drops to zero, to release
            // the resources managed by *this.

            virtual void dispose() = 0; // nothrow

            // destroy() is called when weak_count_ drops to zero.

            virtual void destroy(); // nothrow
            virtual void * get_deleter( sp_typeinfo const & ti ) = 0;
            void add_ref_copy();
            bool add_ref_lock(); // true on success
            void release(); // nothrow
            void weak_add_ref(); // nothrow
            void weak_release(); // nothrow
            long use_count() const; // nothrow
        };

    } // namespace detail

} // namespace boost

#endif  // #ifndef BOOST_SMART_PTR_DETAIL_SP_COUNTED_BASE_SPIN_HPP_INCLUDED
// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4
