///////////////////////////////////////////////////////////
// Copyright (c) 2014, ShangHai xxxx Inc.
//
// FileName: simpleRemoteControl.h
//
// Description:
//
// Created: 2015年04月25日 星期六 17时43分07秒
// Revision: Revision: 1.0
// Compiler: g++
//
///////////////////////////////////////////////////////////
#ifndef _simpleRemoteControl_h_
#define _simpleRemoteControl_h_

class SimpleRemoteControl{
	public:
		void setCommand(Command *command){
			slot = command;
		}
		void buttonWasPressed(){
			slot->execute();
		}
	private:
		Command *slot;

};

#endif
