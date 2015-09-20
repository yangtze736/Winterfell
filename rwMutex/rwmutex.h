///////////////////////////////////////////////////////////
// Copyright (c) 2015, ShangHai xxxx Inc.
//
// FileName: rwmutex.h
//
// Description:
//
// Created: 2015年09月06日 星期日 14时27分18秒
// Revision: Revision: 1.0
// Compiler: g++
//
///////////////////////////////////////////////////////////
#ifndef __RWMUTEX_H__
#define __RWMUTEX_H__

#include <pthread.h>
#include <sys/types.h>

class RWMutex
{
	public:
		RWMutex();
		virtual ~RWMutex();

		int acquireRead(void);
		int acquireWrite(void);

		void acquireCertainWrite(int num);
		void releaseCertain(void);

		void release(void);

	protected:

		int32				m_refCount;
		int32				m_numWaitingWriters;
		int32				m_numWaitingReads;
		pthread_mutex_t 	m_rwLock;
		pthread_cond_t		m_waitingWriters;
		pthread_cond_t		m_waitingReads;	

		pthread_rwlock_t    m_rwlock;
};

class ReadGuard
{
	public:
		ReadGuard(RWMutex& rwMutex);
		virtual ~ReadGuard();

	private:
		RWMutex*	m_rwMutex;
		int 		m_ret;
};

class WriteGuard
{
	public:
		WriteGuard(RWMutex& rwMutex);
		virtual ~WriteGuard();

	private:
		RWMutex*	m_rwMutex;
		int 		m_ret;	
};

class CertainWriteGuard
{
	public:
		CertainWriteGuard(RWMutex& rwMutex, int num);
		virtual ~CertainWriteGuard();

	private:
		RWMutex*		m_rwMutex;
};

#endif /*__RWMUTEX_H__*/

