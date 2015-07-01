///////////////////////////////////////////////////////////
//  Copyright (c) 2013, ShangHai Onewave Inc.
//
//    FileName:   func.cpp
//
//    Description:
//
//    Created:    2014-05-22
//    Revision:   Revision: 1.0
//    Compiler:   g++
//
///////////////////////////////////////////////////////////

#include "func.h"
#include "urlhandle.h"
#include "string.h"
#include <iostream>
#include <stdio.h>


void func()
{

	//string urlStr = "http://124.160.184.148:8080/ch5/test/abc/test/91774f7e7868b308d3332fa434b70c18.ts&start=0&during=20&key1=1&key2=2&key3=3&key4=4&key5=5&w=1&key=183101b";
	//string urlStr = "http://124.160.184.148/ch5/test/abc/test/91774f7e7868b308d3332fa434b70c18.ts&start=0&during=20&key1=1&key2=2&key3=3&key4=4&key5=5&w=1&key=183101b";
	string urlStr = "http://www.chinacache.net:8080/ch5/test/abc/test/91774f7e7868b308d3332fa434b70c18.ts&start=0&during=20&key1=1&key2=2&key3=3&key4=4&key5=5&w=1&key=183101b";
	cout << "\norigin url : " << urlStr <<"\n\n";

	// test func: findKey
	cout << "-----test func: findKey-----\n";
	bool bool1 = URL::findKey(urlStr,"art");
	bool bool2 = URL::findKey(urlStr,"during");
	if(bool1){
		cout << "Find the key [art]\n";
	}
	else{
		cout << "Not find the key [art]\n";
	}

	if(bool2){
		cout << "Find the key [during]\n";
	}
	else{
		cout << "Not find the key [during]\n";
	}

	// test func: getValue
	cout << "-----test func: getValue-----\n";
	string valueStr1, valueStr2, valueStr3;
	URL::getValue(valueStr1, urlStr, "start");
	URL::getValue(valueStr2, urlStr, "during", '&');
	URL::getValue(valueStr3, urlStr, "key");
	cout << "Key[start] have value[" << valueStr1 << "]\n";
	cout << "Key[during] have value[" << valueStr2 << "]\n";
	cout << "Key[key] have value[" << valueStr3 << "]\n";

	// test overwrite func: getValue
	cout << "-----test overwrite func: getValue-----\n";
	string a[5] = { "start", "during", "w", "key", "key5"};
	map<string, string> map1;
	URL::getValue(map1, a, a+5, urlStr);
	map<string, string>::iterator iter1 = map1.begin();
	for(; iter1 != map1.end(); iter1++)
	{
		cout<<"key["<<iter1->first<<"] value["<<iter1->second<<"] ";
	}
	cout << endl;

	vector<string> vec(a, a+5);
	map<string, string> map2;
	URL::getValue(map2, vec.begin(), vec.end(), urlStr);
	map<string, string>::iterator iter2 = map2.begin();
	for(; iter2 != map2.end(); iter2++)
	{
		cout<<"key["<<iter2->first<<"] value["<<iter2->second<<"] ";
	}
	cout << endl;

	list<string> li(a, a+5);
	map<string, string> map3;
	URL::getValue(map3, li.begin(), li.end(), urlStr);
	map<string, string>::iterator iter3 = map3.begin();
	for(; iter3 != map3.end(); iter3++)
	{
		cout<<"key["<<iter3->first<<"] value["<<iter3->second<<"] ";
	}
	cout << endl;

	// test func: getIpPort
	cout << "\n-----test func: getIpPort-----\n";
	string ip, port;
	URL::getIpPort(ip, port, urlStr);
	cout<<"IP:["<<ip<<"] PORT:["<<port<<"]"<<endl;

	// test func: replaceUrl
	cout << "-----test func: replaceUrl-----\n";
	string replaceFirst;
	URL::replaceFirst(replaceFirst, urlStr, "test", "test001");
	cout<<"newUrl:["<<replaceFirst<<"]\n";
	string newUrl;
	URL::replaceAll(newUrl, urlStr, "test", "test001");
	cout<<"newUrl:["<<newUrl<<"]"<<endl;
	URL::replaceAll(urlStr, "test", "test001");
	cout<< urlStr <<endl;
	URL::replaceAll(newUrl, "abc", "");
	cout<<"newUrl:["<<newUrl<<"]"<<endl;

	// test func: replaceIpPort
	cout << "-----test func: replaceIpPort-----\n";
	string ipRedirect("1.2.3.4");
	string portRedirect("1234");
	URL::redirect(urlStr,ipRedirect.c_str(),portRedirect.c_str());
	cout<<urlStr<<endl;
	URL::redirect(urlStr,"124.160.184.149","81");
	cout<<urlStr<<endl;	
	string redirectStr;
	URL::redirect(redirectStr,urlStr,"www.baidu.com","8080");
	cout<<redirectStr<<endl;

	//
	cout << "-----test func: deleteField-----\n";
	URL::deleteField(urlStr,"/test");
	cout << urlStr << endl;
	URL::deleteField(urlStr,"/abc");
	cout << urlStr << endl;
	URL::deleteField(urlStr,"aaaaaaaaaa");
	cout << urlStr << endl;

	// test func: md5Encrpt
	cout << "-----test func: md5Encrpt-----\n";
	string md5String;
	URL::md5Encrpt(md5String,urlStr);
	cout<<md5String<<endl;
		
	// test func: string_utf8_to_gbk
	cout << "\n\t-----utf-8 gbk-----\n";
	string utf8StrIn = "http://1.2.3.4:8080/ch/辛亥革命/中文测试/abcdefg/sid=123456";
	cout<<"orign url:  "<<utf8StrIn<<endl;
	string gbkStrOut;
	URL::string_utf8_to_gbk(gbkStrOut, utf8StrIn);
	cout<<"utf8_to_gbk "<<gbkStrOut<<endl;
	string utfStrOut;
	URL::string_gbk_to_utf8(utfStrOut, gbkStrOut);
	cout<<"gbk_to_utf8 "<<utfStrOut<<endl;
	
	cout << "\n\t-----Encoding Test-----\n";
	
	char url_src[] = "rtsp://192.168.200.8:8564/mnt/data/movie/";
	char url[40];
	URL::UrlDecode( url, url_src, sizeof( url ) );
	printf("%s\n%s\n", url_src, url );
	printf("%s\n", strlen( url ) < sizeof( url ) ? "Encode Access OK" : "Encode Access violent" );
	printf("%d %d\n\n", strlen( url ), sizeof( url ) );
	URL::UrlEncode( url, url_src, sizeof( url ) );                                                                    
	printf("%s\n%s\n", url_src, url );
	printf("%s\n", strlen( url ) < sizeof( url ) ? "Encode Access OK" : "Encode Access violent" );
	printf("%d %d\n\n", strlen( url ), sizeof( url ) );

	char url_encode[] = "rtsp://0.0.0.0:0/<>:#$@~()* mnt/data/movie/";
	URL::UrlDecode( url, url_encode, sizeof( url ) );
	printf("%s\n%s\n", url_encode, url );
	printf("%s\n", strlen( url ) < sizeof( url ) ? "Encode Access OK" : "Encode Access violent" );
	printf("%d %d\n\n", strlen( url ), sizeof( url ) );
	URL::UrlEncode( url, url_encode, sizeof( url ) );
	printf("%s\n%s\n", url_encode, url );
	printf("%s\n", strlen( url ) < sizeof( url ) ? "Encode Access OK" : "Encode Access violent" );
	printf("%d %d\n\n", strlen( url ), sizeof( url ) );

	char url_decode[] = "rtsp://0.0.0.0:0/%20%69(%22)%mnt/data/movie/"; 
	URL::UrlDecode( url, url_decode, sizeof( url ) );
	printf("%s\n%s\n", url_decode, url );
	printf("%s\n", strlen( url ) < sizeof( url ) ? "Encode Access OK" : "Encode Access violent" );
	printf("%d %d\n\n", strlen( url ), sizeof( url ) );
	URL::UrlEncode( url, url_decode, sizeof( url ) );
	printf("%s\n%s\n", url_decode, url );
	printf("%s\n", strlen( url ) < sizeof( url ) ? "Encode Access OK" : "Encode Access violent" );
	printf("%d %d\n\n", strlen( url ), sizeof( url ) );

}
