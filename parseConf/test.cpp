///////////////////////////////////////////////////////////
//  Copyright (c) 2013, ShangHai Onewave Inc.
//
//    FileName:   test.cpp
//
//    Description:
//
//    Created:    Mon Jun  9 15:11:27 2014
//    Revision:   Revision: 1.0
//    Compiler:   g++
//
///////////////////////////////////////////////////////////

#include "configure.h"
#include <stdio.h>

int main()
{
	// test conf 
	printf("\n ----- test -----\n");	

	ConfigSet *cfg = new ConfigSet;

	int result = 0;
	if(cfg->LoadFromFile("./test.conf", &result) < 0)
	{
		printf("failed to read conf file.\n");
	}

	int port1 = cfg->GetIntVal("ftp","port",0);
	int port2 = cfg->GetIntVal("ftp","porrt",0);
	printf("port1 = [%d], port2 = [%d]\n",port1,port2);

	char *ip = (char*)cfg->GetValue("ftp","ip",NULL);
	printf("ip = [%s]\n",ip);

	delete cfg, cfg = NULL;
	printf("\n ----- fini -----\n\n");

	return 0;
}
