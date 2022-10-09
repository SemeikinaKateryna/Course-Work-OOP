#pragma once
#include "Header.h"
class FileEx:public exception
{
	string path;
public:
	FileEx(const char* Message, string Path);
	string WhatFile();
};

