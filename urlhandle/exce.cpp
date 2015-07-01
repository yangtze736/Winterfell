///////////////////////////////////////////////////////////
//  Copyright (c) 2013, ShangHai Onewave Inc.
//
//    FileName:   exce.cpp
//
//    Description:
//
//    Created:    2014-05-22
//    Revision:   Revision: 1.0
//    Compiler:   g++
//
///////////////////////////////////////////////////////////

#include "exce.h"
#include "urlhandle.h"
#include <iostream>

void exce()
{
	//TODO
	cout << "-----test exception situation-----\n\n";

	//
	string url1 = "http://1.2.3.4:1234/ch5/movie/hero.ts?key=123";
	bool b1 = URL::findKey(url1,"key");
	bool b2 = URL::findKey(url1,"");
	string url2;
	bool b3 = URL::findKey(url2,"key");
	bool b4 = URL::findKey(url2,"");
	cout << b1 << b2 << b3 << b4 << endl;

}
