///////////////////////////////////////////////////////////
// Copyright (c) 2015, ShangHai xxxx Inc.
//
// FileName: fileTransfer.cpp
//
// Description:
//
// Created: 2015年08月27日 星期四 13时41分14秒
// Revision: Revision: 1.0
// Compiler: g++
//
///////////////////////////////////////////////////////////

#include "static.h"
#include "utils.h"
#include "net_tool.h"
#include "secrypto.h"
#include "fileTransfer.h"
#include "mfcFile.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <curl/curl.h>
#include <curl/easy.h>

bool encrypt_filename(const std::string &token, const std::string &srcStr, const std::string &dstStr)
{
	/****** To Get User Access Token ******/
	//std::string pResult = m_strResult;
	char tokenJson[256] = {0};                                                                                   
	sprintf(tokenJson, "{\"access_token\":\"%s\"}", token.c_str());
	std::string pResult(tokenJson);
	//PR("Access_token : [%s]", pResult.c_str());


	CSecrypto* sc = new CSecrypto();
	sc->secrypto_init();
	// add openssl conf
	CSecrypto::load_padlock();

	/******  Encrypt The File ******/
	int srcFile, dstFile;
	int bytes_read,bytes_write;

	unsigned char buffer[BLOCK_SIZE] = {0};
	unsigned char buffers[BLOCK_SIZE] = {0};

	if((srcFile = open(srcStr.c_str(), O_RDONLY)) == -1)
	{
		fprintf(stderr, "Open %s Error:%s\n", srcStr.c_str(), strerror(errno));
		return false;
	}

	if((dstFile = open(dstStr.c_str(), O_RDONLY|O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR)) == -1)
	{
		fprintf(stderr, "Open %s Error:%s\n", dstStr.c_str(), strerror(errno));
		return false;
	}


	while(bytes_read = read(srcFile, buffer, BLOCK_SIZE))
	{   
		if((bytes_read == -1) && (errno != EINTR))
		{
			break;
		}
		else if(bytes_read > 0)
		{
			int padding = 0;
			if (bytes_read % BLOCK_SIZE > 0)
			{
				padding =  BLOCK_SIZE - bytes_read % BLOCK_SIZE;
			}
			bytes_read += padding;
			while (padding > 0)
			{
				buffer[BLOCK_SIZE-padding] = '\001';
				padding--;
			}

			sc->sAES_encrypt((const unsigned char*)buffer, buffers, pResult);
			bytes_write = write(dstFile, buffers, bytes_read);

			if(bytes_write == -1) 
				break;
		}
	}   

	close(srcFile);
	close(dstFile);

	sc->secrypto_destroy();
	delete sc, sc = NULL;

	return true;
}

bool decrypt_filename(const std::string &token, const std::string &srcStr, const std::string &dstStr)
{
	/****** To Get User Access Token ******/
	//std::string pResult = m_strResult;
	char tokenJson[256] = {0};                                                                                   
	sprintf(tokenJson, "{\"access_token\":\"%s\"}", token.c_str());
	std::string pResult(tokenJson);
	//PR("Access_token : [%s]", pResult.c_str());


	CSecrypto* sc = new CSecrypto();
	sc->secrypto_init();
	// add openssl conf
	CSecrypto::load_padlock();

	/******  Decrypt The File ******/
	int srcFile, dstFile;
	int bytes_read, bytes_write;

	unsigned char buffer[BLOCK_SIZE] = {0};
	unsigned char buffers[BLOCK_SIZE] = {0};
	
    if((srcFile = open(srcStr.c_str(), O_RDONLY, S_IRUSR|S_IWUSR)) == -1)
    {
        fprintf(stderr, "Open %s Error:%s\n", srcStr.c_str(), strerror(errno));
        exit(1);
    }

	if((dstFile = open(dstStr.c_str(), O_RDONLY|O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR)) == -1)
	{
		fprintf(stderr, "Open %s Error:%s\n", dstStr.c_str(), strerror(errno));
		return false;
	}


    unsigned long offset = lseek(srcFile, 0, SEEK_END);
    lseek(srcFile, 0, SEEK_SET);
    
    unsigned long blocks = offset / BLOCK_SIZE;

    while(bytes_read = read(srcFile, buffer, BLOCK_SIZE))
    {   		
        if((bytes_read == -1) && (errno != EINTR))
        {
            break;
        } 
        else if(bytes_read > 0)
        {
            sc->sAES_decrypt((const unsigned char*)buffer, buffers, pResult);
            unsigned char* ptr = &buffers[BLOCK_SIZE-1];

            if(blocks == 1){
                while(true)
                {
                    if(*ptr != '\001' || bytes_read == 0)
                    {
                        break;
                    }
                    ptr--;
                    bytes_read--;
                }
            }            

            bytes_write = write(dstFile, buffers, bytes_read);

            if(bytes_write == -1)
                break;
        }
        blocks--;
    }

	close(srcFile);
	close(dstFile);

	sc->secrypto_destroy();
	delete sc, sc = NULL;

	return true;
}

