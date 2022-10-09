#include "Exam.h"
#include "RecordBook.h"
Exam::Exam():Student(), Teacher()
{
	//cout << "Визвався конструктор без параматрів класу Exam\n";
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
	//cout << "Визвався конструктор з параматрами класу Exam\n";

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
	//cout << "Визвався деструктор Exam\n";
}

void Exam::OutPut()
{
	cout << "Назва дисципліни: " << subject << endl;
}
void Exam::InPut()   //для вводу екзамена з консолі
{	
	Student::InPut();
	Teacher::InPut();
    cout << "Введіть предмет: ";
	getline(cin, subject);
	cout << "Введіть кількість годин для вивчення предмета: ";
	cin >> hours;
	while (cin.fail())
	{
		cout << "Введіть число, а не символ!\n";
		cin.clear(); // то возвращаем cin в 'обычный' режим работы
		cin.ignore(); // и удаляем значения предыдущего ввода из входного буфера
		cin >> hours;
	}
	while (hours <= 0)
	{
		cout << "Введіть інше число:" << endl;
		cin >> hours;
	}
	cout << "Введіть дату екзамену:\n";
	//перевірка на корректність
	int l, m, n;
	cout << "Введіть число:" << endl; cin >> l;
	while (l > 30 || l < 0) 
	{
		cout << "Введіть інше число:" << endl;
		cin >> l;
	}
	data.day = l;
	cout << "Введіть місяць: " << endl; cin >> n;
	while (n > 12 || n < 0)
	{
		cout << "Введіть інший місяць:" << endl;
		cin >> n;
	}
	data.month = n;
	cout << "Введіть рік:" << endl; cin >> m;
	while (m < 0)
	{
		cout << "Введіть інший рік:" << endl; cin >> m;
	}
	data.year = m;
	cout << "Оцінка:\n"; cin >> grade;
	while (grade > 100 || grade < 0)
	{
		cout << "Введіть оцінку в діапазоні від 0 до 100!\n";
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
	return "День: " + to_string(data.day) + " Місяць: " + to_string(data.month) +
		" Рік: " + to_string(data.year) + "\n";
}

double Exam::GetGrade()
{
	return grade;
}

void Exam::FromFile(string path)  // функція зчитати з файлу 1 екзамен
{
	fstream fin;
	try
	{
		fin.open(path, fstream::in);
		if (!fin.is_open())
		{
			throw FileEx("Помилка при відкритті на читання даних Екзамену!\n", path);
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
		cout << "Файл: " << ex.WhatFile() << " " << ex.what() << endl;
	}
	fin.close();
}
void Exam::ToFile(string path)  // функція запису до файлу 1 екзамен
{
	fstream fout;
	try
	{
		fout.open(path, fstream::out);
		if (!fout.is_open())
		{
			throw FileEx("Помилка при запису до файлу даних Екзамену!\n", path);
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
		cout<<"Файл: "<<ex.WhatFile()<<" "<< ex.what();
	}
	fout.close();
}

ostream& operator<<(ostream& out, Exam& other)
{
	out << "Прізвище студента: " << other.surnameS << endl;
	out << "Ім'я студента: " << other.nameS << endl;
	out << "Група: " << other.group << endl;
	out << "Прізвище викладача: " << other.surnameT << endl;
	out << "Ім'я викладача: "; out << other.nameT << endl;
	out << "Посада викладача: "; out << other.position << endl;
	out << "Назва дисципліни: "; out << other.subject << endl;
	out << "Кількість годин для вивчення: "; out << other.hours << endl;
	out << "Дата екзамену: \n" << "День: "; out << other.data.day << endl;
	out << "Місяць: "; out << other.data.month << endl;
	out<< "Рік: "; out << other.data.year << endl;
	out << "Оцінка: "; out << other.grade << endl;
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
