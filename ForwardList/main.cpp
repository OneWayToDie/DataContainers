#include<iostream>
using namespace std;

#define tab "\t"


	class Element
	{
		int Data;
		Element* pNext;
		static int count;
	public:
		Element(int Data, Element* pNext = nullptr)
		{
			this->Data = Data;
			this->pNext = pNext;
			count++;
			cout << "EConstructor:\t" << this << endl;
		}
		~Element()
		{
			count--;
			cout << "EDestructor:\t" << this << endl;
		}
		friend class ForwardList;
	};
	int Element::count = 0;



	class ForwardList
	{
		Element* Head;
	public:
		ForwardList()
		{
			//Конструктор по умолчанию - создаёт пустой список
			Head = nullptr; //Если список пуст, то его голова указывает на ноль

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
		}

		void push_back(int Data)
		{
			if (Head == nullptr)
			{
				return push_front(Data);
			}
			Element* New = new Element(Data);

			Element* Temp = Head;

			while (Temp->pNext)Temp = Temp->pNext;
			
			Temp->pNext = New;
		}
		void Insert(int Index, int Data)
		{
			if (Index == 0) return push_front(Data);
			if (Index >= Element::count)return push_back(Data);
			//1) Доходим до нужного элемента (элемент перед добавляемым)
			Element* Temp = Head;
			for (int i = 0; i < Index-1; i++)Temp = Temp->pNext;

			//2) Создаём добавляемый элемент
			Element* New = new Element(Data);

			//3) Пристыковываем новый элемент к его следуюущему элементу:
			New->pNext = Temp->pNext;

			//4) Пристыковываем предыдущий элемент к нововму:
			Temp->pNext = New;
		}
		//						Removing elements:
		void pop_front()
		{
			//1) Запоминаем адрес удаляемого элемента:
			Element* Erased = Head;
			//2) Исключаем удаляемый элемент из списка:
			Head = Head->pNext;
			//3) Удаляем удаляемый элемент из памяти:
			delete Erased;
		}
		void pop_back()
		{
			Element* Temp = Head;
			while (Temp->pNext->pNext != nullptr)Temp = Temp->pNext;
			delete Temp->pNext;
			Temp->pNext = nullptr;
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
			// Temp; - указатель 'Temp'
			// Temp->...; - Элемент 'Temp'
		}
	};

//#define BASE_CHECK

void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	cout << "ForwardList" << endl;
	int n;
	cout << "Введите размер списка: "; cin >> n;
	ForwardList list;
	
	for (int i = 0; i < n; i++)
	{
		//list.push_front(rand() % 100);
		list.push_back(rand() % 100);
	}
	list.push_back(123);
	list.print();
	list.pop_front();
	list.print();
	list.pop_back();
	list.print();
	int index;
	int value;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	list.Insert(index, value);
	list.print();
#endif

	ForwardList list1;
	list1.push_back(0);
	list1.push_back(1);
	list1.push_back(1);
	list1.push_back(2);
	list1.print();

	ForwardList list2;
	list2.push_back(3);
	list2.push_back(5);
	list2.push_back(8);
	list2.push_back(13);
	list2.push_back(21);
	list2.push_back(34);
	list2.push_back(55);
	list2.push_back(89);
	list2.print();

	int index;
	int value;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	list1.Insert(value, index);
	list1.print();
}