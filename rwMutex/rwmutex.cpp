///////////////////////////////////////////////////////////
// Copyright (c) 2015, ShangHai xxxx Inc.
//
// FileName: rwmutex.cpp
//
// Description:
//
// Created: 2015年09月06日 星期日 14时27分18秒
// Revision: Revision: 1.0
// Compiler: g++
//
///////////////////////////////////////////////////////////
#include "rwmutex.h"

RWMutex::RWMutex()
{
	pthread_rwlock_init(&m_rwlock, NULL); 
}

RWMutex::~RWMutex()
{
	pthread_rwlock_destroy(&m_rwlock);
}

int RWMutex::acquireRead(void)
{
	return pthread_rwlock_rdlock(&m_rwlock);
}

int RWMutex::acquireWrite(void)
{
	return pthread_rwlock_wrlock(&m_rwlock);	
}

void RWMutex::acquireCertainWrite(int num)
{
	::pthread_mutex_lock(&m_rwLock);

	while(m_refCount >= num)
	{
		m_numWaitingWriters++;
		pthread_cond_wait(&m_waitingWriters, &m_rwLock);
		m_numWaitingWriters--;
	}

	m_refCount++;
	m_logger.debug("acquire, m_refCount = %d", m_refCount);

	::pthread_mutex_unlock(&m_rwLock);
}

void RWMutex::releaseCertain(void)
{
	::pthread_mutex_lock(&m_rwLock);

	if(m_refCount > 0) // releasing a reader.
	{
		m_refCount--;
	}
	else if (m_refCount == -1) // releasing a writer.
	{
		m_refCount = 0;
	}
	else
	{
		fprintf(stderr, "release rw mutex failed. refCount=%d\n", m_refCount);
		return;
	}

	fprintf(stdout, "release, m_refCount = %d\n", m_refCount);
	if (m_numWaitingWriters > 0)  {
		pthread_cond_signal (&m_waitingWriters);
	}

	::pthread_mutex_unlock(&m_rwLock);
}

void RWMutex::release(void)
{
	pthread_rwlock_unlock(&m_rwlock);
}

ReadGuard::ReadGuard(RWMutex& rwMutex)
{
	m_rwMutex = &rwMutex;
	m_ret = m_rwMutex->acquireRead();
}

ReadGuard::~ReadGuard()
{
	if (m_ret == 0) { // 0 means success
		m_rwMutex->release();
	}
}

WriteGuard::WriteGuard(RWMutex& rwMutex)
{
	m_rwMutex = &rwMutex;
	m_ret = m_rwMutex->acquireWrite();
}

WriteGuard::~WriteGuard()
{
	if (m_ret == 0) { // 0 means success
		m_rwMutex->release();
	}
}

CertainWriteGuard::CertainWriteGuard(RWMutex& rwMutex, int num)
{
	m_rwMutex = &rwMutex;
	m_rwMutex->acquireCertainWrite(num);
}

CertainWriteGuard::~CertainWriteGuard()
{
	m_rwMutex->releaseCertain();
}

