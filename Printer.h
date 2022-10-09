#pragma once
#include"Person.h"
class Printer
{
public:
	void Printing(Person* obj)
	{
		Exam* my_ex = dynamic_cast<Exam*>(obj);
		if (my_ex)
			my_ex->OutPut(); //пізнє зв'язування  
		else
			cout << "Цей об'єкт не є об'єктом класу Exam" << endl;
	}
};

