///////////////////////////////////////////////////////////
// Copyright (c) 2014, ShangHai xxxx Inc.
//
// FileName: state.h
//
// Description:
//
// Created: 2015年04月26日 星期日 13时46分40秒
// Revision: Revision: 1.0
// Compiler: g++
//
///////////////////////////////////////////////////////////

#ifndef _state_h_
#define _state_h_

class State{
	public:
		virtual void insertQuarter(){};
		virtual void ejectQuarter(){};
		virtual void turnCrank(){};
		virtual void setState(State *s){
			state = s;
		}
		virtual void dispense(){};
	private:
		State *state;
};


#endif
