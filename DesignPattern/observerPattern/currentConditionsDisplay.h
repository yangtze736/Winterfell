///////////////////////////////////////////////////////////
// Copyright (c) 2014, ShangHai xxxx Inc.
//
// FileName: currentConditionsDisplay.h
//
// Description:
//
// Created: 2015年04月18日 星期六 23时43分02秒
// Revision: Revision: 1.0
// Compiler: g++
//
///////////////////////////////////////////////////////////
#ifndef _currentConditionsDisplay_h_
#define _currentConditionsDisplay_h_

#include "observer.h"
#include "subject.h"
#include "displayElement.h"
#include <iostream>

class CurrentConditionsDisplay :public Observer, DisplayElement{
	public:
		CurrentConditionsDisplay(Subject *data){
			weatherData = data;
		}
		virtual void registerToSubject(){
			weatherData->registerObserver(this);
		}
		virtual void removeToSubject(){
			weatherData->removeObserver(this);
		}
		virtual void update(float t, float h, float p){
			temperature = t;
			humidity = h;
			display();
		}
		virtual void display(){
			std::cout << "Current conditions: " << temperature \
				<< "F degrees, humidity: " << humidity << "% humidity" << std::endl;
		}

	private:
		Subject *weatherData;
		float temperature;
		float humidity;
};

#endif
