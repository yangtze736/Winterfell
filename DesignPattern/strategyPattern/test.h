///////////////////////////////////////////////////////////
// Copyright (c) 2014, ShangHai xxxx Inc.
//
// FileName: test.h
//
// Description:
//
// Created: 2015年04月18日 星期六 19时17分52秒
// Revision: Revision: 1.0
// Compiler: g++
//
///////////////////////////////////////////////////////////
#ifndef _test_h_
#define _test_h_

#include "duck.h"

class MallardDuck :public Duck{
	public:
		MallardDuck(){
			quackBehavior = new Quack();
			flyBehavior = new FlyWithWings();
		}
		~MallardDuck(){
			delete quackBehavior;
			delete flyBehavior;
		}
};

class ModelDuck:public Duck{
	public:
		ModelDuck(){
			quackBehavior = new Quack();
			flyBehavior = new FlyNoWay();
		}
		~ModelDuck(){
			delete quackBehavior;
			delete flyBehavior;
		}
};
#endif
