///////////////////////////////////////////////////////////
// Copyright (c) 2014, ShangHai xxxx Inc.
//
// FileName: singleton.h
//
// Description:
//
// Created: 2015年04月25日 星期六 11时59分20秒
// Revision: Revision: 1.0
// Compiler: g++
//
///////////////////////////////////////////////////////////

#ifndef _singleton_h_
#define _singleton_h_

class Singleton{
	private:
		Singleton(){}

	private:
		static Singleton* uniqueInstance;

	public:
		static Singleton* getInstance(){
			return uniqueInstance;
		}
};


#endif
