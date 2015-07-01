///////////////////////////////////////////////////////////
// Copyright (c) 2014, ShangHai xxxx Inc.
//
// FileName: test.cpp
//
// Description:
//
// Created: 2015年04月18日 星期六 23时54分26秒
// Revision: Revision: 1.0
// Compiler: g++
//
///////////////////////////////////////////////////////////

#include "currentConditionsDisplay.h"
#include "weatherData.h"

int main(void)
{
	WeatherData *weather = new WeatherData;
	CurrentConditionsDisplay currentDisplay(weather);
	currentDisplay.registerToSubject();

	//数值改变，主题对象通知观察者
	weather->setMeasurements(80, 65, 30.4);
	weather->setMeasurements(81, 66, 30.1);

	//取消观察
	currentDisplay.removeToSubject();
	weather->setMeasurements(82, 76, 30.1);

	//再次加入观察
	currentDisplay.registerToSubject();
	weather->setMeasurements(77, 64, 30.1);

	delete weather;
	return 0;
}
