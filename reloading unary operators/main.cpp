#include <iostream>
#include <time.h>
#include <Windows.h>
#include <conio.h>
#include <string.h>
#include <io.h>

using namespace std;

enum Color
{
	Black, Blue, Green, Cyan, Red, Magenta, Brown,
	LightGray, DarkGray, LightBlue, LightGreen, LightCyan, LightRed, LightMagenta, Yellow, White
};
HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
void setColor(Color text, Color background)
{
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}
enum Direction { Up = 72, Left = 75, Right = 77, Down = 80, Enter = 13, Esc = 27 };
void setCursor(int x, int y)
{
	COORD myCoords = { x,y };
	SetConsoleCursorPosition(hStdOut, myCoords);
}

class myDigit
{
	int var1 = 0;
	int var2 = 0;
public:

	myDigit()
	{
		var1 = var2 = 5;
		cout << "ctor\n";
	}

	myDigit(int a, int b)
	{
		setVar1(a); setVar2(b);
		cout << "ctor args\n";
	}

	void setVar1(int v) { var1 = v; }
	void setVar2(int v) { var2 = v; }

	int getVar1()const { return var1; }
	int getVar2()const { return var2; }

	void printDigit()const //помечаем метод, как константный. т.е. как такой, который не вносит изменения в объектв ходе выполнения
	{
		cout << var1 << "\t" << var2 << "\n";
	}
	myDigit& operator=(const myDigit& right)
	{
		cout << "=\n";
		var1 = right.var1;
		var2 = right.var2;
		//копируем содержимое объекта, который прибыл в качестве аргумента, в объект, для которого происходит вызов оператора =
		return *this;
		//возвращаем объект по ссылке, т.к. не хотим производить вызов конструктора копирования.
		//это возможно только в тех случаях, когда объект, который возвращается, продолжает существовать после выхода из метода (функции)
	}
	myDigit operator+(const myDigit& right)
	{
		//для константнoго объекта возможен вызов только константный методов
		cout << "+\n";
		//myDigit result(this->var1 + right.var1, this->var2 + right.var2);
		myDigit result;
		result.var1 = var1 + right.var1;
		result.setVar2(this->var2 + right.getVar2());
		return result;
	}
	//+=
	myDigit& operator+=(const myDigit& right)
	{
		myDigit value;
		value.var1 = var1 + right.var1;
		value.var2 = var2 + right.var2;
		*this = value;
		return *this;
	}
	myDigit(const myDigit& right)
	{
		cout << "COPY!\n";
	}
	~myDigit()
	{
		cout << "delete\n";
	}
};

class MyStr
{
	char* str = nullptr;

public:
	void setMemory(const char* S)
	{
		if (str != nullptr)
		{
			delete[]str;
		}
		int size = strlen(S) + 1;
		str = new char[size];
		strcpy_s(str, size, S);
	}
	char* getStr()const
	{
		return str;
	}
	MyStr()
	{
		setMemory("string");
	}
	MyStr(const char* S)
	{
		setMemory(S);
	}
	~MyStr()
	{
		delete[]str;
	}

	MyStr& operator=(const MyStr& right)
	{
		setMemory(right.str);
		return *this;
	}

	MyStr operator+(const MyStr& right)
	{
		//строка, содержащая результат сложения двух строк
		int size = strlen(this->str) + strlen(right.str) + 1;
		char* res = new char[size];
		strcpy_s(res, size, this->str);
		strcat_s(res, size, right.str);
		MyStr newO(res);
		return newO;
	}

	bool operator==(const MyStr& right)
	{

		if (strlen(this->str) == strlen(right.str))
		{
			for (size_t i = 0; i < strlen(right.str); i++)
			{
				this->str[i] == right.str[i];
			}
			return true;
		}

		return false;

	}

	MyStr operator>(const MyStr& right)
	{
		MyStr any;
		if (strlen(this->str) > strlen(right.str))
		{
			any.setMemory(this->str);
		}
		else
		{
			any.setMemory(right.str);

		}
		for (int i = 0; i < strlen(this->str); i++)
		{
			any.str[i] = tolower(any.str[i]);
		}
		return any;

	}

	MyStr operator<(const MyStr& right)
	{
		MyStr any;
		if (strlen(this->str) < strlen(right.str))
		{
			any.setMemory(this->str);
		}
		else
		{
			any.setMemory(right.str);

		}
		for (int i = 0; i < strlen(this->str); i++)
		{
			any.str[i] = tolower(any.str[i]);
		}
		return any;
	}
};

void main()
{
	setlocale(LC_ALL, "rus");
	srand(time(NULL));

	MyStr obj, obj2("NEW string "), obj3("kU kU"), obj4("kU kU"), result;



	cout << "1 объект: " << endl;
	cout << "\t\t" << obj2.getStr() << endl;
	cout << "2 объект: " << endl;
	cout << "\t\t" << obj3.getStr() << endl;
	cout << "3 объект: " << endl;
	cout << "\t\t" << obj4.getStr() << endl;




	cout << "\n\nДолжен привести к нижнему регистр 1 объект\n";
	obj = obj2 > obj3;
	cout << obj.getStr() << endl;

	cout << "\n\nДолжен привести к нижнему регистр 2 объект\n";
	obj = obj2 < obj3;
	cout << obj.getStr() << endl;

	cout << "\n\nРавны ли строки 2 объекта и 3 объекта: \n";
	if (obj3 == obj4)
	{
		cout << "Yes" << endl;
	}
	else
	{
		cout << "no" << endl;

	}
	cout << "\n\nРавны ли строки 1 объекта и 2 объекта: \n";
	if (obj2 == obj3)
	{
		cout << "Yes" << endl;
	}
	else
	{
		cout << "no" << endl;

	}


}