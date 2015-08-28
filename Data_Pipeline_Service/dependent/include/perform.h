///////////////////////////////////////////////////////////
// Copyright (c) 2015, ShangHai xxxx Inc.
//
// FileName: perform.h
//
// Description:
//
// Created: 2015年08月27日 星期四 14时29分26秒
// Revision: Revision: 1.0
// Compiler: g++
//
///////////////////////////////////////////////////////////
#ifndef __PERFORM_H__
#define __PERFORM_H__

#include <string>

class Perform{
	public:
		Perform();
		~Perform();
	
	public:
		bool data_pipeline(const std::string &strJson, std::string &strResponse);

	private:
		bool getIpPort(std::string &strIpPort);
		bool judgeReturnCode(int ret, std::string &errMsg);
		bool getTenant(const std::string &token, std::string &tenant, std::string &strResponse);
};

#endif
