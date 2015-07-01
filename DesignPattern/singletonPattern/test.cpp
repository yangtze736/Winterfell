///////////////////////////////////////////////////////////
// Copyright (c) 2014, ShangHai xxxx Inc.
//
// FileName: test.cpp
//
// Description:
//
// Created: 2015年04月25日 星期六 12时04分50秒
// Revision: Revision: 1.0
// Compiler: g++
//
///////////////////////////////////////////////////////////

#include "singleton.h"
#include <stdio.h>

Singleton *Singleton::uniqueInstance = new Singleton();

int main()
{
	Singleton *p = Singleton::getInstance();
	printf("address: %p\n",p);

	Singleton *p2 = Singleton::getInstance();
	printf("address: %p\n",p2);

	return 0;
}
