//
//  Copyright (C) 2009-2012 Artyom Beilis (Tonkikh)
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
#include <booster/function.h>
#include "test.h"
#include <iostream>

bool foov_called;
void foov() { 
	foov_called=true;
}
bool fooi_called;
int fooi()
{
	fooi_called=true;
	return 10;
}
bool fooid_called;

int fooid(double const &v)
{
	TEST(v==10.0);
	fooid_called = true;
	return 0;
}

int fooii(int &x)
{
	return x++;
}

void reset()
{
	foov_called = fooi_called = fooid_called = false;
}

struct call_counter {
	int counter;
	call_counter() : counter(0) {}
	int operator()() { return ++counter; }
};


int main()
{
	using booster::function;
	try {
		reset();
		function<void()> f=foov;
		f();
		TEST(foov_called);
		f=fooi;
		f();
		TEST(fooi_called);
		function<int()> fi=fooi;
		TEST(fi()==10);
		TEST(fi);
		function<void(int)> fvi;
		TEST(!fvi);
		try {
			fvi(10);
			throw std::runtime_error("Not throws!");
		}
		catch(booster::bad_function_call const &e) {}
		fvi=fooid;
		TEST(fvi);
		fvi(10);
		TEST(fooid_called);
		int x=2;
		TEST(function<int(int&)>(fooii)(x)==2);
		TEST(x==3);

		function<int()> fcnt1=call_counter();
		function<int()> fcnt2=fcnt1;
		TEST(fcnt1()==1);
		TEST(fcnt1()==2);
		TEST(fcnt2()==1);
		TEST(fcnt2()==2);
	}
	catch(std::exception const &e)
	{
		std::cout << "Fail"<< e.what() << std::endl;
		return 1;
	}
	std::cout << "Ok" << std::endl;
	return 0;
}
