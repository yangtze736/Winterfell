///////////////////////////////////////////////////////////
// Copyright (c) 2014, ShangHai xxxx Inc.
//
// FileName: test.cpp
//
// Description:
//
// Created: 2015年04月26日 星期日 14时49分59秒
// Revision: Revision: 1.0
// Compiler: g++
//
///////////////////////////////////////////////////////////
//#include "state.h"
//#include "hasQuarterState.h"
//#include "noQuarterState.h"
//#include "soldOutState.h"
//#include "soldState.h"
#include "gumballMachine.h"

int main()
{
	GumballMachine *gumballMachine = new GumballMachine(5);
	gumballMachine->insertQuarter();
	gumballMachine->turnCrank();


	gumballMachine->insertQuarter();
	gumballMachine->insertQuarter();
	gumballMachine->turnCrank();
	gumballMachine->turnCrank();
	gumballMachine->turnCrank();
	gumballMachine->turnCrank();

	gumballMachine->insertQuarter();
	gumballMachine->turnCrank();
	gumballMachine->insertQuarter();
	gumballMachine->turnCrank();
	gumballMachine->insertQuarter();
	gumballMachine->turnCrank();
	gumballMachine->insertQuarter();
	gumballMachine->turnCrank();
	gumballMachine->insertQuarter();
	gumballMachine->turnCrank();

	return 0;
}
