///////////////////////////////////////////////////////////
// Copyright (c) 2014, ShangHai xxxx Inc.
//
// FileName: test.cpp
//
// Description:
//
// Created: 2015年04月19日 星期日 18时48分15秒
// Revision: Revision: 1.0
// Compiler: g++
//
///////////////////////////////////////////////////////////
#include "beverage.h"
#include "condimentDecorator.h"
#include <iostream>

int main(void)
{
	Beverage *beverage = new Espresso();
	std::cout << beverage->getDescription() << " $" << beverage->cost() << std::endl;

	Beverage *beverage2 = new DarkRoast();
	Beverage *beverage3 = new Mocha(beverage2);
	Beverage *beverage4 = new Mocha(beverage3);
	Beverage *beverage5 = new Whip(beverage4);
	std::cout << beverage5->getDescription() << " $" << beverage5->cost() << std::endl;

	delete beverage;
	delete beverage2;
	delete beverage3;
	delete beverage4;
	delete beverage5;

	return 0;
}
