///////////////////////////////////////////////////////////
//  Copyright (c) 2014, ShangHai Onewave Inc.
//
//    FileName:   urlhandle.h
//
//    Description:
//
//    Created:    2014-05-12
//    Revision:   Revision: 1.0
//    Compiler:   g++
//
///////////////////////////////////////////////////////////

#ifndef _URLHANDLE_H_
#define _URLHANDLE_H_

#include <string.h>
#include <string>
#include <list>
#include <map>
#include <vector>

using namespace std;

// namespace URL is a frame about url operator
namespace URL
{
	// return true if find the key, else return false
	bool findKey(const string &originUrl, const char *key, const char split='&', const char assign='=');

	// Notice: url[http://1.1.1.1:80/ch5/movie/hero.ts?token=1111&sid=123456&start=4512412]
	// must be like this: "?key=value&" or "?key=value" or "&key=value&" or "&key=value"
	// if value is empty, return false, else return true 
	bool getValue(string &value, const string &originUrl, const char *key, const char split='&', const char assign='=');

	// 
	template< typename InputIterator >
		bool getValue(map<string, string> &mapOut, InputIterator first, InputIterator last, const string &originUrl, const char split='&', const char assign='=')
		{
			mapOut.clear();
			string value;

			string str0(1,'?'), str1(1,split), str3(1,assign);
			for( ; first != last; first++)
			{
				string str2(*first);
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
					mapOut.insert(pair<string,string>(*first,value));
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
						mapOut.insert(pair<string,string>(*first,value));
					}
				}

			}

			return true;
		}

	/* 
	 * url must be like this:
	 *     [http://192.168.1.2:8080/abcdefg...]
	 *     [http://192.168.1.2/abcdefg...]
	 *     [http://www.chinacache.net:8080/abcdefg...]
	 *     [http://www.chinacache.net/abcdefg...]
	 */
	bool getIpPort(string &ip, string &port, const string &originUrl);

	/* 
	 * string originUrl = "http://1.2.3.4:8080/ch5/if5ax/abcdefg..."
	 * string newUrl
	 * if you do operator: replacexxx(newUrl, originUrl, "if5ax/", "");
	 * newUrl = "http://1.2.3.4:8080/ch5/abcdefg..."
	 * if you do operator: replacexxx(newUrl, originUrl, "if5ax/", "replace");
	 * newUrl = "http://1.2.3.4:8080/ch5/replace/abcdefg..."
	 */
	bool replaceAll(string &newUrl, const string &originUrl, const char *oldFlag, const char *newFlag);
	// overwrite replaceAll func
	bool replaceAll(string &originUrl, const char *oldFlag, const char *newFlag);
	//
	bool replaceFirst(string &newUrl, const string &originUrl, const char *oldFlag, const char *newFlag);
	// overwrite replaceFirst func
	bool replaceFirst(string &originUrl, const char *oldFlag, const char *newFlag);

	// ip port redirect
	bool redirect(string &originUrl, const char *ip, const char *port);
	// overwrite redirect func
	bool redirect(string &newUrl, const string &originUrl, const char *ip, const char *port);

	//
	bool deleteField(string &originUrl, const char *field);

	// MD5 encryption algorithm
	bool md5Encrpt(string &md5OutPut, const string &originUrl);

	/*
	 * function about encoding
	 */
	int UrlDecode(char *outUrl, const char *inUrl, int max_len);
	char CharToHex(char up, char low);
	char char_to_hex(char ch);
	//
	int UrlEncode(char *outUrl, const char *inUrl, int max_len);

	void string_gbk_to_utf8(string &out, const string &in);
	int gbk_to_utf8(char *out, const char *in, int max_len, int len);

	void string_utf8_to_gbk(string &out, const string &in);
	int utf8_to_gbk(char *out, const char *in, int max_len, int len);

}
#endif
