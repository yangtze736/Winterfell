///////////////////////////////////////////////////////////
//  Copyright (c) 2014, ShangHai Onewave Inc.
//
//    FileName:   main.cpp
//
//    Description:
//
//    Created:    2014-05-12
//    Revision:   Revision: 1.0
//    Compiler:   g++
//
///////////////////////////////////////////////////////////

#include "func.h"
#include "perf.h"
#include "exce.h"

int main()
{

#ifdef FUNC
	//test function
	func();
#endif

#ifdef PERF
	// test performance
	perf();
#endif

#ifdef EXCE
	// test exception
	exce();
#endif

	return 0;
}
