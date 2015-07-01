///////////////////////////////////////////////////////////
// Copyright (c) 2014, ShangHai xxxx Inc.
//
// FileName: subject.h
//
// Description:
//
// Created: 2015年04月18日 星期六 21时56分06秒
// Revision: Revision: 1.0
// Compiler: g++
//
///////////////////////////////////////////////////////////
#ifndef _subject_h_
#define _subject_h_


class Subject{
	public:
		virtual void registerObserver(Observer *o) = 0;
		virtual void removeObserver(Observer *o) = 0;
		virtual void notifyObservers() = 0;
};

#endif
