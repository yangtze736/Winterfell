///////////////////////////////////////////////////////////
// Copyright (c) 2014, ShangHai xxxx Inc.
//
// FileName: main.cpp
//
// Description:
//
// Created: 2015年04月23日 星期四 22时29分31秒
// Revision: Revision: 1.0
// Compiler: g++
//
///////////////////////////////////////////////////////////

#include "middlewareLog.h"
#include <unistd.h>
#include <sys/types.h>

int main()
{
	MFC_LOG_INIT( LOG_LEVEL_DEBUG, LOG_OUTPUT_STDERR );
	//MFC_LOG_INIT(LOG_LEVEL_DEBUG, LOG_OUTPUT_FILE);
	MFC_LOG_SETFILE("./logs/middleware.log");
	MFC_LOG_SETSYSLOG(LOG_LEVEL_DEBUG);

	pid_t fpid;
	fpid = fork();

	if(fpid < 0)
	{
		fprintf(stderr, "fork error\n");
	}
	else if (fpid == 0)
	{
		fprintf(stdout, "child process %d\n",getpid());
		PR_CRIT("CRIT");
		PR_CRIT("CRIT %s", "crit");

		PR_ERR("ERR");
		PR_ERR("ERR %s", "err");

		PR_WARN("WARN");
	}
	else
	{
		fprintf(stdout, "parent process %d\n",getpid());
		PR_NOTICE("NOTICE");
		PR_NOTICE("NOTICE %s", "notice");

		PR_INFO("INFO");
		PR_INFO("INFO %s", "info");

		PR_DEBUG("DEBUG");
		PR_DEBUG("DEBUG %s", "debug");

		PR_DEBUG("TRACE");
		PR_TRACE("TRACE %s", "trace");
	}

	return 0;
}