int file_download(const std::string &strFilename, const std::string &token, const std::string &strUrl, std::string &strResponse)
{
	CURLcode res;  
	CURL* curl = curl_easy_init();  
	if(NULL == curl)  
	{  
		return CURLE_FAILED_INIT;  
	}

	struct curl_slist *slist = 0;
	char tokenBuf[128] = {0};
	sprintf(tokenBuf, "X-Auth-Token:%s", token.c_str());
	slist = curl_slist_append(slist,tokenBuf);
	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, slist);

	//
	FILE *fp;
	if((fp = fopen(strFilename.c_str(),"wb")) == NULL)
	{
		fprintf(stderr, "file open error, file:[%s]\n",strFilename.c_str());
		return -1;
	}

	curl_easy_setopt(curl, CURLOPT_URL, strUrl.c_str());  
	curl_easy_setopt(curl, CURLOPT_READFUNCTION, NULL);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteData);  
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);  
	curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);  
	curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 30);  
	curl_easy_setopt(curl, CURLOPT_TIMEOUT, 30);  

	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

	res = curl_easy_perform(curl);  
	// clean up
	fclose(fp);
	curl_slist_free_all(slist);
	curl_easy_cleanup(curl);  


	// decrypt file
	//std::string decryptFilename = MfcFile::createTmpFile(strFilename);
	//if(!decrypt_filename(token, strFilename, decryptFilename))
	//{
	//	printf("decrypt src file failed.\n");
	//	return -1;
	//}
	//
	//MfcFile::delFile(strFilename);
	//MfcFile::reName(decryptFilename, strFilename);


	return res;  
}

int file_upload(const std::string &strFilename, const std::string &token, const std::string &strUrl, std::string &strResponse)
{
	CURLcode res;
	CURL *curl = curl_easy_init();
	if(NULL == curl)
	{
		return CURLE_FAILED_INIT;
	}

	struct curl_slist *slist = 0;
	char tokenBuf[128] = {0};
	sprintf(tokenBuf, "X-Auth-Token:%s", token.c_str());
	slist = curl_slist_append(slist,tokenBuf);
	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, slist);

	// create linux file start with dot
	std::string encryptFilename = MfcFile::createTmpFile(strFilename);
	if(!encrypt_filename(token, strFilename, encryptFilename))
	{
		printf("encrypt src file failed.\n");
		return -1;
	}

	struct stat file_info;
	FILE *fp;
	if((fp = fopen(encryptFilename.c_str(),"rb")) == NULL)
	{
		fprintf(stderr, "file open error. file:[%s]\n", strFilename.c_str());
		return -1;
	}
	if(fstat(fileno(fp), &file_info) != 0)
	{
		return -1;
	}

	curl_easy_setopt(curl, CURLOPT_URL, strUrl.c_str());
	curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
	curl_easy_setopt(curl, CURLOPT_READFUNCTION, ReadData);
	curl_easy_setopt(curl, CURLOPT_READDATA, fp);
	curl_easy_setopt(curl, CURLOPT_INFILESIZE_LARGE, (curl_off_t)file_info.st_size);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, OnWriteData);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&strResponse);
	curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);
	curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 30);
	curl_easy_setopt(curl, CURLOPT_TIMEOUT, 30);

	res = curl_easy_perform(curl);

	// remove tmp file
	fclose(fp);
	MfcFile::delFile(encryptFilename);

	// clean up
	curl_slist_free_all(slist);
	curl_easy_cleanup(curl);

	return res;
}
