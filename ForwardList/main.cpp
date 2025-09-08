#include<iostream>
#include<time.h>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n----------------------------------------------------------------------\n"


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
#ifdef Debug
		cout << "EConstructor:\t" << this << endl;
#endif	//DEBUG
	}
	~Element()
	{
		count--;
#ifdef DEBUG
		cout << "EDestructor:\t" << this << endl;
#endif	//DEBUG
	}
	friend class ForwardList;
	friend ForwardList operator+(const ForwardList& left, const ForwardList& right);
	friend std::ostream& operator<<(std::ostream& os, const ForwardList& obj);
};
int Element::count = 0;


class ForwardList
{
	Element* Head;
	size_t size;	//unsigned int
public:
	Element* get_Head()const
	{
		return Head;
	}
	size_t get_size()const
	{
		return size;
	}
	explicit ForwardList()
	{
		//Конструктор по умолчанию - создаёт пустой список
		Head = nullptr; //Если список пуст, то его голова указывает на ноль
		size = 0;
		cout << "FLConstructor:\t" << this << endl;
	}
	ForwardList(Element* Head)
	{
		for (int i = 0; i < size; i++)
		{
			this->Head[i] = Head[i];
		}
		cout << "FLDefaultConstructor:\t" << this << endl;
	}
	ForwardList(const ForwardList& other):ForwardList()
	{
		//Deep copy (Побитовое копирование):
		*this = other;
		cout << "FLCopyConstructor:\t" << this << endl;
	}	
	~ForwardList()
	{
		clock_t t_start = clock();
		while (Head)pop_front();
		clock_t t_end = clock();
		cout << "FLDestructor:\t" << this << "\tcomplete for " << double(t_end - t_start)/CLOCKS_PER_SEC << endl;
	}
	//		Operators:
	ForwardList& operator=(const ForwardList& other)
	{
		if (this == &other)return *this;		//0) Проверяем, не являются ли 'this' и 'other' одним объектом.
		while (Head)pop_front();				//1) Старое значение объекта удаляется из памяти
		//2)Deep copy (Побитовое копирование):
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_back(Temp->Data);
		cout << "FLCopyAssignment:\t" << this << endl;
		return *this;
	}
	//ForwardList& operator=(ForwardList&& other)
	//{
	//	if (this == &other)return *this;
	//	while (Head)pop_front();
	//	//Shallow copy
	//	for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
	//	{
	//		push_back(Temp->Data);
	//		push_back(other.size);
	//	}
	//	other.Head = nullptr;
	//	other.size = 0;
	//	cout << "FLMoveAssignment:\t\t" << this << endl;
	//	return *this;
	//}
	ForwardList& operator=(ForwardList&& other) noexcept
	{
		if (this == &other) return *this;

		while (Head) pop_front();
		// ShallowCopy
		Head = other.Head;
		size = other.size;

		other.Head = nullptr;
		other.size = 0;

		cout << "FLMoveAssignment:\t\t" << this << endl;
		return *this;
	}
	const Element operator[](int size)const
	{
		Element* Temp = Head;
		for (int i = 0; i < size; i++)Temp = Temp->pNext;
		return Temp->Data;
	}
	Element operator[](int size)
	{
		Element* Temp = Head;
		for (int i = 0; i < size; i++)Temp = Temp->pNext;
		return Temp->Data;
	}
	ForwardList(ForwardList&& other) noexcept
	{
		this->size = other.size;
		this->Head = other.Head;
		other.size = 0;
		other.Head = nullptr;
		cout << "MoveConstructor:\t" << this << endl;
	}
	//		Adding elements:
	void push_front(int Data)
	{
		Head = new Element(Data, Head);
		size++;
	}

	void push_back(int Data)
	{
		if (Head == nullptr)return push_front(Data);
		Element* Temp = Head;
		while (Temp->pNext)Temp = Temp->pNext;
		Temp->pNext = new Element(Data);
		size++;
	}
	void Insert(int Index, int Data)
	{
		if (Index == 0) return push_front(Data);
		if (Index >= size)return push_back(Data);
		Element* Temp = Head;
		for (int i = 0; i < Index-1; i++)Temp = Temp->pNext;
		Temp->pNext = new Element(Data, Temp->pNext);
		size++;
	}
	//						Removing elements:
	void Erase(int Index)
	{
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++)Temp = Temp->pNext;

