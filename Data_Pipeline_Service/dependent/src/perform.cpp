///////////////////////////////////////////////////////////
// Copyright (c) 2015, ShangHai xxxx Inc.
//
// FileName: perform.cpp
//
// Description:
//
// Created: 2015年08月27日 星期四 14时38分08秒
// Revision: Revision: 1.0
// Compiler: g++
//
///////////////////////////////////////////////////////////

#include "configure.h"
#include "parser.h"
#include "perform.h"
#include "baseFunc.h"
#include "mfcFile.h"
#include "secrypto.h"
#include "fileTransfer.h"

#include <string.h>
#include <list>


Perform::Perform()
{
}

Perform::~Perform()
{
}

bool Perform::data_pipeline(const std::string &strJson, std::string &strResponse)
{
	std::string strIpPort;
	if(!getIpPort(strIpPort))
	{
		fprintf(stderr, "get ip port from conf failed.\n");
		strResponse = "{\"status\":15001,\"errMsg\":\"get ip port from conf failed\"}";
		return false;
	}

	MsgStruct msgStruct;
	parseMessage(msgStruct, strJson);

	msgStruct.method = "file2tmp";
	if(0 == strcmp(msgStruct.method.c_str(), "file2tmp"))
	{
		//std::string tenant;
		//if(!getTenant(msgStruct.objToken, tenant, strResponse))
		//{
		//	return false;
		//}

		std::string version("/v1/");
		//std::string strUrl = "https://" + strIpPort + version + "AUTH_" + tenant \
		//					  + msgStruct.objPath + "?op=OPEN&ftype=f&type=" + msgStruct.objMode;
		std::string strUrl = "https://" + strIpPort + version + \
							  msgStruct.objPath + "?op=OPEN&ftype=f&type=" + msgStruct.objMode;
		std::cout << strUrl << std::endl;

		std::string src = "/home/test/mnt/ssh/" + msgStruct.shareName;
		file_download(src, msgStruct.objToken, urlEncode(strUrl), strResponse);
		std::cout << strResponse << std::endl;
	}
	else if(0 == strcmp(msgStruct.method.c_str(), "tmp2file"))
	{
		;
	}
	else
	{
		fprintf(stderr, "can not match method:[%s] !\n",msgStruct.method.c_str());
		return false;
	}

	return true;
}

bool Perform::getIpPort(std::string &strIpPort)
{
	ConfigSet *cfg = new ConfigSet;                                                                        
	int result = 0;
	if(cfg->LoadFromFile("./server.cnf", &result) < 0)
	{    
		return false;
	}
	char *serverIp = (char*)cfg->GetValue("server", "ip", NULL);
	int port = cfg->GetIntVal("server", "port", 0);
	char ch[128] = {0};
	sprintf(ch, "%s:%d", serverIp, port);
	strIpPort = ch;

	delete cfg, cfg = NULL;
	return true;
}

bool Perform::getTenant(const std::string &token, std::string &tenant, std::string &strResponse)        
{
	std::string output;

	CSecrypto *sc = new CSecrypto;
	sc->secrypto_init();

	char tokenJson[256] = {0};
	sprintf(tokenJson, "{\"access_token\":\"%s\"}", token.c_str());
	string tokenString(tokenJson);

	int ret = sc->convert_ukey2_cloudtoken(tokenString, output);
	std::string errMsg;
	if(!judgeReturnCode(ret, errMsg))
	{
		strResponse = "{\"status\":" + toStr(ret) + ",\"errMsg\":\"" \
					   + errMsg + "\"}";
		delete sc, sc = NULL;
		return false;
	}
	tenant = parserByKey(output, "tenant_id");

	delete sc, sc = NULL;
	return true;
}

bool Perform::judgeReturnCode(int ret, std::string &errMsg)
{
	switch(ret)
	{
		case Secrypto_NoError :
			break;
		case Error_CommunicationKey :
			//fprintf(stderr, "get communication key fail.\n");
			errMsg = "get communication key fail.";
			return false;
			break;
		case Error_PublicKey :
			//fprintf(stderr, "get public key fail.\n");
			errMsg = "get public key fail.";
			return false;
			break;
		case Error_Expire :
			//fprintf(stderr, "the access token provided is expired.\n");
			errMsg = "the access token provided is expired.";
			return false;
			break;
		case Error_NoJson :
			//fprintf(stderr, "no json object could be decoded.\n");
			errMsg = "no json object could be decoded.";
			return false;
			break;
		case Error_WrongRequest :
			//fprintf(stderr, "wrong request.\n");
			errMsg = "wrong request.";
			return false;
			break;
		case Error_Invalid :
			//fprintf(stderr, "invalid access token.\n");
			errMsg = "invalid access token.";
			return false;
			break;
		default :
			//fprintf(stderr, "unknown error number.\n");
			errMsg = "unknown error number.";
			return false;
			break;
	}
	return true;
}

