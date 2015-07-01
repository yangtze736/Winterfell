///////////////////////////////////////////////////////////
// Copyright (c) 2014, ShangHai xxxx Inc.
//
// FileName: light.h
//
// Description:
//
// Created: 2015年04月25日 星期六 17时44分40秒
// Revision: Revision: 1.0
// Compiler: g++
//
///////////////////////////////////////////////////////////

#ifndef _light_h_
#define _light_h_

#include <stdio.h>

class Light{
	public:
		void on(){
			printf("Light is on.\n");
		}
		void off(){
			printf("Light is off.\n");
		}
};

class LightOnCommand :public Command{
	public:
		LightOnCommand(Light *l){
			light = l;
		}
		virtual void execute(){
			light->on();
		}
	private:
		Light *light;
};

#endif
