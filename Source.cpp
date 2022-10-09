#include "Exam.h"
#include "Printer.h"
#include "RecordBook.h"
#define T Exam
//#define path "File.txt"

int amount = 2;  //������ ������� ������ �� 2 ��������
RecordBook<T>a(amount);  //��������� ������ - ���� ������� ������

void StartProgramm();
//������������ ������� ��� �������� ����� �����������
void CheckChoice(int &choice, int min, int max);
void CheckChoice(int &choice, int min);
//������� ����
void CreateRB();
void PrintRB(RecordBook<T>&a);
void EditRB(RecordBook<T>&a);
void AddToRB(RecordBook<T>&a);
void DeleteFromRB(RecordBook<T>& a);
void ToFileRB(RecordBook<T>& a);
void StudRB(RecordBook<T>& a);
void TeachRB(RecordBook<T>& a);
void ExamRB(RecordBook<T>& a);
void RateRB(RecordBook<T>& a);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	cout << "��� ��� �������� ������� ������!\n";
	StartProgramm();
}

void StartProgramm()
{
	int choice{}; bool flag{ 1 };
	while (flag)
	{
		cout << "\n������ �� :\n"
			<< "1. �������� ������� ������\n"
			<< "2. ������������ ������� ������\n"
			<< "3. ³����������� �������� ������� ������\n"
			<< "4. ������ ������� �� ������� ������\n"
			<< "5. �������� ������� � ������� ������\n"
			<< "6. �������� ��� ������� ������ � ����\n"
			<< "7. ������� ��� ��� ��������� ������ ��������\n"
			<< "8. ������� ��� ��� ��������� ������ � ���������\n"
			<< "9. ������� ��� ��� ��������� ������ � ���������\n"
			<< "10. �������� ������� �������� �� ���������� ��������� ������\n"
			<< "0. ����� � ��������\n";
		cin >> choice;
		CheckChoice(choice, 0, 10);//�������� ������ �� ������������
		switch (choice)
		{
		case 1:CreateRB(); break;
		case 2:PrintRB(a); break;
		case 3:EditRB(a); break;
		case 4:AddToRB(a); break;
		case 5:DeleteFromRB(a); break;
		case 6:ToFileRB(a); break;
		case 7:StudRB(a); break;
		case 8:TeachRB(a); break;
		case 9:ExamRB(a); break;
		case 10:RateRB(a); break;
		case 0: exit(0);
		default:flag = 0; break;
		}
	}
}
//�������� ����� �����������
void CheckChoice(int& choice, int min, int max)
{
	while (cin.fail() || choice < min || choice > max)
		// ���� ���������� ���������� ���� ���������, �� ����������� ��� ��������
	{
		if (choice < min || choice > max)
		{
			cout << "������ ����� � ������ �� " << min << " �� " << max << "!\n";
			cin >> choice;
		}
		else
		{
			cout << "������ �����, � �� ������!\n";
			cin.clear(); // �� ���������� cin � '�������' ����� ������
			cin.ignore(); // � ������� �������� ����������� ����� �� �������� ������
			cin >> choice;
		}
	}
}
void CheckChoice(int& choice, int min)
//������������� �������� ��� ��������, ��� �������� ������ ���� �� � ���������,
//� ������ ������-�� ��������
{
	while (cin.fail() || choice < 0)
	{
		if (choice < 0)
		{
			cout << "������ ����� ����� " << min << " !\n";
			cin >> choice;
		}
		else
		{
			cout << "������ �����, � �� ������!\n";
			cin.clear();
			cin.ignore();
			cin >> choice;
		}
	}
}

//������� ��������� ������
void CreateRB()
{
	if(amount == 2)
	{
		cout << "������ ������� �������� � ������� ������\n";
		cin >> amount;
		CheckChoice(amount, 0);  //�������� ���������� ���������
		a.Reserve(amount);
		cout << "������ � ���� ����� ������� ������ ���� ���������\n"
			<< "(1) ������ \n"
			<< "(2) ������� ��� � �����\n";
		int choice2; 
		cin >> choice2;
		CheckChoice(choice2, 0, 2);  //�������� ������ 2
		string path;
		switch (choice2)
		{
		case 1:a.Manually(); a.OutPut(); break;
		case 2: cout << "������ ����, � ����� ������� ����������:\n";cin >> path;
		 a.FromFile(path); break;
		default:break;
		}
	}
	else
	{
		cout << "� ��� ��� � ������� ������!\n";
	}
}

//������� ����� ������
void PrintRB(RecordBook<T>& a)
{
	if (a.Is_empty())
	{
		cout << "� ��� �� ���� ������� ������ ��� ���� �������!\n";
	}
	else
	{
		a.OutPut();
	}
}

//������� ����������� ������
void EditRB(RecordBook<T>& a)
{
	if (a.Is_empty())
	{
		cout << "� ��� �� ���� ������� ������ ��� ���� �������!\n";
	}
	else
	{
		cout << "������ ����� ��������, ���� ����� ����������\n";
		int number{}; cin >> number;
		CheckChoice(number, 0, a.Size() - 1);
		if (a.Size() == 1)
		{
			while (number != 0)
			{
				cout << "������� ������ �� ���� 1 �������,������ ����� �����!\n ";
				cin >> number;
			}
		}
		a.Edit(number);
	}
}

//������� ��������� �������� �� ������
void AddToRB(RecordBook<T>& a)
{
	if (a.Is_empty())
	{
		cout << "� ��� �� ���� ������� ������ ��� ���� �������!\n";
	}
	else
	{
		cout << "������ �������:\n";
		Exam b;
		cin.ignore();
		b.InPut();
		a.Add(b);
	}
}

//������� ��������� �������� � ������
void DeleteFromRB(RecordBook<T>& a)
{
	if (a.Is_empty())
	{
		cout << "� ��� �� ���� ������� ������ ��� ���� �������!\n";
	}
	else
	{
		a.Delete();
	}
}

//������� ������ ������ �� �����
void ToFileRB(RecordBook<T>& a)
{
	if (a.Is_empty())
	{
		cout << "� ��� �� ���� ������� ������ ��� ���� �������!\n";
	}
	else
	{
		string path2;
		cout << "������ ����, � ���� ����� �������� ����������:\n";
		cin >> path2;
		a.ToFile(path2);
	}
}

//������� ������ ��������
void StudRB(RecordBook<T>& a)
{
	if (a.Is_empty())
	{
		cout << "� ��� �� ���� ������� ������ ��� ���� �������!\n";
	}
	else
	{
		a.SearchStud();
	}
}

//������� ������ ���������
void TeachRB(RecordBook<T>& a)
{
	if (a.Is_empty())
	{
		cout << "� ��� �� ���� ������� ������ ��� ���� �������!\n";
	}
	else
	{
		a.SearchTeach();
	}
}

//������� ������ ���������
void ExamRB(RecordBook<T>& a)
{
	if (a.Is_empty())
	{
		cout << "� ��� �� ���� ������� ������ ��� ���� �������!\n";
	}
	else
	{
		a.SearchEx();
	}
}

//������� ��������� ��������
void RateRB(RecordBook<T>& a)
{
	if (a.Is_empty())
	{
		cout << "� ��� �� ���� ������� ������ ��� ���� �������!\n";
	}
	else
	{
		a.RateEx();
	}
}

