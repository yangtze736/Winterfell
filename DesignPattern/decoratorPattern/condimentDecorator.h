///////////////////////////////////////////////////////////
// Copyright (c) 2014, ShangHai xxxx Inc.
//
// FileName: condimentDecorator.h
//
// Description:
//
// Created: 2015年04月19日 星期日 18时29分01秒
// Revision: Revision: 1.0
// Compiler: g++
//
///////////////////////////////////////////////////////////
#ifndef _condimentDecorator_h_
#define _condimentDecorator_h_

#include <string>

class CondimentDecorator :public Beverage{
	public:
		virtual std::string getDescription(){}
};

class Mocha :public CondimentDecorator{
	public:
		Mocha(Beverage *b){
			beverage = b;
		}
		std::string getDescription(){
			return beverage->getDescription() + ", Mocha";
		}
		double cost(){
			return 0.20 + beverage->cost();
		}

	public:
		Beverage *beverage;
};

class Soy :public CondimentDecorator{
	public:
		Soy(Beverage *b){
			beverage = b;
		}
		std::string getDescription(){
			return beverage->getDescription() + ", Soy";
		}
		double cost(){
			return 0.15 + beverage->cost();
		}

	public:
		Beverage *beverage;
};

class Whip :public CondimentDecorator{
	public:
		Whip(Beverage *b){
			beverage = b;
		}
		std::string getDescription(){
			return beverage->getDescription() + ", Whip";
		}
		double cost(){
			return 0.10 + beverage->cost();
		}

	public:
		Beverage *beverage;
};

#endif
