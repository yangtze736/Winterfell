///////////////////////////////////////////////////////////
// Copyright (c) 2015, ShangHai xxxx Inc.
//
// FileName: configure.h
//
// Description:
//
// Created: 2015年05月04日 星期一 14时34分11秒
// Revision: Revision: 1.0
// Compiler: g++
//
///////////////////////////////////////////////////////////
#ifndef __CONFIGURE_H__
#define __CONFIGURE_H__

#include <map>
#include <string>

#define INVALID_INTEGER 0
#define INVALID_DOUBLE  0.0

class ConfigSet
{
	private:
		ConfigSet( const ConfigSet & c );
		ConfigSet & operator = ( const ConfigSet & c );

	public:
		ConfigSet();
		~ConfigSet();

		void Clear();

		int LoadFromFile( const char * filename, int * errline = NULL );
		int StoreToFile( const char * filename );
		int Dump( void );

	public:
		// basic funxtion
		// get value, return NULL when not found.
		// const char * GetValue( const char * sectname, const char * key ) const;
		const char * GetValue( const char * sectname, const char * key, const char * default_val = NULL ) const;

		// set value, return 0 when success;  < 0 when error, 
		// if section key exist, then change it's value, otherwise add a new one
		int SetValue( const char * sectname, const char * key, const char * value );

		// some help function, 
		// get int (double), ATTENTION!! we return 0 (0.0) when error. use GetValue() to test exist or not
		// FIXME : how to deal with default value ??
		// int32_t GetIntVal( const char * sectname, const char * key ) const;
		int GetIntVal( const char * sectname, const char * key, int default_val = INVALID_INTEGER ) const;
		int SetIntVal( const char * sectname, const char * key, int value );

		// double GetDblVal( const char * sectname, const char * key ) const;
		double GetDblVal( const char * sectname, const char * key, double default_val = INVALID_DOUBLE ) const;
		int SetDblVal( const char * sectname, const char * key, double value );

		// int64_t GetInt64Val( const char * sectname, const char * key ) const;
		double GetInt64Val( const char * sectname, const char * key, double default_val = INVALID_INTEGER ) const;
		int SetInt64Val( const char * sectname, const char * key, double value );

		int DelKey( const char * sectname, const char * key );
		int DelSection( const char * sectname );

	public:
		// enum all config value, SLOW func, maybe we need an iterator-like interface
		int GetSectionNum() const;
		const char * GetSectionName( int index ) const;
		int GetSectionKeyNum( const char * sectname ) const;
		const char * GetSectionKeyName( const char * sectname, int index ) const;
		// GetFirstSectionName(), GetNextSectionName() etc...

	protected:
		static char * skip_blank( char * str );
		static char * skip_to_blank( char * str );

	protected:

		std::map< std::string, std::map< std::string, std::string > > m_cfg;

		typedef std::map< std::string, std::map< std::string, std::string > >::iterator SectItt;
		typedef std::map< std::string, std::string >::iterator ItemItt;

		typedef std::map< std::string, std::map< std::string, std::string > >::const_iterator const_SectItt;
		typedef std::map< std::string, std::string >::const_iterator const_ItemItt;
		std::string		m_fname;

};

#endif
