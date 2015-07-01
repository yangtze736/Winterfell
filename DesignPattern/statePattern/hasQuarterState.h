///////////////////////////////////////////////////////////
// Copyright (c) 2014, ShangHai xxxx Inc.
//
// FileName: hasQuarterState.h
//
// Description:
//
// Created: 2015年04月26日 星期日 14时00分09秒
// Revision: Revision: 1.0
// Compiler: g++
//
///////////////////////////////////////////////////////////
#ifndef _hasQuarterState_h_
#define _hasQuarterState_h_

#include "state.h"
#include "gumballMachine.h"
#include <stdio.h>

class HasQuarterState :public State{
	public:
		HasQuarterState(GumballMachine *g){
			gumballMachine = g;
		}
		void insertQuarter(){
			printf("You can't insert another quarter\n");
		}
		void ejectQuarter(){
			printf("Quarter returned\n");
			gumballMachine->setState(gumballMachine->getNoQuarterState());
		}
		void turnCrank(){
			printf("You turned...\n");
			gumballMachine->setState(gumballMachine->getSoldState());
		}
		void dispense(){
			printf("No gumball dispensed\n");
		}

	private:
		GumballMachine *gumballMachine;
};


#endif
