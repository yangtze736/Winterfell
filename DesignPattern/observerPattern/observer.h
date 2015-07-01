///////////////////////////////////////////////////////////
// Copyright (c) 2014, ShangHai xxxx Inc.
//
// FileName: observer.h
//
// Description:
//
// Created: 2015年04月18日 星期六 21时59分42秒
// Revision: Revision: 1.0
// Compiler: g++
//
///////////////////////////////////////////////////////////
#ifndef _observer_h_
#define _observer_h_

class Observer{
	public:
		virtual void update(float temp, float humidity, float pressure) = 0;
		virtual void registerToSubject() = 0;
		virtual void removeToSubject() = 0;
};

#endif
