#include <booster/log.h>
#include <iostream>
#include <fstream>
#include <booster/shared_ptr.h>
#include <booster/weak_ptr.h>
#include "test.h"

booster::log::level_type last_level;
char const *last_module;
bool called = false;
std::string last_message;
void reset() 
{
	called = false;
	last_module = "";
	last_level = booster::log::all;
	last_message = "invalid";
}
class my_sink : public booster::log::sink {
	virtual void log(booster::log::message const &m)
	{
		last_level = m.level();
		last_module = m.module();
		last_message = m.log_message();
		called =true;
	}
};

bool never_called_called;
int never_called()
{
	never_called_called = true;
	return 10;
}

int main()
{
	try {
		namespace bl = booster::log;
		booster::shared_ptr<bl::sink> s(new my_sink);
		bl::logger::instance().add_sink(s);
		reset();
		BOOSTER_EMERG("test") << "Test";
		TEST(called);
		TEST(last_message == "Test");
		TEST(last_module==std::string("test"));
		TEST(last_level ==bl::emergency);
		reset();
		BOOSTER_ALERT("test") << "x";
		TEST(called);
		TEST(last_level==bl::alert);
		reset();
		BOOSTER_ERROR("test") << "x";
		TEST(called);
		TEST(last_level==bl::error);
		reset();
		BOOSTER_WARNING("test") << "x";
		TEST(!called);
		reset();
		BOOSTER_NOTICE("test") << "x";
		TEST(!called);
		reset();
		BOOSTER_DEBUG("test") << "x";
		TEST(!called);
		reset();
		bl::logger::instance().set_default_level(bl::notice);
		BOOSTER_NOTICE("test") << "x";
		TEST(called);
		reset();
		BOOSTER_INFO("test") << "x";
		TEST(!called);
		reset();
		bl::logger::instance().set_log_level(bl::error,"test");
		BOOSTER_ERROR("test") << "x";
		TEST(called);
		reset();
		BOOSTER_WARNING("test") << "x";
		TEST(!called);
		reset();
		bl::logger::instance().set_log_level(bl::warning,"test");
		BOOSTER_WARNING("test") << "x";
		TEST(called);
		reset();
		BOOSTER_NOTICE("test") << "x";
		TEST(!called);
		reset();
		bl::logger::instance().reset_log_level("test");
		BOOSTER_NOTICE("test") << "x";
		TEST(called);
		reset();
		BOOSTER_INFO("test") << "x";
		TEST(!called);
		reset();
		BOOSTER_INFO("test") << never_called();
		TEST(!called);
		TEST(!never_called_called);
		reset();
		bl::logger::instance().remove_sink(s);
		BOOSTER_ERROR("test") << "message";
		TEST(!called);
		reset();
		bl::logger::instance().add_sink(s);
		BOOSTER_ERROR("test") << "message";
		TEST(called);
		reset();
		bl::logger::instance().remove_all_sinks();
		BOOSTER_ERROR("test") << "message";
		TEST(!called);
		reset();

		booster::shared_ptr<bl::sinks::file> f(new bl::sinks::file());
		f->open("test.log");
		bl::logger::instance().add_sink(f);
		BOOSTER_ERROR("module") << "Message " << 3.14159;
		std::ifstream ifs("test.log");
		TEST(ifs.good());
		std::string line;
		std::getline(ifs,line);
		TEST(line.find("Message ")!=std::string::npos);
		TEST(line.find("module")!=std::string::npos);
		TEST(line.find("3.14159")!=std::string::npos);
	}
	catch(std::exception const &e)
	{
		std::cerr << "Fail: " <<e.what() << std::endl;
		return 1;
	}
	
	std::cout << "Ok" << std::endl;

	return 0;
}
