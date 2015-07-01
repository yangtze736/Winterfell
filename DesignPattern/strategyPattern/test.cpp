///////////////////////////////////////////////////////////
// Copyright (c) 2014, ShangHai xxxx Inc.
//
// FileName: test.cpp
//
// Description:
//
// Created: 2015年04月18日 星期六 19时18分50秒
// Revision: Revision: 1.0
// Compiler: g++
//
///////////////////////////////////////////////////////////
#include "test.h"

int main(void)
{
	MallardDuck *mallard = new MallardDuck();
	mallard->performQuack();
	mallard->performFly();

	ModelDuck model;
	model.performFly();
	model.setFlyBehavior(new FlyRocketPowered());
	model.performFly();

	return 0;
}
