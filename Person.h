#pragma once
#include "Header.h"
#include "FileEx.h"
class Person
{
public:
	virtual ~ Person();
	virtual void OutPut() = 0;
	virtual void InPut() = 0;
	virtual void FromFile(string path) = 0;
	virtual void ToFile(string path) = 0;
};

