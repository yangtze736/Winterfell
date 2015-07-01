///////////////////////////////////////////////////////////
// Copyright (c) 2014, ShangHai xxxx Inc.
//
// FileName: test.cpp
//
// Description:
//
// Created: 2015年04月25日 星期六 17时26分44秒
// Revision: Revision: 1.0
// Compiler: g++
//
///////////////////////////////////////////////////////////

#include "command.h"
#include "simpleRemoteControl.h"
#include "light.h"
#include "garageDoor.h"

int main()
{
	SimpleRemoteControl *remote = new SimpleRemoteControl();

	Light *light = new Light();
	LightOnCommand *lightOn = new LightOnCommand(light);
	remote->setCommand(lightOn);
	remote->buttonWasPressed();

	GarageDoor *garageDoor = new GarageDoor();
	GarageDoorOpenCommand *garageDoorOpen = new GarageDoorOpenCommand(garageDoor);
	remote->setCommand(garageDoorOpen);
	remote->buttonWasPressed();

	delete remote;
	delete light;delete lightOn;
	delete garageDoor;delete garageDoorOpen;

	return 0;
}
