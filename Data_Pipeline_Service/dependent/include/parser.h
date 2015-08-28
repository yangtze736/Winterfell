///////////////////////////////////////////////////////////
// Copyright (c) 2015, ShangHai xxxx Inc.
//
// FileName: parser.h
//
// Description:
//
// Created: 2015年04月29日 星期三 16时30分42秒
// Revision: Revision: 1.0
// Compiler: g++
//
///////////////////////////////////////////////////////////
#ifndef __PARSER_H__
#define __PARSER_H__

#include <string>

typedef struct MsgStructTag
{
	MsgStructTag()
	{
		method.clear();
		shareName.clear();
		objName.clear();
		objMd5.clear();
		objMode.clear();
		objToken.clear();
		objPath.clear();
	}
	std::string method;
	std::string shareName;
	std::string objName;
	std::string objMd5;
	std::string objMode;
	std::string objToken;
	std::string objPath;
}MsgStruct;

bool parseMessage(MsgStruct &msgStruct, const std::string &strJson);
bool judgeValid(const std::string &strJson);

std::string handle(const std::string &strJson);
std::string parseMsg(const std::string &strJson);
std::string parserByKey(const std::string &strJson, const std::string &key);

#endif //__PARSER_H__
