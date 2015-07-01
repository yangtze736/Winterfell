///////////////////////////////////////////////////////////
// Copyright (c) 2014, ShangHai xxxx Inc.
//
// FileName: gumbalMachine.h
//
// Description:
//
// Created: 2015年04月26日 星期日 13时50分42秒
// Revision: Revision: 1.0
// Compiler: g++
//
///////////////////////////////////////////////////////////
#ifndef _gumballMachine_h_
#define _gumballMachine_h_

#include "state.h"
#include <stdio.h>
#if 1
#include "soldOutState.h"
#include "noQuarterState.h"
#include "hasQuarterState.h"
#include "soldState.h"
#endif
class GumballMachine{
	private:
		State *soldOutState;
		State *noQuarterState;
		State *hasQuarterState;
		State *soldState;
		State *state;

		int count;

	public:
		GumballMachine(int numberGumballs){
			soldOutState = new SoldOutState();
			noQuarterState = new NoQuarterState();
			hasQuarterState = new HasQuarterState();
			soldState = new SoldState();
			count = numberGumballs;
			if (numberGumballs > 0)
				state = noQuarterState;
		}
		void insertQuarter(){
			state->insertQuarter();
		}
		void ejectQuarter(){
			state->ejectQuarter();
		}
		void turnCrank(){
			state->turnCrank();
			state->dispense();
		}
		void setState(State *s){
			state = s;
		}
		void releaseBall(){
			printf("A gumball comes rolling out the slot...\n");
			if(count != 0)
				count = count - 1;
		}
		int getCount(){
			return count;
		}

		//getter
		State* getNoQuarterState(){return noQuarterState;}
		State* getHasQuarterState(){return hasQuarterState;}
		State* getSoldOutState(){return soldOutState;}
		State* getSoldState(){return soldState;}

};

#endif
