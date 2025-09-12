#include<iostream>
using namespace std;

#define tab "\t"
#define delimiter "\n----------------------------------------------------------------------\n"


class Element
{
	int Data;
	Element* pNext;
	Element* pPrev;	//предыдущий элемент
	static int count;
public:
	Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr)
	{
		this->Data = Data;
		this->pNext = pNext;
		this->pPrev = pPrev;
		count++;
#ifdef DEBUG
		cout << "EConstructor:\t" << this << endl;
#endif // DEBUG

	}
	~Element()
	{
		count--;
#ifdef DEBUG
		cout << "EDestructor:\t" << this << endl;
#endif // DEBUG

	}
	friend class List;
	friend List operator+(const List& left, const List& right);
};
int Element::count = 0;


class List
{
	Element* Head;
	Element* Tail;	//Хвост
	size_t size;
public:
	Element* get_Head()const
	{
		return Head;
	}
	Element* get_Tail()const
	{
		return Tail;
	}
	size_t get_size()const
	{
		return size;
	}
	List()
	{
		//Конструктор по умолчанию - создаёт пустой список
		Head = nullptr; //Если список пуст, то его голова указывает на ноль
		Tail = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	List(int size) :List()
	{
		while (size--)push_front(0);
		cout << "LSizeConstructor:\t" << this << endl;
	}
	List(const List& other) :List()
	{
		*this = other;
		cout << "LCopyConstructor:\t" << this << endl;
	}
	~List()
	{
		while (Head)
		{
			delete exchange(Head, Head->pNext);
		}
		cout << "LDestructor:\t" << this << endl;
	}
	//				Operators:
	List& operator=(const List& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_front(Temp->Data);
		cout << "FLCopyAssignment:\t" << this << endl;
		return *this;
	}

	//		Adding elements:
	void push_front(int Data)
	{
		Element* New = new Element(Data);
		New->pNext = Head;
		if (Head != NULL)Head->pPrev = New;
		if (Tail == nullptr)Tail = New;
		Head = New;
		size++;
	}

	void push_back(int Data)
	{
		Element* New = new Element(Data);
		//обновляем показатели хвоста и нового элемента
		//if (Tail)
		//{
		//	Tail->pNext = New;
		//	New->pPrev = Tail;
		//	Tail = New;
		//}
		//else
		//{
		//	Head = Tail = New;		//Если список пуст - устанавливаем новый элемент как голову и хвост
		//}
		New->pPrev = Tail;
		if (Tail != nullptr)Tail->pNext = New;
		if (Head == nullptr)Head = New;
		Tail = New;
		size++;
	}
	void Insert(int Index, int Data)
	{
		if (Index == 0)
		{
			return push_front(Data);
		}
		if (Index >= size)
		{
			return push_back(Data);
		}
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
		}
		size++;
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
		size--;
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
		size--;
	}
	void print()const
	{
		Element* Temp = Head;
		while (Temp)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;
		}
	}
	friend List operator+(const List& left, const List& right);
};
List operator+(const List& left, const List& right)
{
	List fusion;
	for (Element* Temp = left.get_Head(); Temp; Temp = Temp->pNext)
		fusion.push_front(Temp->Data);
	for (Element* Temp = right.get_Head(); Temp; Temp = Temp->pNext)
		fusion.push_front(Temp->Data);
	return fusion;
}

#define BASE_CHECK
//#define OPERATOR_PLUS_CHECK

void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	cout << "ForwardList" << endl;
	int n;
	cout << "Введите размер списка: "; cin >> n;
	List list;

	for (int i = 0; i < n; i++)
	{
		//list.push_front(rand() % 100);
		list.push_back(rand() % 100);
	}
	list.print();
	list.pop_front();
	list.print();
	list.pop_back();
	list.print();
	//list.Insert(5,5);
	//list.print();
#endif // BASE_CHECK

#ifdef OPERATOR_PLUS_CHECK
	List list1;
	list1.push_back(0);
	list1.push_back(1);
	list1.push_back(1);
	list1.push_back(2);
	list1.print();

	List list2;
	list2.push_back(3);
	list2.push_back(5);
	list2.push_back(8);
	list2.push_back(13);
	list2.push_back(21);
	list2.push_back(34);
	list2.push_back(55);
	list2.push_back(89);
	list2.print();

	List list3;
	cout << delimiter << endl;
	list3 = list1 + list2;	
	cout << delimiter << endl;
	list3.print();
#endif // OPERATOR_PLUS_CHECK
	
}