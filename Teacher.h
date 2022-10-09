#pragma once
#include "Person.h"
class Teacher : virtual public Person
{
protected:
	string surnameT;
	string nameT;
	string position;
public:
	Teacher();
	Teacher(string surname,string name, string position);
	Teacher(const Teacher& other);
	~Teacher() ;

	virtual void OutPut()override;
	virtual void InPut()override;

	void SetPosition(string position);
	string GetPosition();
	void SetSurnameT(string surname);
	void SetNameT(string name);
	string GetSurnameT();
	string GetNameT();

	Teacher& operator()(string a,string b,string p);    //перегружені () для встановлення поля посада Викладача
	Teacher& operator=(Teacher& other);
	friend ostream& operator<<(ostream& out,Teacher& other);
	friend istream& operator>>(istream& in,Teacher& other);

	void ToFile(string path);
	void FromFile(string path);
};

