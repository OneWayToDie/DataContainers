#include<iostream>
using namespace std;

#define tab "\t"


	class Element
	{
		int Data;
		Element* pNext;
		Element* pPrev;	//предыдущий элемент
		
	public:
		Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr)
		{
			this->Data = Data;
			this->pNext = pNext;
			this->pPrev = pPrev;
			cout << "EConstructor:\t" << this << endl;
		}
		~Element()
		{
			cout << "EDestructor:\t" << this << endl;
		}
		friend class ForwardList;
	};

	class ForwardList
	{
		Element* Head;
		Element* Tail;	//Хвост
		//int SIZE;
	public:
		ForwardList()
		{
			//Конструктор по умолчанию - создаёт пустой список
			Head = nullptr; //Если список пуст, то его голова указывает на ноль
			Tail = nullptr;
			cout << "FLConstructor:\t" << this << endl;
		}
		~ForwardList()
		{
			cout << "FLDestructor:\t" << this << endl;
		}

		//		Adding elements:
		void push_front(int Data)
		{
			//1)Создаём элемент и сохраняем в него добавляемое значение:
			Element* New = new Element(Data);

			//2)Привязываем новый, созданный элемент к началу списка
			New->pNext = Head;

			//3) Переносим голову на новый элемент (Отправляем новый элемент в голову):
			Head = New;
			//SIZE++;
		}

		void push_back(int Data)
		{
			Element* New = new Element(Data);
			//обновляем показатели хвоста и нового элемента
			if (Tail)
			{
				Tail->pNext = New;
				New->pPrev = Tail;
				Tail = New;
			}
			else
			{
				Head = Tail = New;		//Если список пуст - устанавливаем новый элемент как голову и хвост
			}
			//SIZE++;
		}
		void Insert(int Index, int Data)
		{
			//if (Index > SIZE)
			//{
			//	cout << "Index out of range" << endl;
			//}
			if (Index == 0)
			{
				push_front(Data);
			}
			//else if (Index == SIZE)
			//{
			//	push_back(Data);
			//}
			else
			{
				Element* place = Head;
				for (int i = 0; i < Index; i++)
				{
					place = place->pNext;
				}
				Element* New = new Element(Data);
				New->pPrev = place->pPrev;
				New->pNext = place;
				place->pPrev->pNext = New;
				place->pPrev = New;
				//SIZE++;
			}
		}

		void pop_front()
		{
			if (Head == nullptr)
			{
				cout << "Список пуст, заполните его для начала." << endl;
			}
			//Если элемент хвоста совпадает с элементом головы
			if (Head == Tail)
			{
				delete Head;
				Head = nullptr;
				Tail = nullptr;
			}
			//Удаляем элемент из начала списка
			Element* New_Delete = Head;	//Приравниваем новый элемент с головой
			Head = Head->pNext;	//Даём голове адрес следующего элемента
			Head->pPrev = nullptr;	//Обновляем указатель головы
			delete New_Delete;	//Удаляем элемент
		}
		void pop_back()
		{
			if (Head == nullptr)
			{
				cout << "Список пуст, заполните его для начала." << endl;
			}
			if (Head == Tail)
			{
				delete Head;
				Head = nullptr;
				Tail = nullptr;
			}
			Element* New_Delete = Tail;
			Tail = Tail->pPrev;
			Tail->pNext = nullptr;
			delete New_Delete;
		}
		void print()const
		{
			Element* Temp = Head;	// Temp - это итератор.
			//Итератор - это указатель, при помощи которого можно перебирать элементы структуры данных.
			while (Temp)
			{
				cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
				Temp = Temp->pNext;
			}
		}
	};



void main()
{
	setlocale(LC_ALL, "");
	cout << "ForwardList" << endl;
	int n;
	cout << "Введите размер списка: "; cin >> n;
	ForwardList list;
	
	for (int i = 0; i < n; i++)
	{
		//list.push_front(rand() % 100);
		list.push_back(rand() % 100);
	}
	//list.Insert(0, 216);
	//list.Insert(3, 222);
	list.print();
	list.pop_front();
	list.print();
	list.pop_back();
	list.print();
}