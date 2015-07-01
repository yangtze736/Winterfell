//////////////////////////////////////////////////////////
// Copyright (c) 2014, ShangHai xxxx Inc.
//
// FileName: beverage.h
//
// Description:
//
// Created: 2015年04月19日 星期日 18时16分49秒
// Revision: Revision: 1.0
// Compiler: g++
//
///////////////////////////////////////////////////////////
#ifndef _beverage_h_
#define _beverage_h_

#include <iostream>

class Beverage{
	public:
		Beverage(){}
		virtual ~Beverage(){}
		virtual double cost(){}
		virtual std::string getDescription(){}

	protected:
		std::string description;
};

class Espresso :public Beverage{
	public:
		Espresso(){
			description = "Espresso";
		}
		double cost(){
			return 1.99;
		}
		std::string getDescription(){
			return description;
		}
};

class HouseBlend :public Beverage{
	public:
		HouseBlend(){
			description = "House Blend Coffee";
		}
		double cost(){
			return 0.89;
		}
		std::string getDescription(){
			return description;
		}
};

class DarkRoast :public Beverage{
	public:
		DarkRoast(){
			description = "Dark Roast Coffee";
		}
		double cost(){
			return 0.99;
		}
		std::string getDescription(){
			return description;
		}
};

#endif
