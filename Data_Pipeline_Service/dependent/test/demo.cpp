///////////////////////////////////////////////////////////
// Copyright (c) 2015, ShangHai xxxx Inc.
//
// FileName: demo.cpp
//
// Description:
//
// Created: 2015年08月28日 星期五 19时40分57秒
// Revision: Revision: 1.0
// Compiler: g++
//
///////////////////////////////////////////////////////////

#include "iceGrid.h"
#include <stdio.h>
#include <string>


#define SEND_EVENT  "http://10.3.3.248:8080/Phoenix-Web-Service/api/Service/Queue" \
	"/SendEvent?op=OPERATION_SENDTO_QUEUE&from=pipeline&to=cloudfs&project=cloudstorage&msg="

int main()
{
	std::string sendEventUrl = SEND_EVENT;
	//sendEventUrl.append("{\"sharename\": \"f215e5a4-684e-57fa-b9f4-eb54c087b842\", \"objname\": \"hello.txt\", \"objmd5\": \"cba3802592fe1c0dba81a359977963d4\", \"objmode\": \"NORMAL\", \"table\": \"objShare_objshare\", \"operate\": \"insert\", \"objtoken\": \"7zXM751OF73uJG2I2twl1MTiTgkj57zjDmZ51dsm\", \"objlength\": \"115224\", \"objpath\": \"AUTH_wei_ji163com/normal/hello.txt\"}");
	sendEventUrl.append("eyJzaGFyZW5hbWUiOiAiZjIxNWU1YTQtNjg0ZS01N2ZhLWI5ZjQtZWI1NGMwODdiODQyIiwgIm9iam5hbWUiOiAiaGVsbG8udHh0IiwgIm9iam1kNSI6ICJjYmEzODAyNTkyZmUxYzBkYmE4MWEzNTk5Nzc5NjNkNCIsICJvYmptb2RlIjogIk5PUk1BTCIsICJ0YWJsZSI6ICJvYmpTaGFyZV9vYmpzaGFyZSIsICJvcGVyYXRlIjogImluc2VydCIsICJvYmp0b2tlbiI6ICI3elhNNzUxT0Y3M3VKRzJJMnR3bDFNVGlUZ2tqNTd6akRtWjUxZHNtIiwgIm9iamxlbmd0aCI6ICIxMTUyMjQiLCAib2JqcGF0aCI6ICJBVVRIX3dlaV9qaTE2M2NvbS9ub3JtYWwvaGVsbG8udHh0In0=");
	printf("%s\n", sendEventUrl.c_str());

	std::string sendEventResp;
	MfcIceGrid iceGrid;
	iceGrid.post(sendEventUrl, "", sendEventResp);
	printf("send resp: %s\n", sendEventResp.c_str());

	return 0;
}
