#include "Student.h"

Student::Student()
{
	//cout << "�������� ����������� ��� ��������� ����� Student\n";

	surnameS = " ";
	nameS = " ";
	group = " ";
}

Student::Student(string surname, string name,string group) 
{
	//cout << "�������� ����������� � ����������� ����� Student\n";

	this->surnameS = surname;
	this->nameS = name;
    this->group = group;
}

Student::Student(const Student& other)
{
	this->surnameS = other.surnameS;
	this->nameS = other.nameS;
	this->group = other.group;
}

Student::~Student()
{
	//cout << "�������� ���������� ����� Student\n";
}

void Student::OutPut()
{
	cout << "������� ��������: " << surnameS << endl;
}

void Student::InPut()  //��� ����� � ������
{
	cout << "������ ������� ��������:";
	getline(cin, surnameS);
	cout << "������ ��'� ��������:";
	getline(cin, nameS);
	cout << "������ ����� ����� ��������:";
	getline(cin, group);
}


Student& Student::operator=(const Student& other)
{
	this->surnameS = other.surnameS;
	this->nameS = other.nameS;
	this->group = other.group;
	return *this;
}

void Student::ToFile(string path)
{
	fstream fout;
	try
	{
		fout.open(path, fstream::out);
		if (!fout.is_open())
		{
			throw FileEx("������� ��� ������� �� ����� ����� ��������!\n", path);
		}
		cout << "���� �����!\n";
		fout << this->surnameS <<";";
		fout << this->nameS << ";";
		fout << this->group << endl;
	}
	catch (FileEx &ex)
	{
		cout << "����: " << ex.WhatFile() << " " << ex.what() << endl;
	}
	fout.close();
}

void Student::FromFile(string path)
{
	fstream fin;
	try
	{
		fin.open(path, fstream::in);
		if (!fin.is_open())
		{
			throw FileEx("������� ��� ������� �� ������� ����� ��������!\n",path);
		}
		cout << "���� �����!\n";
		getline(fin, this->surnameS, ';');
		getline(fin, this->nameS,';');
		getline(fin, this->group, '\n');
	}
	catch (FileEx&ex)
	{
		cout << "����: " << ex.WhatFile() << " " << ex.what() << endl;
	}
	fin.close();
}

ostream& operator<<(ostream &out, Student& other)
{
	out << "������� ��������: " <<other.surnameS << endl;
	out << "��'� ��������: " << other.nameS << endl;
	out <<"�����: " << other.group << endl;
	return out;
}

istream& operator>>(istream& in,Student& other)
{
	cout << "������ ������� ��������:";
	getline(in, other.surnameS);
	cout << "������ ��'� ��������:";
	getline(in, other.nameS);
	cout << "������ ����� �����:";
	getline(in, other.group);
	return in;
}
void Student::SetSurnameS(string surname)
{
	this->surnameS = surname;
}
void Student::SetNameS(string name)
{
	this->nameS = name;
}
string Student::GetSurnameS()
{
	return surnameS;
}
string Student::GetNameS()
{
	return nameS;
};
void Student::SetGroup(string group)
{
	this->group = group;
};

string Student::GetGroup()
{
	return group;
}

Student& Student::operator()(string a, string b,string n)
{
	SetNameS(a);
	SetSurnameS(b);
	SetGroup(n);
	return *this;
}