		Element* Erased = Temp->pNext;
		Temp->pNext = Erased->pNext;
		delete Erased;
		size--;
	}
	void pop_front()
	{
		//1) Запоминаем адрес удаляемого элемента:
		Element* Erased = Head;
		//2) Исключаем удаляемый элемент из списка:
		Head = Head->pNext;
		//3) Удаляем удаляемый элемент из памяти:
		delete Erased;
		size--;
	}
	void pop_back()
	{
		if (!Head || Head->pNext == nullptr)return pop_front();
		Element* Temp = Head;
		while (Temp->pNext->pNext != nullptr)Temp = Temp->pNext;
		delete Temp->pNext;
		Temp->pNext = nullptr;
		size--;
	}
	void print()const
	{
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Количество элементов списка: " << size << endl;
		cout << "Общее количество элементов: " << Element::count << endl;
	}
	friend ForwardList operator+(const ForwardList& left, const ForwardList& right);
	friend std::ostream& operator<<(std::ostream& os, const ForwardList& obj);
};

ForwardList operator+(const ForwardList& left, const ForwardList& right)
{
	ForwardList fusion;
	for (Element* Temp = left.get_Head(); Temp; Temp = Temp->pNext)
		fusion.push_back(Temp->Data);
	for (Element* Temp = right.Head; Temp; Temp = Temp->pNext)
		fusion.push_back(Temp->Data);
	return fusion;
}
std::ostream& operator<<(std::ostream& os, const ForwardList& obj)
{
	return os << obj.get_Head();
}

//#define BASE_CHECK
//#define OPERATOR_PLUS_CHECK
//#define PERFORMANCE_CHECK
//#define trbIndec
#define MOVESEMANTIC_CHECK

void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	//cout << "ForwardList" << endl;
	int n;
	cout << "Введите размер списка: "; cin >> n;
	ForwardList list;

	for (int i = 0; i < n; i++)
	{
		//list.push_front(rand() % 100);
		list.push_back(rand() % 100);
	}
	//list.push_back(123);
	//list.print();
	//list.pop_front();
	//list.print();
	//list.pop_back();
	//list.print();
	//int index;
	//int value;
	//cout << "Введите индекс добавляемого элемента: "; cin >> index;
	//cout << "Введите значение добавляемого элемента: "; cin >> value;
	//list.Insert(index, value);
	//list.print();
	//list.Erase(3);
	//list.print();
#endif

#ifdef OPERATOR_PLUS_CHECK
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

	//ForwardList fusion = list1 + list2;		//CopyConstructor
	ForwardList fusion;
	cout << delimiter << endl;
	fusion = list1 + list2;						//CopyAssignment
	cout << delimiter << endl;
	fusion.print();

	/*int index;
	int value;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	list1.Insert(value, index);*/
	//list1.print();
#endif

#ifdef PERFORMANCE_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;
	ForwardList list;
	clock_t t_start = clock();
	for (int i = 0; i < n; i++)
	{
		//list.push_back(rand() % 100);
		list.push_front(rand() % 100);
	}
	clock_t t_end = clock();
	cout << "ForwardList filled for " << double(t_end - t_start) / CLOCKS_PER_SEC << " sec. ";
	system("PAUSE");
#endif

#ifdef trbIndec
	ForwardList list;

	for (int i = 0; i < list.get_size(); i++)
	{
		list[i] = rand() % 100;
	}
	for (int i = 0; i < list.get_size(); i++)
	{
		cout << list[i] << tab;
	}
	cout << endl;
#endif

#ifdef MOVESEMANTIC_CHECK
	ForwardList list1;
	cout << list1 << endl;
	ForwardList list2 = list1;
	cout << list2 << endl;
#endif
}