#include "Teacher.h"

Teacher::Teacher()
{
	//cout << "�������� ����������� ��� ��������� ����� Teacher\n";
	surnameT = " ";
	nameT = " ";
	position = " ";
}

Teacher::Teacher(string surname, string name, string position)
{
	//cout << "�������� ����������� � ����������� ����� Teacher\n";

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
	//cout << "�������� ���������� Teacher\n";
 }

void Teacher::OutPut()
{
	cout << "������� ���������: " << surnameT << endl;
}

void Teacher::InPut()
{
	cout << "������ ������� ���������:";
	getline(cin, surnameT);
	cout << "������ ��'� ���������:";
	getline(cin, nameT);
	cout << "������ ������ ���������:";
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
	out << "������� ���������: " << other.surnameT << endl;
	out << "��'� ���������: " << other.nameT << endl;
	out << "������ ���������: " << other.position << endl;
	return out;
}

istream& operator>>(istream& in,Teacher& other)
{
	cout << "������ ������� ���������:" << endl;
	getline(cin, other.surnameT);
	cout << "������ ��'� ���������:" << endl;
	getline(cin, other.nameT);
	cout << "������ ������ ���������:" << endl;
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
			throw FileEx("������� ��� ������� �� ����� ����� ���������!\n", path);
		}
		cout << "���� �����!\n";
		fout << this->surnameT << ";";
		fout << this->nameT << ";";
		fout << this->position << endl;
	}
	catch (FileEx& ex)
	{
		cout << "����: " << ex.WhatFile() << " " << ex.what() << endl;
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
			throw FileEx("������� ��� ������� �� ������� ����� ���������!\n", path);
		}
		cout << "���� �����!\n";
		getline(fin, this->surnameT, ';');
		getline(fin, this->nameT, ';');
		getline(fin, this->position, '\n');
	}
	catch (FileEx& ex)
	{
		cout << "����: " << ex.WhatFile() << " " << ex.what() << endl;

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
