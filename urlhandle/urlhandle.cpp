///////////////////////////////////////////////////////////
//  Copyright (c) 2014, ShangHai Onewave Inc.
//
//    FileName:   urlhandle.cpp
//
//    Description:
//
//    Created:    2014-05-12
//    Revision:   Revision: 1.0
//    Compiler:   g++
//
///////////////////////////////////////////////////////////

#include "string.h"
#include "urlhandle.h"
#include "stdio.h"
#include "openssl/md5.h"
#include <iconv.h>
#include <iostream>

namespace URL
{
	#define XX 127

	// Table for hex to char
	static char url_hex_map[16] = {
		'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b',
		'c', 'd', 'e', 'f'
	};

	// Table for url encode
	// ! $ & ' * + / , - .  0-9 : ; = ? @ A-Z _ a-z
	static char url_url_table[256] = {
		1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,
		1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,
		1, 0, 1, 1,  0, 1, 0, 0,  1, 1, 0, 0,  0, 0, 0, 0,
		0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  1, 0, 1, 0,
		0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,
		0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 1,  1, 1, 1, 0,
		1, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,
		0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 1,  1, 1, 1, 1,
		1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,
		1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,
		1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,
		1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,
		1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,
		1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,
		1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,
		1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,
	};

	static char url_hex_index[256] = {
		XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX,
		XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX,
		XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX,
		 0, 1, 2, 3,  4, 5, 6, 7,  8, 9,XX,XX, XX,XX,XX,XX,
		XX,10,11,12, 13,14,15,XX, XX,XX,XX,XX, XX,XX,XX,XX,
		XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX,
		XX,10,11,12, 13,14,15,XX, XX,XX,XX,XX, XX,XX,XX,XX,
		XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX,
		XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX,
		XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX,
		XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX,
		XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX,
		XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX,
		XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX,
		XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX,
		XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX,
	};

	bool findKey(const string &originUrl, const char *key, const char split, const char assign)
	{
		string str0(1,'?'), str1(1,split), str2(key), str3(1,assign);
		// for case: &key=value
		string target1 = str1 + str2 +str3;
		string::size_type pos1 = originUrl.find(target1);
		if(pos1 != string::npos)
		{
			return true;
		}
		else
		{
			// for case: ?key=value
			string target2 = str0 + str2 + str3;
			string::size_type pos2 = originUrl.find(target2);
			if(pos2 != string::npos)
			{
				return true;
			}
		}

		return false;
	}

