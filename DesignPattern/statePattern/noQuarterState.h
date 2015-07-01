///////////////////////////////////////////////////////////
// Copyright (c) 2014, ShangHai xxxx Inc.
//
// FileName: noQuarterState.h
//
// Description:
//
// Created: 2015年04月26日 星期日 14时15分43秒
// Revision: Revision: 1.0
// Compiler: g++
//
///////////////////////////////////////////////////////////
#ifndef _noQuarterState_h_
#define _noQuarterState_h_

#include "state.h"
#include "gumballMachine.h"
#include <stdio.h>

class NoQuarterState :public State{
	public:
		NoQuarterState(GumballMachine *g){
			gumballMachine = g;
		}
		void insertQuarter(){
			printf("You insert a quarter\n");
			gumballMachine->setState(gumballMachine->getHasQuarterState());
		}
		void ejectQuarter(){
			printf("You can't eject a quarter\n");
		}
		void turnCrank(){
			printf("You turned, but there is no quarter\n");
		}
		void dispense(){
			printf("You need to pay first\n");
		}

	private:
		GumballMachine *gumballMachine;

};

#endif
