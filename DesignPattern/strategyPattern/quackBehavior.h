///////////////////////////////////////////////////////////
// Copyright (c) 2014, ShangHai xxxx Inc.
//
// FileName: quackBehavior.h
//
// Description:
//
// Created: 2015年04月18日 星期六 19时12分20秒
// Revision: Revision: 1.0
// Compiler: g++
//
///////////////////////////////////////////////////////////
#ifndef _quackBehavior_h_
#define _quackBehavior_h_

#include <stdio.h>

class QuackBehavior{
	public:
		virtual void quack() = 0;
};

class Quack :public QuackBehavior{
	public:
		virtual void quack(){
			printf("Quack.\n");
		}
};

class MuteQuack :public QuackBehavior{
	public:
		virtual void quack(){
			printf("<Silence>\n");
		}
};

#endif
