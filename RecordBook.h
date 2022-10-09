#pragma once
#include "Header.h"
#include "Exam.h"
#include "Printer.h"
#include "FileEx.h"
extern void StartProgramm();
extern void CheckChoice(int& choice, int min, int max);
extern void CheckChoice(int& choice, int min);

template<typename T>
class RecordBook
{
protected:
	T* arr; // �������� �� ����� �������� �����
	int size; // ������� ��������
	int maxSize; //������, ������������ ����� ������
private:
	void FreeMemory()
	{
		delete[]arr;
	}
public:
	// ����������� ����
	class iter
	{
	protected:
		T* i; 
	public:
		explicit iter(T* i1 = 0): i(i1) { } // ����������� �����������
		iter(const iter& x) : i(x.i) { } // ����������� ���������
		iter& operator=(const iter& x) { i = x.i; return *this; };
		T& operator*() const { return *i; };
		iter& operator++ () { ++i; return *this; };
		bool operator!=(const iter& x)const { return i != x.i; }
		friend int operator-(const iter& x, const iter& y) { return x.i - y.i; }
	};
	iter begin() { return iter(arr); }
	iter end() { return iter(arr + size); }
	
	
	RecordBook(int n)
	{
		size = 0;
		arr = new T[ n];
		maxSize = n;
		for (iter i = begin(); i != end(); ++i) 
			*i = arr[i - begin()];

	}
	RecordBook(const RecordBook& a)   //����������� ��������� ��������� 
	{
		if (this != a)
		{
			this->maxSize = a.maxSize;
			this->size = a.size;
			arr = new T[size];
			for (iter i = begin(); i != end(); ++i) 
				*i = a.arr[i - begin()];
		}
		else
			return 0;
	}
	RecordBook& operator=(const RecordBook& a)
	{
		if (this != a)
		{
			delete[]arr;
			this->maxSize = a.maxSize;
			this->size = a.size;
			arr = new T[size];
			for (iter i = begin(); i != end(); ++i) 
				*i = a.arr[i - begin()];
		}
		return *this;
	}

	T& operator[](int index)
	{
		return arr[index];
	};

	~RecordBook()
	{
		this->FreeMemory();
		//cout << "�������� ���������� ������� ������!\n";
	};

	bool Is_empty()
	{
		if (size == 0)
			return true;
		else
			return false;
	};

	int Size()
	{
		return size;
	};

	int Capacity()
	{
		return maxSize;
	};

	void Reserve(int N)    //N-������� ��������, �� ������� ������ �� ������
	{
		if (N <= maxSize)
		{
			size = N;
		}
		else
		{
			maxSize = N;
			T* temp = new T[maxSize];

			for (int i = 0; i < size; i++)
			{
				temp[i] = arr[i];
			}
			this->FreeMemory();
			arr = temp;
			size = N;
		}
		cout << "������� ������ ��������!\n";
	}

	void Add(T &value)          //����� - ������ � ����� �������
	{
		if (size == maxSize)
		{
			maxSize *= 2;
			T* temp = new T[maxSize];

			for (int i = 0;i < size;i++)
			{
				temp[i] = arr[i];
			}

			this->FreeMemory();
			arr = temp;
		}
		arr[size] = value;
		size++;
	}

	void Delete()
	{
		try
		{
			if (size == 0 && maxSize == 1)
			{
				throw exception
				("������� ������ �������, ��������� ��������� � ����!\n");
			}
			else
			{
				size--;
			}
		}
		catch (exception& ex)
		{
			cout << ex.what() << endl;
		}
		cout << "������� ������ ��������!\n";
	};

	void OutPut()
	{
		int kol{};
		for (iter i = begin(); i != end(); ++i)
		{
			cout << "������� �" << kol << " :" << endl;
			cout << *i;
			kol++;
		}
		cout << endl;
	};
	
	void Manually()
	{
		for (int i = 0; i < size; ++i)
		{
			//cin >> arr[i]; //��� ����� ���������� ������
			cin.ignore();  //������ ����� ������ ��� ������ ��������
			cout << "������� �" << i << endl;
			arr[i].InPut();  //��� ����� ������ ��������
		}
	};

	void FromFile(string path)
	{
		fstream fin;
		try
		{
			fin.open(path, fstream::in);
			if (!fin.is_open())
			{
				throw FileEx("�� ����!\n", path);
			}
			cout << "���� �����!\n\n";
			if (fin.peek()==EOF) //� ��� ���� ������ � ����� �����, �� ���������� ����������
			{
				throw FileEx
				("���� ���������� ����� ��� ���������� ������!\n", path);
			}
			while(!fin.eof())
			for (iter i = begin(); i != end(); ++i)
			{
				fin >> (*i);
				if (fin.eof())
				{
					break;
				}
			}
			OutPut();
		}
		catch (FileEx &ex)
		{
			cout << "����: " << ex.WhatFile() << " ��� �������: " << ex.what() << endl;
		}
		fin.close();
	};

