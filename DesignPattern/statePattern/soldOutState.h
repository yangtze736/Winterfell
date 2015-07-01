///////////////////////////////////////////////////////////
// Copyright (c) 2014, ShangHai xxxx Inc.
//
// FileName: soldOutState.h
//
// Description:
//
// Created: 2015年04月26日 星期日 14时46分33秒
// Revision: Revision: 1.0
// Compiler: g++
//
///////////////////////////////////////////////////////////
#ifndef _soldOutState_h_
#define _soldOutState_h_

#include "state.h"
#include "gumballMachine.h"
#include <stdio.h>

class SoldOutState :public State{
	public:
		SoldOutState(GumballMachine *g){
			gumballMachine = g;
		}
		void insertQuarter(){
			printf("You can't insert a quarter, the machine is sold out\n");
		}
		void ejectQuarter(){
			printf("You can't eject\n");
		}
		void turnCrank(){
			printf("There is no gumballs...\n");
		}
		void dispense(){
			printf("No gumball dispensed\n");
		}

	private:
		GumballMachine *gumballMachine;
};

#endif
