///////////////////////////////////////////////////////////
// Copyright (c) 2014, ShangHai xxxx Inc.
//
// FileName: soldState.h
//
// Description:
//
// Created: 2015年04月26日 星期日 14时22分35秒
// Revision: Revision: 1.0
// Compiler: g++
//
///////////////////////////////////////////////////////////
#ifndef _soldState_h_
#define _soldState_h_

#include "state.h"
#include "gumballMachine.h"
#include <stdio.h>

class SoldState :public State{
	public:
		SoldState(GumballMachine *g){
			gumballMachine = g
		}
		void insertQuarter(){
			printf("Please wait, we're already giving you a guymball\n");
		}
		void ejectQuarter(){
			printf("Sorry, you are already turned the crank\n");
		}
		void turnCrank(){
			printf("Turning twice doesn't get you another gumball!\n");
		}
		void dispense(){
			gumballMachine->releaseBall();
			if(gumballMachine->getCount() > 0){
				gumballMachine->setState(gumballMachine->getNoQuarterState());
			}
			else{
				printf("Oops, out of gumballs!\n");
				gumballMachine->setState(gumballMachine->getSoldOutState());
			}
		}

	private:
		GumballMachine *gumballMachine;

};

#endif
