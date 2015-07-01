///////////////////////////////////////////////////////////
//  Copyright (c) 2013, ShangHai Onewave Inc.
//
//    FileName:   perf.cpp
//
//    Description:
//
//    Created:    2014-05-22
//    Revision:   Revision: 1.0
//    Compiler:   g++
//
///////////////////////////////////////////////////////////

#include "perf.h"
#include "urlhandle.h"
#include <iostream>
#include <time.h>
#include <sys/time.h>

void perf()
{
	cout << "\n ----- test_perf ----- \n" << endl;

	string urlStr = "http://www.chinacache.net:8080/ch5/test/abc/test/91774f7e7868b308d3332fa434b70c18.ts&start=0&during=20&key1=1&key2=2&key3=3&key4=4&key5=5&w=1&key=183101b";


	cout << "-----test func: findKey-----\n";
	bool bool1, bool2;
	long long t1 = get_time();
	for(int i = 0; i < 10000; i++)
	{
		bool1 = URL::findKey(urlStr,"art");
		bool2 = URL::findKey(urlStr,"during");
	}
	long long t2 = get_time();
	cout << "10000 times loop, cost " << t2-t1 << "ms.\n";

	cout << "\n-----test func: getValue-----\n";
	string valueStr1, valueStr2, valueStr3;
	long long t3 = get_time();
	for(int i = 0; i < 10000; i++)
	{
		URL::getValue(valueStr1, urlStr, "start");
		URL::getValue(valueStr2, urlStr, "during", '&');
		URL::getValue(valueStr3, urlStr, "key");
	}
	long long t4 = get_time();
	cout << "10000 times loop, cost " << t4-t3 << "ms.\n";
	
}

long long get_time()
{
	timeval tp;
	gettimeofday(&tp,0);

	return (long)(tp.tv_sec * 1000) + (long)(tp.tv_usec / 1000);
}
