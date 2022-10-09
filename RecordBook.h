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
	T* arr; // вказівник на масив елементів даних
	int size; // кількість елементів
	int maxSize; //ємність, максимальний розмір масиву
private:
	void FreeMemory()
	{
		delete[]arr;
	}
public:
	// Ітераторний клас
	class iter
	{
	protected:
		T* i; 
	public:
		explicit iter(T* i1 = 0): i(i1) { } // конструктор ініціалізації
		iter(const iter& x) : i(x.i) { } // конструктор копіювання
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
	RecordBook(const RecordBook& a)   //конструктор глибокого копіювання 
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
		//cout << "Визвався деструктор Залікової книжки!\n";
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

	void Reserve(int N)    //N-кількість предметів, що потрібно додати до масиву
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
		cout << "Залікова книжка створена!\n";
	}

	void Add(T &value)          //метод - додати в кінець екзамен
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
				("Залікова книжка порожня, неможливе видалення з кінця!\n");
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
		cout << "Екзамен успішно видалено!\n";
	};

	void OutPut()
	{
		int kol{};
		for (iter i = begin(); i != end(); ++i)
		{
			cout << "Екзамен №" << kol << " :" << endl;
			cout << *i;
			kol++;
		}
		cout << endl;
	};
	
	void Manually()
	{
		for (int i = 0; i < size; ++i)
		{
			//cin >> arr[i]; //для вводу звичайного масиву
			cin.ignore();  //очищую буфер консолі для запису екзамена
			cout << "Екзамен №" << i << endl;
			arr[i].InPut();  //для вводу масиву екзаменів
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
				throw FileEx("Не уснує!\n", path);
			}
			cout << "Файл відрит!\n\n";
			if (fin.peek()==EOF) //у разі якщо символ є кінцем файлу, то викидується виключення
			{
				throw FileEx
				("Немає необхідних даних для заповнення книжки!\n", path);
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
			cout << "Файл: " << ex.WhatFile() << " Тип помилки: " << ex.what() << endl;
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
				("Cпроба запису залікової книжки до файлу!\n",path);
			}
			cout << "Файл відрит!\n";
			for (iter i = begin(); i != end(); ++i)
			{
				fout << (*i);
			}
			cout << "Дані успішно записані до файлу!\n";
		}
		catch (FileEx& ex)
		{
			cout << "Файл: " << ex.WhatFile() << " Тип помилки: " << ex.what() << endl;
		}
		fout.close();
	};

	void Edit(int number)
	{
		cout << "Екзaмен, що потрібно редагувати: " << number << endl;
		Printer object;
		Person* pa = &(this->arr[number]); 
		object.Printing(pa);          //виводиться назва диципліни
		cout << "Виберіть що потрібно редагувати:\n" 
			<< "(1)Прізвище студента\n"
			<< "(2)Ім'я студента\n"
			<< "(3)Групу студента\n"
			<< "(4)Прізвище викладача\n"
			<< "(5)Ім'я викладача\n"
			<< "(6)Посаду викладача\n"
			<< "(7)Назву дисципліни\n"
			<< "(8)Кількість годин для вивчення\n"
			<< "(9)Дату екзамену\n"
			<< "(10)Оцінку\n"
			<< "(11)Весь екзамен\n"
			<< "(0)Завершити редагування\n";
		enum MyEnum  
			//перерахування для запобігання плутаниці при описі кейсів
			//використувується замість чисел
		{
			defolt,surnameS,nameS,group,
			surnameT,nameT,position,nameExam,hours,date,grade,
			allExam
		};
		int choice3{}; bool flag2{ 1 }; int choice4{}; bool flag3{ 1 };
		//змінні для запом'ятовування відповіді
		string temp1; int temp2, day2, month2, year2; double temp3;
		while (flag2)
		{
			cout << "Виберіть що потрібно редагувати:\n";
			cin >> choice3;
			CheckChoice(choice3, 0, 11);
			switch (choice3)
			{
			case MyEnum::surnameS:
				cout << "Поточне значення: " 
					<< arr[number].Exam::GetSurnameS()<< endl;
				cout << "Введіть оновлені дані:\n"; cin.ignore();
				getline(cin, temp1); arr[number].Exam::SetSurnameS(temp1);
				break;
			case MyEnum::nameS:
				cout << "Поточне значення: " 
					<< arr[number].Exam::GetNameS() << endl;
				cout << "Введіть оновлені дані:\n"; cin.ignore();
				getline(cin, temp1); arr[number].Exam::SetNameS(temp1);
				break;
			case MyEnum::group:
				cout << "Поточне значення: "
					<< arr[number].Exam::GetGroup() << endl;
				cout << "Введіть оновлені дані:\n"; cin.ignore();
				getline(cin, temp1); arr[number].Exam::SetGroup(temp1);
				break;
			case MyEnum::surnameT:
				cout << "Поточне значення: " 
					<< arr[number].Exam::GetSurnameT() << endl;
				cout << "Введіть оновлені дані:\n"; cin.ignore();
				getline(cin, temp1); arr[number].Exam::SetSurnameT(temp1);
				break;
			case MyEnum::nameT:
				cout << "Поточне значення: " 
					<< arr[number].Exam::GetNameT() << endl;
				cout << "Введіть оновлені дані:\n"; cin.ignore();
				getline(cin, temp1); arr[number].Exam::SetNameT(temp1);
				break;
			case MyEnum::position:
				cout << "Поточне значення: "
					<< arr[number].Exam::GetPosition() << endl;
				cout << "Введіть оновлені дані: \n"; cin.ignore();
				getline(cin, temp1); arr[number].Exam::SetPosition(temp1);
				break;
			case MyEnum::nameExam:
				cout << "Поточне значення: " 
					<< arr[number].Exam::GetSubject() << endl;
				cout << "Введіть оновлені дані:\n"; cin.ignore();
				getline(cin, temp1); arr[number].Exam::SetSubject(temp1);
				break;
			case MyEnum::hours:
				cout << "Поточне значення: " 
					<< arr[number].Exam::GetHours() << endl;
				cout << "Введіть оновлені дані:" << endl;
				cin >> temp2; CheckChoice(temp2, 0);
				arr[number].Exam::SetHours(temp2);
				break;
			case MyEnum::date:
			{
				cout << arr[number].Exam::GetDate() << endl;
				cout << "Можна редагувати:\n"
					<< "(1)День\n(2)Місяць\n(3)Рік\n(4)Всю дату\n"
					<< "(0)Повернутися в редагування екзамену\n";
				while (flag3)
				{
					cout << "Оберіть, що саме потребує редагування в даті:\n";
					cin >> choice4;
					CheckChoice(choice4, 0, 4);
					switch (choice4)
					{
					case 1:
						cout << "Введіть оновлений день:\n";
						cin >> day2;
						CheckChoice(day2, 0, 30);
						arr[number].Exam::SetDay(day2);
						cout << "День успішно змінений!\n";
						break;
					case 2:
						cout << "Введіть оновлений місяць:\n";
						cin >> month2;
						CheckChoice(month2, 0, 12);
						arr[number].Exam::SetMonth(month2);
						cout << "Місяць успішно змінений!\n";
						break;
					case 3:
						cout << "Введіть оновлений рік:\n";
						cin >> year2;
						CheckChoice(year2, 0);
						arr[number].Exam::SetYear(year2);
						cout << "Рік успішно змінений!\n";
						break;
					case 4:
						cout << "Введіть оновлену дату:\n";
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
				cout << "Поточне значення: " 
					<< arr[number].Exam::GetGrade() << endl;
				cout << "Введіть оновлені дані:\n"; cin.ignore(); cin >> temp3;
				while (temp3 > 100 || temp3 < 0)
				{
					cout << "Введіть оцінку в діапазоні від 0 до 100!\n";
					cin >> temp3;
				};
				arr[number].Exam::SetGrade(temp3);
				break;
			case MyEnum::allExam:
				cout << "Екзамен, що ви обрали:\n" << arr[number]
					<< "-------------------------\n"
					<< "Введіть оновлені дані:\n"; cin.ignore();
				arr[number].Exam::InPut(); break;
			case 0: flag2 = 0; StartProgramm();
				break;
			default: break;
			}
			}
			cout << "Дані успішно записані!\n";
		}
	}

	void SearchStud()
	{
		string prizv, im; int mark{};
		cout << "Введіть прізвище студента:\n";
		cin >> prizv;
		cout << "Введіть ім'я студента:\n";
		cin >> im;
		cout << "Результати складання іспитів студента "
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
			cout << "Даних про такого студента у заліковій книжці немає!\n";
		}
	};

	void SearchTeach()
	{
		string prizv, im; int mark{};
		cout << "Введіть прізвище викладача:\n";
		cin >> prizv;
		cout << "Введіть ім'я викладача:\n";
		cin >> im;
		cout << "Результати складання іспитів у викладача "
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
			cout << "Даних про такого викладача у заліковій книжці немає!\n";
		}
	};

	void SearchEx()
	{
		string dis; int mark{}; double grades{}, sr{};
		cout << "Введіть дисципліну:\n"; cin.ignore();
		getline(cin, dis);
		cout << "Результати складання іспитів з дисципліни " << dis << endl;
		for (iter i = begin(); i != end(); ++i)
		{
			if ((*i).GetSubject() == dis)
			{
				cout << (*i).GetSurnameS() << " " 
					<< (*i).GetNameS() << "\t" 
					<< (*i).GetGrade() << endl;
				mark++;    //к-ть знайдених екзаменів
				grades += (*i).GetGrade();  //сума оцінок
			}
		}
		if (mark)
		{
			sr = grades / mark;
			cout << "Середній результат за дисципліною " << dis << " :" << sr << endl;
		}
		else
		{
			cout << "Даних про таку дисципліну у заліковій книжці немає!\n";
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
		cout << "Рейтинг студентів:\n";
		for (iter i = begin(); i != end(); ++i)
		{
			cout<< setw(12) << (*i).GetSurnameS()
				<< setw(8) << (*i).GetGrade() << endl;
		}
	}
};
