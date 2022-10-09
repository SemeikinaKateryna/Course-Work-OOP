#pragma once
#include "Person.h"
class Student : virtual public Person
{
protected:
	string surnameS;
	string nameS;
	string group;
public:
	Student();
	Student(string surname, string name, string group);
	Student (const Student& other);
	~Student(); 

	virtual void OutPut()override;
	virtual void InPut()override;

	void SetGroup(string group);
	string GetGroup();
	void SetSurnameS(string surname);
	string GetSurnameS();
	void SetNameS(string name);
	string GetNameS();

	Student& operator()(string a, string b,string n); 
	Student& operator=(const Student& other);
	friend ostream& operator<<(ostream& out, Student& other);
	friend istream& operator>>(istream& in, Student& other);

	void ToFile(string path);   //файл в який записуємо
	void FromFile(string path)override; //файл з якого зчитуємо
};