	void ToFile(string path)
	{
		fstream fout;
		try
		{
			fout.open(path, fstream::out);
			if (!fout)
			{
				throw FileEx
				("C����� ������ ������� ������ �� �����!\n",path);
			}
			cout << "���� �����!\n";
			for (iter i = begin(); i != end(); ++i)
			{
				fout << (*i);
			}
			cout << "��� ������ ������� �� �����!\n";
		}
		catch (FileEx& ex)
		{
			cout << "����: " << ex.WhatFile() << " ��� �������: " << ex.what() << endl;
		}
		fout.close();
	};

	void Edit(int number)
	{
		cout << "���a���, �� ������� ����������: " << number << endl;
		Printer object;
		Person* pa = &(this->arr[number]); 
		object.Printing(pa);          //���������� ����� ��������
		cout << "������� �� ������� ����������:\n" 
			<< "(1)������� ��������\n"
			<< "(2)��'� ��������\n"
			<< "(3)����� ��������\n"
			<< "(4)������� ���������\n"
			<< "(5)��'� ���������\n"
			<< "(6)������ ���������\n"
			<< "(7)����� ���������\n"
			<< "(8)ʳ������ ����� ��� ��������\n"
			<< "(9)���� ��������\n"
			<< "(10)������\n"
			<< "(11)���� �������\n"
			<< "(0)��������� �����������\n";
		enum MyEnum  
			//������������� ��� ���������� ��������� ��� ���� �����
			//��������������� ������ �����
		{
			defolt,surnameS,nameS,group,
			surnameT,nameT,position,nameExam,hours,date,grade,
			allExam
		};
		int choice3{}; bool flag2{ 1 }; int choice4{}; bool flag3{ 1 };
		//���� ��� �����'���������� ������
		string temp1; int temp2, day2, month2, year2; double temp3;
		while (flag2)
		{
			cout << "������� �� ������� ����������:\n";
			cin >> choice3;
			CheckChoice(choice3, 0, 11);
			switch (choice3)
			{
			case MyEnum::surnameS:
				cout << "������� ��������: " 
					<< arr[number].Exam::GetSurnameS()<< endl;
				cout << "������ ������� ���:\n"; cin.ignore();
				getline(cin, temp1); arr[number].Exam::SetSurnameS(temp1);
				break;
			case MyEnum::nameS:
				cout << "������� ��������: " 
					<< arr[number].Exam::GetNameS() << endl;
				cout << "������ ������� ���:\n"; cin.ignore();
				getline(cin, temp1); arr[number].Exam::SetNameS(temp1);
				break;
			case MyEnum::group:
				cout << "������� ��������: "
					<< arr[number].Exam::GetGroup() << endl;
				cout << "������ ������� ���:\n"; cin.ignore();
				getline(cin, temp1); arr[number].Exam::SetGroup(temp1);
				break;
			case MyEnum::surnameT:
				cout << "������� ��������: " 
					<< arr[number].Exam::GetSurnameT() << endl;
				cout << "������ ������� ���:\n"; cin.ignore();
				getline(cin, temp1); arr[number].Exam::SetSurnameT(temp1);
				break;
			case MyEnum::nameT:
				cout << "������� ��������: " 
					<< arr[number].Exam::GetNameT() << endl;
				cout << "������ ������� ���:\n"; cin.ignore();
				getline(cin, temp1); arr[number].Exam::SetNameT(temp1);
				break;
			case MyEnum::position:
				cout << "������� ��������: "
					<< arr[number].Exam::GetPosition() << endl;
				cout << "������ ������� ���: \n"; cin.ignore();
				getline(cin, temp1); arr[number].Exam::SetPosition(temp1);
				break;
			case MyEnum::nameExam:
				cout << "������� ��������: " 
					<< arr[number].Exam::GetSubject() << endl;
				cout << "������ ������� ���:\n"; cin.ignore();
				getline(cin, temp1); arr[number].Exam::SetSubject(temp1);
				break;
			case MyEnum::hours:
				cout << "������� ��������: " 
					<< arr[number].Exam::GetHours() << endl;
				cout << "������ ������� ���:" << endl;
				cin >> temp2; CheckChoice(temp2, 0);
				arr[number].Exam::SetHours(temp2);
				break;
			case MyEnum::date:
			{
				cout << arr[number].Exam::GetDate() << endl;
				cout << "����� ����������:\n"
					<< "(1)����\n(2)̳����\n(3)г�\n(4)��� ����\n"
					<< "(0)����������� � ����������� ��������\n";
				while (flag3)
				{
					cout << "������, �� ���� ������� ����������� � ���:\n";
					cin >> choice4;
					CheckChoice(choice4, 0, 4);
					switch (choice4)
					{
					case 1:
						cout << "������ ��������� ����:\n";
						cin >> day2;
						CheckChoice(day2, 0, 30);
						arr[number].Exam::SetDay(day2);
						cout << "���� ������ �������!\n";
						break;
					case 2:
						cout << "������ ��������� �����:\n";
						cin >> month2;
						CheckChoice(month2, 0, 12);
						arr[number].Exam::SetMonth(month2);
						cout << "̳���� ������ �������!\n";
						break;
					case 3:
						cout << "������ ��������� ��:\n";
						cin >> year2;
						CheckChoice(year2, 0);
						arr[number].Exam::SetYear(year2);
						cout << "г� ������ �������!\n";
						break;
					case 4:
						cout << "������ �������� ����:\n";
						cin >> day2;
						CheckChoice(day2, 0, 30);
						cin >> month2;
						CheckChoice(month2, 0, 12);
						cin >> year2;
						CheckChoice(year2, 0);
						arr[number].Exam::SetDate(day2, month2, year2); break;
					default:
						flag3 = 0; break;
					}
				}break;
			case MyEnum::grade:
				cout << "������� ��������: " 
					<< arr[number].Exam::GetGrade() << endl;
				cout << "������ ������� ���:\n"; cin.ignore(); cin >> temp3;
				while (temp3 > 100 || temp3 < 0)
				{
					cout << "������ ������ � ������� �� 0 �� 100!\n";
					cin >> temp3;
				};
				arr[number].Exam::SetGrade(temp3);
				break;
			case MyEnum::allExam:
				cout << "�������, �� �� ������:\n" << arr[number]
					<< "-------------------------\n"
					<< "������ ������� ���:\n"; cin.ignore();
				arr[number].Exam::InPut(); break;
			case 0: flag2 = 0; StartProgramm();
				break;
			default: break;
			}
			}
			cout << "��� ������ �������!\n";
		}
	}

