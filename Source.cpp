#include "Exam.h"
#include "Printer.h"
#include "RecordBook.h"
#define T Exam
//#define path "File.txt"

int amount = 2;  //одразу створюю вектор на 2 елемента
RecordBook<T>a(amount);  //створений вектор - сама залікова книжка

void StartProgramm();
//перевантажені функції для перевірки вводу користувача
void CheckChoice(int &choice, int min, int max);
void CheckChoice(int &choice, int min);
//функції меню
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
	cout << "Вас вітає програма Залікова книжка!\n";
	StartProgramm();
}

void StartProgramm()
{
	int choice{}; bool flag{ 1 };
	while (flag)
	{
		cout << "\nОберіть дію :\n"
			<< "1. Створити залікову книжку\n"
			<< "2. Роздрукувати залікову книжку\n"
			<< "3. Відредагувати створену залікову книжку\n"
			<< "4. Додати екзамен до залікової книжки\n"
			<< "5. Видалити екзамен з залікової книжки\n"
			<< "6. Записати дані залікової книжки у файл\n"
			<< "7. Вивести дані про складання іспитів студента\n"
			<< "8. Вивести дані про складання іспитів у викладача\n"
			<< "9. Вивести дані про складання іспитів з дисципліни\n"
			<< "10. Створити рейтинг студентів за результами складання іспитів\n"
			<< "0. Вийти з програми\n";
		cin >> choice;
		CheckChoice(choice, 0, 10);//проверка выбора на корректность
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
//перевірка вводу користувача
void CheckChoice(int& choice, int min, int max)
{
	while (cin.fail() || choice < min || choice > max)
		// если предыдущее извлечение было неудачным, то обрабатывем эту ситуацию
	{
		if (choice < min || choice > max)
		{
			cout << "Введіть число у діпазоні від " << min << " до " << max << "!\n";
			cin >> choice;
		}
		else
		{
			cout << "Введіть число, а не символ!\n";
			cin.clear(); // то возвращаем cin в 'обычный' режим работы
			cin.ignore(); // и удаляем значения предыдущего ввода из входного буфера
			cin >> choice;
		}
	}
}
void CheckChoice(int& choice, int min)
//перегруженная проверка для варианта, где значение должно быть не в диапазоне,
//а больше какого-то значения
{
	while (cin.fail() || choice < 0)
	{
		if (choice < 0)
		{
			cout << "Введіть число більше " << min << " !\n";
			cin >> choice;
		}
		else
		{
			cout << "Введіть число, а не символ!\n";
			cin.clear();
			cin.ignore();
			cin >> choice;
		}
	}
}

//функція створення книжки
void CreateRB()
{
	if(amount == 2)
	{
		cout << "Введіть кількість екзаменів у заліковій книжці\n";
		cin >> amount;
		CheckChoice(amount, 0);  //проверка количества экзаменов
		a.Reserve(amount);
		cout << "Оберіть у який спосіб залікова книжка буде заповнена\n"
			<< "(1) Вручну \n"
			<< "(2) Зчитати дані з файлу\n";
		int choice2; 
		cin >> choice2;
		CheckChoice(choice2, 0, 2);  //проверка выбора 2
		string path;
		switch (choice2)
		{
		case 1:a.Manually(); a.OutPut(); break;
		case 2: cout << "Введіть файл, з якого зчитати інформацію:\n";cin >> path;
		 a.FromFile(path); break;
		default:break;
		}
	}
	else
	{
		cout << "У вас уже є залікова книжка!\n";
	}
}

//функція друку книжки
void PrintRB(RecordBook<T>& a)
{
	if (a.Is_empty())
	{
		cout << "У вас ще немає залікової книжки або вона порожня!\n";
	}
	else
	{
		a.OutPut();
	}
}

//функція редагування книжки
void EditRB(RecordBook<T>& a)
{
	if (a.Is_empty())
	{
		cout << "У вас ще немає залікової книжки або вона порожня!\n";
	}
	else
	{
		cout << "Оберіть номер екзамену, який треба редагувати\n";
		int number{}; cin >> number;
		CheckChoice(number, 0, a.Size() - 1);
		if (a.Size() == 1)
		{
			while (number != 0)
			{
				cout << "Залікова книжка має лише 1 екзамен,введіть інший номер!\n ";
				cin >> number;
			}
		}
		a.Edit(number);
	}
}

//функція додавання екзамену до книжки
void AddToRB(RecordBook<T>& a)
{
	if (a.Is_empty())
	{
		cout << "У вас ще немає залікової книжки або вона порожня!\n";
	}
	else
	{
		cout << "Введіть екзамен:\n";
		Exam b;
		cin.ignore();
		b.InPut();
		a.Add(b);
	}
}

//функція видалення екзамену з книжки
void DeleteFromRB(RecordBook<T>& a)
{
	if (a.Is_empty())
	{
		cout << "У вас ще немає залікової книжки або вона порожня!\n";
	}
	else
	{
		a.Delete();
	}
}

//функция запису книжки до файлу
void ToFileRB(RecordBook<T>& a)
{
	if (a.Is_empty())
	{
		cout << "У вас ще немає залікової книжки або вона порожня!\n";
	}
	else
	{
		string path2;
		cout << "Введіть файл, в який треба записати інформацію:\n";
		cin >> path2;
		a.ToFile(path2);
	}
}

//функція пошуку студенту
void StudRB(RecordBook<T>& a)
{
	if (a.Is_empty())
	{
		cout << "У вас ще немає залікової книжки або вона порожня!\n";
	}
	else
	{
		a.SearchStud();
	}
}

//функція пошуку викладача
void TeachRB(RecordBook<T>& a)
{
	if (a.Is_empty())
	{
		cout << "У вас ще немає залікової книжки або вона порожня!\n";
	}
	else
	{
		a.SearchTeach();
	}
}

//функция пошуку дисципліни
void ExamRB(RecordBook<T>& a)
{
	if (a.Is_empty())
	{
		cout << "У вас ще немає залікової книжки або вона порожня!\n";
	}
	else
	{
		a.SearchEx();
	}
}

//функція створення рейтингу
void RateRB(RecordBook<T>& a)
{
	if (a.Is_empty())
	{
		cout << "У вас ще немає залікової книжки або вона порожня!\n";
	}
	else
	{
		a.RateEx();
	}
}

