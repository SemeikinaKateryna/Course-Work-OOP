#include "Exam.h"
#include "RecordBook.h"
Exam::Exam():Student(), Teacher()
{
	//cout << "�������� ����������� ��� ��������� ����� Exam\n";
	this->subject = " ";
	this->hours = 0;
	this->data.day = 0;
	this->data.month = 0;
	this->data.year = 0;
	this->grade = 0.0;
}

Exam::Exam(string surnameS, string nameS, string group, string surnameT, string nameT, string position,
	string subject, int hours, int day,int month,int year, double grade)
	:Student(surnameS,nameS,group),Teacher(surnameT, nameT, position)
{
	//cout << "�������� ����������� � ����������� ����� Exam\n";

	this->subject = subject;
	this->hours = hours;
	this->data.day =day;
	this->data.month = month;
	this->data.year = year;
	this->grade = grade;
}

Exam::Exam(const Exam& other):Student(other),Teacher(other)
{
	this->subject = other.subject;
	this->hours = other.hours;
	this->data.day = other.data.day;
	this->data.month = other.data.month;
	this->data.year = other.data.year;
	this->grade = other.grade;
}

Exam::~Exam()
{
	//cout << "�������� ���������� Exam\n";
}

void Exam::OutPut()
{
	cout << "����� ���������: " << subject << endl;
}
void Exam::InPut()   //��� ����� �������� � ������
{	
	Student::InPut();
	Teacher::InPut();
    cout << "������ �������: ";
	getline(cin, subject);
	cout << "������ ������� ����� ��� �������� ��������: ";
	cin >> hours;
	while (cin.fail())
	{
		cout << "������ �����, � �� ������!\n";
		cin.clear(); // �� ���������� cin � '�������' ����� ������
		cin.ignore(); // � ������� �������� ����������� ����� �� �������� ������
		cin >> hours;
	}
	while (hours <= 0)
	{
		cout << "������ ���� �����:" << endl;
		cin >> hours;
	}
	cout << "������ ���� ��������:\n";
	//�������� �� �����������
	int l, m, n;
	cout << "������ �����:" << endl; cin >> l;
	while (l > 30 || l < 0) 
	{
		cout << "������ ���� �����:" << endl;
		cin >> l;
	}
	data.day = l;
	cout << "������ �����: " << endl; cin >> n;
	while (n > 12 || n < 0)
	{
		cout << "������ ����� �����:" << endl;
		cin >> n;
	}
	data.month = n;
	cout << "������ ��:" << endl; cin >> m;
	while (m < 0)
	{
		cout << "������ ����� ��:" << endl; cin >> m;
	}
	data.year = m;
	cout << "������:\n"; cin >> grade;
	while (grade > 100 || grade < 0)
	{
		cout << "������ ������ � ������� �� 0 �� 100!\n";
		cin >> grade;
	}
}

void Exam::SetSubject(string subject)
{
	this->subject = subject;
}

void Exam::SetHours(int hours)
{
	this->hours = hours;
}

void Exam::SetDay(int day) { this->data.day = day; }

void Exam::SetMonth(int month) { this->data.month = month; }

void Exam::SetYear(int year) { this->data.year = year; }

void Exam::SetDate(int day, int month, int year)
{
	this->data.day = day;
	this->data.month = month;
	this->data.year = year;
}

void Exam::SetGrade(double grade)
{
	this->grade = grade;
}

string Exam::GetSubject()
{
	return subject;
}

int Exam::GetHours()
{
	return hours;
}

string Exam::GetDate()
{
	return "����: " + to_string(data.day) + " ̳����: " + to_string(data.month) +
		" г�: " + to_string(data.year) + "\n";
}

double Exam::GetGrade()
{
	return grade;
}

void Exam::FromFile(string path)  // ������� ������� � ����� 1 �������
{
	fstream fin;
	try
	{
		fin.open(path, fstream::in);
		if (!fin.is_open())
		{
			throw FileEx("������� ��� ������� �� ������� ����� ��������!\n", path);
		}
		char str[256];
		fin.getline(str, 256);
		surnameS = strtok(str, ";");
		nameS = strtok(0, ";");
		group = strtok(0, "\0\n");
		fin.getline(str, 256);
		surnameT = strtok(str, ";");
		nameT = strtok(0, ";");
		position = strtok(0, "\0\n");
		fin.getline(str, 100);
		subject = strtok(str, "\0\n");
		fin.getline(str, 50);
		hours = atoi(strtok(str, "\0\n"));
		fin.getline(str, 50);
		data.day = atoi(strtok(str, "."));
		data.month = atoi(strtok(0, "."));
		data.year = atoi(strtok(0, "\0\n"));
		fin.getline(str, 20);
		grade = atof(strtok(str, "\0\n"));
	}
	catch (FileEx& ex)
	{
		cout << "����: " << ex.WhatFile() << " " << ex.what() << endl;
	}
	fin.close();
}
void Exam::ToFile(string path)  // ������� ������ �� ����� 1 �������
{
	fstream fout;
	try
	{
		fout.open(path, fstream::out);
		if (!fout.is_open())
		{
			throw FileEx("������� ��� ������ �� ����� ����� ��������!\n", path);
		}
		fout << surnameS << ';';
		fout << nameS << ';';
		fout << group << endl;
		fout << surnameT << ';';
		fout << nameT << ';';
		fout << position << endl;
		fout << subject << endl;
		fout << hours << endl;
		fout << data.day << ".";
		fout << data.month <<".";
		fout << data.year << endl;
		fout << grade << endl;
	}
	catch (FileEx& ex)
	{
		cout<<"����: "<<ex.WhatFile()<<" "<< ex.what();
	}
	fout.close();
}

ostream& operator<<(ostream& out, Exam& other)
{
	out << "������� ��������: " << other.surnameS << endl;
	out << "��'� ��������: " << other.nameS << endl;
	out << "�����: " << other.group << endl;
	out << "������� ���������: " << other.surnameT << endl;
	out << "��'� ���������: "; out << other.nameT << endl;
	out << "������ ���������: "; out << other.position << endl;
	out << "����� ���������: "; out << other.subject << endl;
	out << "ʳ������ ����� ��� ��������: "; out << other.hours << endl;
	out << "���� ��������: \n" << "����: "; out << other.data.day << endl;
	out << "̳����: "; out << other.data.month << endl;
	out<< "г�: "; out << other.data.year << endl;
	out << "������: "; out << other.grade << endl;
	out << "------------------------------------\n";
	return out;
}

istream& operator>>(istream& in, Exam& other)        
{
	char str[256];
	in.getline(str, 256);
	other.surnameS = strtok(str, ";");
	other.nameS = strtok(0, ";");
	other.group = strtok(0, "\0\n");
	in.getline(str, 256);
	other.surnameT = strtok(str, ";");
	other.nameT = strtok(0, ";");
	other.position = strtok(0, "\0\n");
	in.getline(str, 100);
	other.subject = strtok(str, "\0\n");
	in.getline(str, 50);
	other.hours = atoi(strtok(str, "\0\n"));
	in.getline(str, 50);
	other.data.day = atoi(strtok(str, "."));
	other.data.month = atoi(strtok(0, "."));
	other.data.year = atoi(strtok(0, "\0\n"));
	in.getline(str, 20);
	other.grade = atof(strtok(str, "\0\n"));
	return in;
}