	bool getValue(string &value, const string &originUrl, const char *key, const char split, const char assign)
	{
		// clear it first, judge return value
		value.clear();

		string str0(1,'?'), str1(1,split), str2(key), str3(1,assign);
		// for case: &key=value
		string target1 = str1 + str2 + str3;
		// for case: ?key=value
		string target2 = str0 + str2 + str3;

		string::size_type pos1 = originUrl.find(target1);
		if(pos1 != string::npos)
		{
			size_t offset = target1.length();

			string::size_type pos2 = originUrl.find(split,pos1+offset);
			if(pos2 != string::npos)
			{
				value = originUrl.substr(pos1+offset,pos2-pos1-offset);
			}
			else
			{
				value = originUrl.substr(pos1+offset,originUrl.length()-pos1-offset);
			}
		}
		else
		{
			string::size_type pos3 = originUrl.find(target2);
			if(pos3 != string::npos)
			{
				size_t offset = target2.length();

				string::size_type pos4 = originUrl.find(split,pos3+offset);
				if(pos4 != string::npos)
				{
					value = originUrl.substr(pos3+offset,pos4-pos3-offset);
				}
				else
				{
					value = originUrl.substr(pos3+offset,originUrl.length()-pos3-offset);
				}
			}
		}

		if(value.empty())
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	bool getIpPort(string &ip, string &port, const string &originUrl)
	{
		string::size_type pos1 = originUrl.find("://");
		if(pos1 != string::npos)
		{
			size_t offset = strlen("://");

			string::size_type pos2 = originUrl.find('/',pos1+offset);
			if(pos2 != string::npos)
			{
				string str = originUrl.substr(pos1+offset,pos2-pos1-offset);

				string::size_type pos3 = str.find(':');
				if(pos3 != string::npos)
				{
					// parse ip port field
					ip = str.substr(0,pos3);
					port = str.substr(pos3+sizeof(':'),str.length()-pos3-sizeof(':'));
				}
				else
				{
					// only have ip field
					ip = str;
				}
			}

		}

		return true;
	}

	bool replaceAll(string &newUrl, const string &originUrl, const char *oldFlag, const char *newFlag)
	{
		newUrl = originUrl;

		string::size_type pos = newUrl.find(oldFlag);
		while(pos != string::npos)
		{
			newUrl = newUrl.replace(pos,strlen(oldFlag),newFlag);
			pos = newUrl.find(oldFlag,pos+strlen(oldFlag));
		}

		return true;
	}

	bool replaceAll(string &originUrl, const char *oldFlag, const char *newFlag)
	{
		string::size_type pos = originUrl.find(oldFlag);
		while(pos != string::npos)
		{
			originUrl = originUrl.replace(pos,strlen(oldFlag),newFlag);
			pos = originUrl.find(oldFlag,pos+strlen(oldFlag));
		}

		return true;
	}

	bool replaceFirst(string &newUrl, const string &originUrl, const char *oldFlag, const char *newFlag)
	{
		newUrl = originUrl;

		string::size_type pos = newUrl.find(oldFlag);
		if(pos != string::npos)
		{
			newUrl = newUrl.replace(pos,strlen(oldFlag),newFlag);
		}

		return true;
	}

	bool replaceFirst(string &originUrl, const char *oldFlag, const char *newFlag)
	{
		string::size_type pos = originUrl.find(oldFlag);
		if(pos != string::npos)
		{
			originUrl = originUrl.replace(pos,strlen(oldFlag),newFlag);
		}

		return true;
	}

	bool redirect(string &originUrl, const char *ip, const char *port)
	{
		string::size_type pos1 = originUrl.find("://");
		if(pos1 != string::npos)
		{
			string::size_type pos2 = originUrl.find('/',pos1+strlen("://"));
			if(pos2 != string::npos)
			{
				string IP(ip), PORT(port);

				originUrl = originUrl.substr(0,pos1) + "://" + \
							IP + ':' + PORT + originUrl.substr(pos2,originUrl.length()-pos2);
				
				return true;
			}
		}

		return false;
	}

	bool redirect(string &newUrl, const string &originUrl, const char *ip, const char *port)
	{
		string::size_type pos1 = originUrl.find("://");
		if(pos1 != string::npos)
		{
			string::size_type pos2 = originUrl.find('/',pos1+strlen("://"));
			if(pos2 != string::npos)
			{
				string IP(ip), PORT(port);

				newUrl = originUrl.substr(0,pos1) + "://" + \
						 IP + ':' + PORT + originUrl.substr(pos2,originUrl.length()-pos2);

				return true;
			}
		}

		return false;
	}

	bool deleteField(string &originUrl, const char *field)
	{
		replaceAll(originUrl,field,"");

		return true;
	}

	bool md5Encrpt(string &md5OutPut, const string &originUrl)
	{
		unsigned char MD5Digest[MD5_DIGEST_LENGTH];
		string MD5Input(originUrl);

		md5OutPut.clear();

		MD5((unsigned char *)MD5Input.data(), MD5Input.length(), MD5Digest);
		for(unsigned int i = 0; i < MD5_DIGEST_LENGTH; i++)
		{
			char tmpNum[32] = "";
			sprintf(tmpNum, "%02x", MD5Digest[i]);
			md5OutPut.append(tmpNum);
		}

		return true;
	}

	// function about encoding
	void string_utf8_to_gbk(string &outUrl, const string &inUrl)
	{
		if(inUrl.length() <= 0)
		{
			return;
		}
		char* buf = new char[3*inUrl.length()];
		memset(buf, 0, 3*inUrl.length());
		utf8_to_gbk(buf, inUrl.c_str(), 3*inUrl.length(), inUrl.length());
		outUrl = buf;
		delete[] buf;

		return;
	}

	int utf8_to_gbk(char *outUrl, const char *inUrl, int max_len, int len)
	{
		size_t byte = len;
		size_t max_size = max_len - 1;

		char *out_ptr = outUrl;
		char *in_ptr = ( char *)inUrl;
		iconv_t cd = iconv_open("GBK", "UTF-8");
		if( cd == (iconv_t)(-1) ) {
			return -1;
		}
		int ret = iconv(cd, &in_ptr, &byte, &out_ptr, &max_size );
		iconv_close( cd );
		if( ret == -1 ) {
			//do something
		}
		outUrl[ out_ptr - outUrl ] = '\0';
		return ( out_ptr - outUrl );
	}

	void string_gbk_to_utf8(string &outUrl, const string &inUrl)
	{
		if(inUrl.length() <= 0)
		{
			return;
		}
		char* buf = new char[3*inUrl.length()];
		memset(buf, 0, 3*inUrl.length());
		gbk_to_utf8(buf, inUrl.c_str(), 3*inUrl.length(), inUrl.length());
		outUrl = buf;
		delete[] buf;

		return;
	}

	int gbk_to_utf8(char *outUrl, const char *inUrl, int max_len, int len) 
	{
		size_t byte = len, max_size = max_len - 1;
		char *out_ptr = outUrl;
		char *in_ptr = ( char *)inUrl;
		iconv_t cd = iconv_open("UTF-8", "GBK");
		if( cd == (iconv_t)(-1) ) {
			return -1;
		}
		int ret = iconv(cd, &in_ptr, &byte, &out_ptr, &max_size );
		iconv_close( cd );
		if( ret == -1 ) {
			// do something
		}
		outUrl[ out_ptr - outUrl ] = '\0';
		return ( out_ptr - outUrl );
	}

	int UrlDecode( char *outUrl, const char *inUrl, int max_len )
	{
		int pos = 0, len = strlen(inUrl);
		for(int i = 0; i < len && pos < max_len; ++i)
		{
			if(inUrl[i] != '%')
			{
				outUrl[pos++] = inUrl[i];
			}
			else if(i+3 <= len)
			{
				outUrl[pos++] = CharToHex(inUrl[i+1], inUrl[i+2]);
				i += 2;
			}
			else
			{
				break;
			}
		}

		if(pos == max_len)
		{
			pos--;
		}
		outUrl[pos] = '\0';

		return pos;
	}

	char CharToHex(char up, char low)
	{
		return ( char_to_hex(up) & 0x0f ) << 4 | ( char_to_hex(low) & 0x0f );
	}

	char char_to_hex(char ch)
	{
		return url_hex_index[(unsigned char)ch];
	}

	int UrlEncode( char *outUrl, const char *inUrl, int max_len )
	{
		int pos = 0, len = strlen(inUrl);
		for(int i = 0; i < len && pos < max_len; ++i)
		{
			if(url_url_table[(unsigned char)inUrl[i]] == '\0')
			{
				outUrl[pos++] = inUrl[i];
			}
			else if(pos + 3 <= max_len)
			{
				outUrl[pos++] = '%';
				outUrl[pos++] = url_hex_map[(inUrl[i] & 0xf0) >> 4];
				outUrl[pos++] = url_hex_map[inUrl[i] & 0x0f];
			}
			else
			{
				break;
			}
		}

		if(pos == max_len)
		{
			pos--;
		}
		outUrl[pos] = '\0';

		return pos;
	}

}
