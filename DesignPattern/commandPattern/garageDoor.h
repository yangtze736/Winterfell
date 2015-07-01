///////////////////////////////////////////////////////////
// Copyright (c) 2014, ShangHai xxxx Inc.
//
// FileName: garageDoor.h
//
// Description:
//
// Created: 2015年04月25日 星期六 17时47分28秒
// Revision: Revision: 1.0
// Compiler: g++
//
///////////////////////////////////////////////////////////

#ifndef _garageDoor_h_
#define _garageDoor_h_

#include <stdio.h>

class GarageDoor{
	public:
		void up(){
			printf("Garage Door is Open.\n");
		}
};

class GarageDoorOpenCommand :public Command{
	public:
		GarageDoorOpenCommand(GarageDoor *c){
			garageDoor = c;
		}
		virtual void execute(){
			garageDoor->up();
		}
	private:
		GarageDoor *garageDoor;
};

#endif