	void SearchStud()
	{
		string prizv, im; int mark{};
		cout << "������ ������� ��������:\n";
		cin >> prizv;
		cout << "������ ��'� ��������:\n";
		cin >> im;
		cout << "���������� ��������� ������ �������� "
			<< prizv << " " << im << endl;
		for (iter i = begin(); i != end(); ++i)
		{
			if ((*i).GetSurnameS() == prizv && (*i).GetNameS() == im)
			{
				cout << (*i).GetSubject() << "\t" << (*i).GetGrade() << endl;
				mark++;
			}
		}
		if (!mark)
		{
			cout << "����� ��� ������ �������� � ������� ������ ����!\n";
		}
	};

	void SearchTeach()
	{
		string prizv, im; int mark{};
		cout << "������ ������� ���������:\n";
		cin >> prizv;
		cout << "������ ��'� ���������:\n";
		cin >> im;
		cout << "���������� ��������� ������ � ��������� "
			<< prizv << " " << im << endl;
		for (iter i = begin(); i != end(); ++i)
		{
			if ((*i).GetSurnameT() == prizv && (*i).GetNameT() == im)
			{
				cout << (*i).GetSurnameS() << "\t"
					<< (*i).GetNameS() << "\t"
					<< (*i).GetGrade() << endl;
				mark++;
			}
		}
		if (!mark)
		{
			cout << "����� ��� ������ ��������� � ������� ������ ����!\n";
		}
	};

	void SearchEx()
	{
		string dis; int mark{}; double grades{}, sr{};
		cout << "������ ���������:\n"; cin.ignore();
		getline(cin, dis);
		cout << "���������� ��������� ������ � ��������� " << dis << endl;
		for (iter i = begin(); i != end(); ++i)
		{
			if ((*i).GetSubject() == dis)
			{
				cout << (*i).GetSurnameS() << " " 
					<< (*i).GetNameS() << "\t" 
					<< (*i).GetGrade() << endl;
				mark++;    //�-�� ��������� ��������
				grades += (*i).GetGrade();  //���� ������
			}
		}
		if (mark)
		{
			sr = grades / mark;
			cout << "������� ��������� �� ���������� " << dis << " :" << sr << endl;
		}
		else
		{
			cout << "����� ��� ���� ��������� � ������� ������ ����!\n";
		}

	};

	void RateEx()
	{
		for (iter i = begin(); i != end(); ++i)
		{
			for (iter j = i; j !=end(); ++j)
			{
				if ((*i).GetGrade() < (*j).GetGrade())
				{
					T tmp = *i;
					*i = *j;
					*j = tmp;
				}
			}
		}
		cout << "������� ��������:\n";
		for (iter i = begin(); i != end(); ++i)
		{
			cout<< setw(12) << (*i).GetSurnameS()
				<< setw(8) << (*i).GetGrade() << endl;
		}
	}
};
