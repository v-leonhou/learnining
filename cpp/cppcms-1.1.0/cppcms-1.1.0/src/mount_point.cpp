///////////////////////////////////////////////////////////////////////////////
//                                                                             
//  Copyright (C) 2008-2012  Artyom Beilis (Tonkikh) <artyomtnk@yahoo.com>     
//                                                                             
//  See accompanying file COPYING.TXT file for licensing details.
//
///////////////////////////////////////////////////////////////////////////////
#define CPPCMS_SOURCE
#include <cppcms/mount_point.h>
#include <booster/regex.h>

namespace cppcms {

struct mount_point::_data {};
mount_point::mount_point() :
	group_(0),
	selection_(match_path_info)
{
}

mount_point::mount_point(std::string const &path,int group) :
	path_info_(path),
	group_(group),
	selection_(match_path_info)
{
}

mount_point::mount_point(std::string const &script) :
	script_name_(script),
	group_(0),
	selection_(match_path_info)
{
}

mount_point::mount_point(std::string const &script,std::string const &path,int group) :
	script_name_(script),
	path_info_(path),
	group_(group),
	selection_(match_path_info)
{
}

mount_point::mount_point(mount_point::selection_type sel,std::string const &selected,int group) :
	group_(group),
	selection_(sel)
{
	if(sel == match_path_info)
		path_info_ = booster::regex(selected);
	else
		script_name_ = booster::regex(selected);
}

mount_point::mount_point(mount_point::selection_type sel,std::string const &non,std::string const &selected,int group) :
	group_(group),
	selection_(sel)
{
	if(sel == match_path_info) {
		path_info_ = booster::regex(selected);
		script_name_ = booster::regex(non);
	}
	else {
		script_name_ = booster::regex(selected);
		path_info_ = booster::regex(non);
	}
}

mount_point::mount_point(mount_point::selection_type sel,std::string const &non) :
	group_(0),
	selection_(sel)
{
	if(sel == match_path_info) {
		script_name_ = booster::regex(non);
	}
	else {
		path_info_ = booster::regex(non);
	}
}

mount_point::mount_point(	selection_type sel,
				booster::regex const &http_host,
				booster::regex const &script,
				booster::regex const &path,
				int group) 
	:	host_(http_host),
		script_name_(script),
		path_info_(path),
		group_(group),
		selection_(sel)
{
}



mount_point::~mount_point()
{
}

mount_point::mount_point(mount_point const &other) : 
	host_(other.host_),
	script_name_(other.script_name_),
	path_info_(other.path_info_),
	group_(other.group_),
	selection_(other.selection_)
{
}

mount_point const &mount_point::operator=(mount_point const &other) 
{
	if(this!=&other) {
		host_ = other.host_;
		script_name_ = other.script_name_;
		path_info_ = other.path_info_;
		group_ = other.group_;
		selection_ = other.selection_;
	}
	return *this;
}

void mount_point::host(booster::regex const &h) 
{
	host_ = h;
}

void mount_point::script_name(booster::regex const &s) 
{
	script_name_ = s;
}

void mount_point::path_info(booster::regex const &p)
{
	path_info_ = p;
}

void mount_point::group(int g)
{
	group_ = g;
}

void mount_point::selection(mount_point::selection_type s)
{
	selection_ = s;
}

booster::regex mount_point::host() const
{
	return host_;
}

booster::regex mount_point::script_name() const
{
	return script_name_;
}

booster::regex mount_point::path_info() const
{
	return path_info_;
}

int mount_point::group() const
{
	return group_;
}

mount_point::selection_type mount_point::selection() const
{
	return selection_;
}


std::pair<bool,std::string> mount_point::match(std::string const &h,std::string const &s,std::string const &p) const
{
	return match(h.c_str(),s.c_str(),p.c_str());
}
std::pair<bool,std::string> mount_point::match(char const *h,char const *s,char const *p) const
{
	std::pair<bool,std::string> res;
	res.first = false;

	if(!host_.empty() && !booster::regex_match(h,host_))
		return res;

	if(selection_ == match_path_info) {
		if(!script_name_.empty() && !booster::regex_match(s,script_name_))
			return res;
		if(path_info_.empty()) {
			res.second = p;
			res.first = true;
			return res;
		}
		
		if(group_ == 0) {
			if(!booster::regex_match(p,path_info_))
				return res;
			res.second=p;
			res.first=true;
			return res;
		}
		else {
			booster::cmatch m;
			if(!booster::regex_match(p,m,path_info_))
				return res;
			res.second=m[group_];
			res.first = true;
			return res;
		}
	}
	else {
		if(!path_info_.empty() && !booster::regex_match(p,path_info_))
			return res;
		if(script_name_.empty()) {
			res.second=s;
			res.first = true;
			return res;
		}
		if(group_ == 0) {
			if(!booster::regex_match(s,script_name_))
				return res;
			res.second=s;
			res.first = true;
			return res;
		}
		else {
			booster::cmatch m;
			if(!booster::regex_match(s,m,script_name_))
				return res;
			res.second=m[group_];
			res.first = true;
			return res;
		}
	}
}




} // cppcms
