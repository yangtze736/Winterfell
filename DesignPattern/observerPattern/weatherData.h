///////////////////////////////////////////////////////////
// Copyright (c) 2014, ShangHai xxxx Inc.
//
// FileName: weatherData.h
//
// Description:
//
// Created: 2015年04月19日 星期日 01时07分08秒
// Revision: Revision: 1.0
// Compiler: g++
//
///////////////////////////////////////////////////////////

#include "subject.h"
#include "observer.h"
#include <list>

class WeatherData :public Subject{
	public:
		virtual void registerObserver(Observer *o){
			observers.push_back(o);
		}
		virtual void removeObserver(Observer *o){
			observers.remove(o);
		}
		virtual void notifyObservers(){
			std::list<Observer*>::iterator ite = observers.begin();
			for(; ite != observers.end(); ite++){
				(*ite)->update(temperature, humidity, pressure);
			}
		}
		void measurementsChanged(){
			notifyObservers();
		}
		void setMeasurements(float t, float h, float p){
			temperature = t;
			humidity = h;
			pressure = p;
			measurementsChanged();
		}
		int get(){return observers.size();}


	private:
		std::list<Observer*> observers;
		float temperature;
		float humidity;
		float pressure;
};
