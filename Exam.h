#pragma once
#include "Student.h"
#include "Teacher.h"
class Exam: public Student, public Teacher
{
protected:
	string subject;
	int hours;
	struct Date 
	{
		int day;
		int month;
		int year;
	}data;
	double grade;
public:
	Exam();
	Exam(string surnameS, string nameS, string group, string surnameT, string nameT, string position, 
		string subject, int hours, int day, int month, int year, double grade);
	Exam(const Exam& other);
	~Exam();

	void OutPut()override;
	void InPut()override;

	void SetSubject(string subject);
	string GetSubject();
	void SetHours(int hours);
	int GetHours();
	void SetDay(int day);
	void SetMonth(int month);
	void SetYear(int year);
	void SetDate(int day, int month, int year);
	string GetDate();
	void SetGrade(double grade);
	double GetGrade();

	friend ostream& operator<<(ostream& out, Exam& other);
	friend istream& operator>>(istream& in, Exam& other);
	void FromFile(string path)override;
	void ToFile(string path)override;
};

