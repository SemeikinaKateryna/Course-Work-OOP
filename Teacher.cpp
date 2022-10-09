#include "Teacher.h"

Teacher::Teacher()
{
	//cout << "Визвався конструктор без параматрів класу Teacher\n";
	surnameT = " ";
	nameT = " ";
	position = " ";
}

Teacher::Teacher(string surname, string name, string position)
{
	//cout << "Визвався конструктор з параматрами класу Teacher\n";

	this->nameT = name;
	this->surnameT = surname;
	this->position = position;
}

Teacher::Teacher(const Teacher& other)
{
	this->surnameT = other.surnameT;
	this->nameT = other.nameT;
	this->position = other.position;
}

Teacher::~Teacher()
{
	//cout << "Визвався деструктор Teacher\n";
 }

void Teacher::OutPut()
{
	cout << "Прізвище викладача: " << surnameT << endl;
}

void Teacher::InPut()
{
	cout << "Введіть прізвище викладача:";
	getline(cin, surnameT);
	cout << "Введіть ім'я викладача:";
	getline(cin, nameT);
	cout << "Введіть посаду викладача:";
	getline(cin, position);
}


void Teacher::SetPosition(string position)
{
	this->position = position;
}

string Teacher::GetPosition()
{
	return position;
}

Teacher& Teacher::operator()(string a, string b, string p)
{
	SetSurnameT(a);
	SetNameT(b);
	SetPosition(p);
	return *this;
}

Teacher& Teacher::operator=(Teacher& other)
{
	this->surnameT = other.surnameT;
	this->nameT = other.nameT;
	this->position = other.position;
	return *this;
}

ostream& operator<<(ostream& out,Teacher& other)
{
	out << "Прізвище викладача: " << other.surnameT << endl;
	out << "Ім'я викладача: " << other.nameT << endl;
	out << "Посада викладача: " << other.position << endl;
	return out;
}

istream& operator>>(istream& in,Teacher& other)
{
	cout << "Введіть прізвище викладача:" << endl;
	getline(cin, other.surnameT);
	cout << "Введіть ім'я викладача:" << endl;
	getline(cin, other.nameT);
	cout << "Введіть посаду викладача:" << endl;
	getline(cin, other.position);
	return in;
}

void Teacher::ToFile(string path)
{
	fstream fout;
	try
	{
		fout.open(path, fstream::out);
		if (!fout.is_open())
		{
			throw FileEx("Помилка при відкритті на запис даних Викладача!\n", path);
		}
		cout << "Файл відрит!\n";
		fout << this->surnameT << ";";
		fout << this->nameT << ";";
		fout << this->position << endl;
	}
	catch (FileEx& ex)
	{
		cout << "Файл: " << ex.WhatFile() << " " << ex.what() << endl;
	}
	fout.close();
}

void Teacher::FromFile(string path)
{
	fstream fin;
	try
	{
		fin.open(path, fstream::in);
		if (!fin.is_open())
		{
			throw FileEx("Помилка при відкритті на читання даних Викладача!\n", path);
		}
		cout << "Файл відрит!\n";
		getline(fin, this->surnameT, ';');
		getline(fin, this->nameT, ';');
		getline(fin, this->position, '\n');
	}
	catch (FileEx& ex)
	{
		cout << "Файл: " << ex.WhatFile() << " " << ex.what() << endl;

	}
	fin.close();
}

void Teacher::SetSurnameT(string surname)
{
	this->surnameT = surname;
}
void Teacher::SetNameT(string name)
{
	this->nameT = name;
}
string Teacher::GetSurnameT()
{
	return surnameT;
}
string Teacher::GetNameT()
{
	return nameT;
}
