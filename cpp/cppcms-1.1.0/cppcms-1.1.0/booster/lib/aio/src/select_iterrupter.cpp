//
//  Copyright (C) 2009-2012 Artyom Beilis (Tonkikh)
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
#define BOOSTER_SOURCE
#include <booster/config.h>
#ifdef BOOSTER_WIN32
#include <winsock2.h>
#include <windows.h>
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#endif

#include "select_iterrupter.h"
#include <booster/system_error.h>

#include "category.h"


namespace booster { namespace aio { namespace impl {
	
	select_interrupter::select_interrupter() :
		read_(invalid_socket),
		write_(invalid_socket)
	{
	}

	namespace {
		void check(native_type t)
		{
			if(t==invalid_socket) {
				#ifdef BOOSTER_WIN32
				int ec = WSAGetLastError();
				#else
				int ec=errno;
				#endif
				throw system::system_error(ec,syscat);
			}
		}
	}


	select_interrupter::~select_interrupter()
	{
		close();
	}
	namespace {
		inline void closefd(native_type fd)
		{
			#ifdef BOOSTER_WIN32
			::closesocket(fd);
			#else
			::close(fd);
			#endif
		}
	}
	void select_interrupter::close()
	{
		if(read_ != invalid_socket) 
			closefd(read_);
		if(write_ != invalid_socket)
			closefd(write_);
		read_ = write_ = invalid_socket;
	}
	
	bool select_interrupter::open()
	{
		if(read_ != invalid_socket) {
			return false;
		}
		#if defined(BOOSTER_WIN32)
		native_type fds[2]={invalid_socket,invalid_socket};
		native_type lst=invalid_socket;
		try {
			struct sockaddr_in inaddr;
			struct sockaddr addr;
			native_type lst=::socket(AF_INET, SOCK_STREAM,IPPROTO_TCP);
			check(lst);
			memset(&inaddr, 0, sizeof(inaddr));
			memset(&addr, 0, sizeof(addr));
			inaddr.sin_family = AF_INET;
			inaddr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
			inaddr.sin_port = 0;
			int yes=1;
			check(::setsockopt(lst,SOL_SOCKET,SO_REUSEADDR,(char*)&yes,sizeof(yes)));
			check(::bind(lst,(struct sockaddr *)&inaddr,sizeof(inaddr)));
			::listen(lst,1);
			int len=sizeof(inaddr);
			check(::getsockname(lst, &addr,&len));
			fds[0]=::socket(AF_INET, SOCK_STREAM,0);
			check(fds[0]);
			check(::connect(fds[0],&addr,len));
			fds[1]=::accept(lst,0,0);
			check(fds[1]);
			closefd(lst);
			lst=invalid_socket;
		}
		catch(...) {
			if(fds[0]!=invalid_socket)
				closefd(fds[0]);
			if(fds[1]!=invalid_socket)
				closefd(fds[1]);
			if(lst!=invalid_socket)
				closefd(lst);
			throw;
		}
		#else
		int fds[2];
		check(::pipe(fds));
		#endif
		read_ = fds[0];
		write_=fds[1];

		set_non_blocking(read_);	
		set_non_blocking(write_);	

		return true;
	}
	void select_interrupter::set_non_blocking(native_type fd)
	{
		#if defined BOOSTER_WIN32
		unsigned long opt =  1;
		check(::ioctlsocket(fd,FIONBIO,&opt));
		#elif defined O_NONBLOCK
		int flags = ::fcntl(fd,F_GETFL,0);
		check(flags);
		check(::fcntl(fd,F_SETFL,flags | O_NONBLOCK));
		#else
		int opt = 1;
		check(::ioctl(fd,FIONBIO,&opt));
		#endif
	}

	native_type select_interrupter::get_fd()
	{
		return read_;
	}
	
	void select_interrupter::notify()
	{
		#ifdef BOOSTER_WIN32
		char c='A';
		::send(write_,&c,1,0);
		#else
		for(;;) {
			char c='A';
			if(::write(write_,&c,1) < 0 && errno==EINTR)
				continue;
			break;
		}
		#endif
	}
	
	void select_interrupter::clean()
	{
		int n;
		static char buffer[64];
		#ifdef BOOSTER_WIN32
		n = ::recv(read_,buffer,sizeof(buffer),0);
		#else
		n = ::read(read_,buffer,sizeof(buffer));
		#endif
		(void)(n); // Shut the GCC UP
	}

	

}}} /// booster::aio::impl
