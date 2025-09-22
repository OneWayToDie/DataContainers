#include<iostream>
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"

//#define ELEVATOR
//#define FACTORIAL
#define FIBONACHI
//#define PowerRangersGoAhead

void elevator(int floor);
int factorial(int number);
int fibonachi(int number_1, int number_2, int cnt);
int powerr(int number, int degree);

void main()
{
	setlocale(LC_ALL, "");
#ifdef ELEVATOR
	int n;
	cout << "Введите номер этажа: "; cin >> n;
	elevator(n);
	//cout << "Recursion";
	main();
#endif // ELEVATOR

#ifdef FACTORIAL
	int n; cout << "Введите факториал числа: "; cin >> n;
	int result = factorial(n);
	cout << "Факториал числа " << n << " - " << result << endl;
	main();
#endif // FACTORIAL

#ifdef FIBONACHI
	int n; cout << "Введите количество чисел ряда Фибоначи: "; cin >> n;
	if(n >= 5) cout << "Ряд чисел Фибоначи до указанного предела в " << n << " чисел - \t";
	if(n < 5 && n > 1) cout << "Ряд чисел Фибоначи до указанного предела в " << n << " числа - \t";
	if(n == 1) cout << "Это не ряд, а ты дурак, иди в наряд - \t";
	if (n == 0) cout << "Вы попали в джокушку ловушкера";
	if (n > 46) n = 46;
	int result = fibonachi(1,1,n); cout << endl;
	main();
#endif // FIBONACHI

#ifdef PowerRangersGoAhead
	int number; cout << "Введите число: "; cin >> number;
	int degree; cout << "Введите степень: "; cin >> degree;
	int result = powerr(number, degree);
	cout << "Результат возведения в степень - " << result << endl;
	main();
#endif // PowerRangersGoAhead
}

void elevator(int floor)
{
	if (floor == 0)
	{
		cout << "Вы в подвале" << endl;
		return;
	}
	cout << "Вы на " << floor << " этаже" << endl;
	//elevator(floor-1);
	//cout << "Вы на " << floor << " этаже" << endl;
}

int factorial(int number)
{
	if (number == 0) return 1;
	return number * factorial(number - 1);
}

int fibonachi(int number_1, int number_2, int cnt)
{
	if (cnt == 0) return 0;
	cout << number_1 << tab;
	return fibonachi(number_2, number_1 + number_2, cnt - 1);
}

int powerr(int number, int degree)
{
	if (degree == 0) return 1;
	return number * powerr(number, degree - 1);
}

//fibonachi, power(возведение в степень), factorial