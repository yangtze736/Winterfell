///////////////////////////////////////////////////////////
// Copyright (c) 2015, ShangHai xxxx Inc.
//
// FileName: iceGrid.h
//
// Description:
//
// Created: 2015年08月20日 星期四 10时13分09秒
// Revision: Revision: 1.0
// Compiler: g++
//
///////////////////////////////////////////////////////////
#ifndef __ICEGRID_H__
#define __ICEGRID_H__

#include <string>

class MfcIceGrid{
	public:
		MfcIceGrid();
		~MfcIceGrid();

		
		int get(const std::string &strUrl, std::string &strResponse, const char *pCaPath=NULL);
		int post(const std::string &strUrl, const std::string &postField, std::string &strResponse, const char *pCaPath=NULL);
};

#endif
