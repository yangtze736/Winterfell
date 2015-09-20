// **********************************************************************
//
// Copyright (c) Sari CloudBackup Group, All rights reserved.
//
// **********************************************************************

#include "parser.h"
#include "baseFunc.h"
#include "perform.h"
#include <Ice/Ice.h>
#include <DatapipelineI.h>

using namespace std;

DatapipelineI::DatapipelineI(const string& name) : _name(name)
{
}

string
DatapipelineI::fileTransfer(const string& s, const Ice::Current&)
{
	cout << s << endl;
	Perform perform;

	std::string msg = base64Decode(parseMsg(s));
	cout << msg << endl;
	
	std::string strResponse;
	perform.data_pipeline(msg, strResponse);
	cout << _name << strResponse << endl;

	return _name + strResponse;
}

