///////////////////////////////////////////////////////////
// Copyright (c) 2014, ShangHai xxxx Inc.
//
// FileName: flyBehavior.h
//
// Description:
//
// Created: 2015年04月18日 星期六 19时02分30秒
// Revision: Revision: 1.0
// Compiler: g++
//
///////////////////////////////////////////////////////////
#ifndef _flyBehavior_h_
#define _flyBehavior_h_

#include <stdio.h>

class FlyBehavior{
	public:
		virtual void fly() = 0;
};

class FlyWithWings :public FlyBehavior{
	public:
		virtual void fly(){
			printf("I'm flying.\n");
		}
};

class FlyNoWay :public FlyBehavior{
	public:
		virtual void fly(){
			printf("I can't fly.\n");
		}
};

class FlyRocketPowered :public FlyBehavior{
	public:
		virtual void fly(){
			printf("I'm flying with a rocket.\n");
		}
};

#endif
