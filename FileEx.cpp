#include "FileEx.h"
FileEx::FileEx(const char* Message, string Path) :
	exception(Message)
{
	this->path = Path;
};

string FileEx:: WhatFile()
{
	return path;
};