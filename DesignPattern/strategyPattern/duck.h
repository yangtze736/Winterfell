///////////////////////////////////////////////////////////
// Copyright (c) 2014, ShangHai xxxx Inc.
//
// FileName: duck.h
//
// Description:
//
// Created: 2015年04月18日 星期六 18时47分58秒
// Revision: Revision: 1.0
// Compiler: g++
//
///////////////////////////////////////////////////////////
#ifndef _duck_h_
#define _duck_h_

#include "flyBehavior.h"
#include "quackBehavior.h"

class Duck{
	public:
		Duck(){
			flyBehavior = NULL;
			quackBehavior = NULL;
		}
		void performFly(){
			flyBehavior->fly();
		}
		void performQuack(){
			quackBehavior->quack();
		}
		void setFlyBehavior(FlyBehavior *fb){
			if(flyBehavior != NULL){
				delete flyBehavior;
			}
			flyBehavior = fb;
		}
		void setQuackBehavior(QuackBehavior *qb){
			if(quackBehavior != NULL){
				delete quackBehavior;
			}
			quackBehavior = qb;
		}

	public:
		FlyBehavior *flyBehavior;
		QuackBehavior *quackBehavior;

};

#endif
