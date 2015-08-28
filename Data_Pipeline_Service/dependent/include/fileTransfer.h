///////////////////////////////////////////////////////////
// Copyright (c) 2015, ShangHai xxxx Inc.
//
// FileName: fileTransfer.h
//
// Description:
//
// Created: 2015年08月27日 星期四 13时41分25秒
// Revision: Revision: 1.0
// Compiler: g++
//
///////////////////////////////////////////////////////////

#ifndef __FILETRANSFER_H__
#define __FILETRANSFER_H__

#include <string>

enum{
	BLOCK_SIZE = 1024
};

bool encrypt_filename(const std::string &token, const std::string &srcFileStr, const std::string &dstFileStr);

bool decrypt_filename(const std::string &token, const std::string &srcFileStr, const std::string &dstFileStr);


int file_upload(const std::string &strFilename, const std::string &token, const std::string &strUrl, std::string &strResponse);

int file_download(const std::string &strFilename, const std::string &token, const std::string &strUrl, std::string &strResponse);

#endif
