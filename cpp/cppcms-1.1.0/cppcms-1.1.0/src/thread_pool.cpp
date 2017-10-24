///////////////////////////////////////////////////////////////////////////////
//                                                                             
//  Copyright (C) 2008-2012  Artyom Beilis (Tonkikh) <artyomtnk@yahoo.com>     
//                                                                             
//  See accompanying file COPYING.TXT file for licensing details.
//
///////////////////////////////////////////////////////////////////////////////
#define CPPCMS_SOURCE
#include <cppcms/thread_pool.h>
#include <booster/backtrace.h>
#include <booster/log.h>
#include <ostream>
#include <list>
#include <vector>
#include <cppcms/config.h>
#include <cppcms/mem_bind.h>
#include <booster/shared_ptr.h>
#include <booster/thread.h>

#if defined(CPPCMS_POSIX)
#include <signal.h>
#endif 

namespace cppcms {
namespace impl {
	class thread_pool : public booster::noncopyable {
	public:

		bool cancel(int id) {
			booster::unique_lock<booster::mutex> lock(mutex_);
			queue_type::iterator p;
			for(p=queue_.begin();p!=queue_.end();++p) {
				if(p->first==id) {
					queue_.erase(p);
					return true;
				}
			}
			return false;
		}
		int post(booster::function<void()> const &job)
		{
			booster::unique_lock<booster::mutex> lock(mutex_);
			int id=job_id_++;
			queue_.push_back(std::make_pair(id,job));
			cond_.notify_one();
			return id;
		}
		thread_pool(int threads) :
			shut_down_(false),
			job_id_(0)
		{
			workers_.resize(threads);
			#if defined(CPPCMS_POSIX)
			sigset_t set,old;
			sigfillset(&set);
			pthread_sigmask(SIG_BLOCK,&set,&old);
			#endif
			for(int i=0;i<threads;i++) {
				workers_[i].reset(new booster::thread(cppcms::util::mem_bind(&thread_pool::worker,this)));
			}
	
			#if defined(CPPCMS_POSIX)
			pthread_sigmask(SIG_SETMASK,&old,0);
			#endif
	
		}
		void stop()
		{
			{
				booster::unique_lock<booster::mutex> lock(mutex_);
				shut_down_=true;
				cond_.notify_all();
			}

			for(unsigned i=0;i<workers_.size();i++) {
				booster::shared_ptr<booster::thread> thread=workers_[i];
				workers_[i].reset();
				if(thread)
					thread->join();
			}
		}
		~thread_pool()
		{
			try {
				stop();
			}
			catch(...)
			{
			}
		}

	private:

		void worker()
		{
			for(;;) {
				booster::function<void()> job;

				{
					booster::unique_lock<booster::mutex> lock(mutex_);
					if(shut_down_)
						return;
					if(!queue_.empty()) {
						queue_.front().second.swap(job);
						queue_.pop_front();
					}
					else {
						cond_.wait(lock);
					}
				}

				if(job) {
					try {
						job();
					}
					catch(std::exception const &e) {
						BOOSTER_ERROR("cppcms") << "Catched exception in thread pool" << e.what() <<'\n'
									<< booster::trace(e);

					}
					catch(...) {
						BOOSTER_ERROR("cppcms") << "Catched unknown exception in thread pool";
					}
				}
			} 	
		}

	
		booster::mutex mutex_;
		booster::condition_variable cond_;

		bool shut_down_;	
		int job_id_;
		typedef std::list<std::pair<int,booster::function<void()> > > queue_type;
		queue_type queue_;
		std::vector<booster::shared_ptr<booster::thread> > workers_;

	};
	


}

thread_pool::thread_pool(int n) :
	impl_(new impl::thread_pool(n))
{
}

int thread_pool::post(booster::function<void()>  const &job)
{
	return impl_->post(job);
}

void thread_pool::stop()
{
	impl_->stop();
}

bool thread_pool::cancel(int id)
{
	return impl_->cancel(id);
}

thread_pool::~thread_pool()
{
}


} // cppcms


