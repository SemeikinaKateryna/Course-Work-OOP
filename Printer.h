#pragma once
#include"Person.h"
class Printer
{
public:
	void Printing(Person* obj)
	{
		Exam* my_ex = dynamic_cast<Exam*>(obj);
		if (my_ex)
			my_ex->OutPut(); //��� ��'��������  
		else
			cout << "��� ��'��� �� � ��'����� ����� Exam" << endl;
	}
};

