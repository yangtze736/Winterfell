/////////////////////////////////////////////////////////
// Copyright (c) 2015, ShangHai xxxx Inc.
//
// FileName: parser.cpp
//
// Description:
//
// Created: 2015年04月29日 星期三 17时30分09秒
// Revision: Revision: 1.0
// Compiler: g++
//
///////////////////////////////////////////////////////////

#include "parser.h"
#include "json/json.h"
#include <strings.h>

std::string parserByKey(const std::string &strJson, const std::string &key)
{
	Json::Reader reader;
	Json::Value value;

	reader.parse(strJson, value);
	std::string val = value[key.c_str()].asString();
	return val;
}

bool judgeValid(const std::string &strJson)
{
	Json::Reader reader;
	Json::Value value;

	reader.parse(strJson, value);
	std::string status = value["status"].asString();
	if(strcasecmp(status.c_str(),"0") == 0){
		return true;
	}
	else{
		return false;
	}
}

std::string handle(const std::string &strJson)
{
	// parser json
	Json::Reader reader;
	Json::Value value;
	
	reader.parse(strJson, value);
	std::string md5 = value["objmd5"].asString();
	std::string share = value["sharename"].asString();
	std::string obj = value["objname"].asString();
	std::string mode = value["objmode"].asString();
	std::string tab = value["table"].asString();
	//std::string op = value["operate"].asString();
	std::string op = "update";
	std::string objToken = value["objtoken"].asString();
	std::string len = value["objlength"].asString();
	std::string objPath = value["objpath"].asString();


	// generate json
	Json::Value root;
	root["objmd5"] = md5;
	root["sharename"] = share;
	root["objname"] = obj;
	root["objmode"] = mode;
	root["table"] = tab;
	root["operate"] = op;
	root["objtoken"] = objToken;
	root["objlength"] = len;
	root["objpath"] = objPath;

	return root.toStyledString();
}

std::string parseMsg(const std::string &strJson)
{
	Json::Reader reader;
	Json::Value value;

	reader.parse(strJson, value);
	std::string msg = value["message"].asString();

	return msg;
}

bool parseMessage(MsgStruct &msgStruct, const std::string &strJson)
{
	Json::Reader reader;
	Json::Value value;

	reader.parse(strJson, value);
	msgStruct.shareName = value["sharename"].asString();
	msgStruct.objName = value["objname"].asString();
	msgStruct.objMd5 = value["objmd5"].asString();
	msgStruct.objMode = value["objmode"].asString();
	msgStruct.objToken = value["objtoken"].asString();
	msgStruct.objPath = value["objpath"].asString();

	return true;
}
