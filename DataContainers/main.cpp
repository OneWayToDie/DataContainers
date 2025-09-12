#include<iostream>
using namespace std;

#define tab "\t"
#define delimiter "\n----------------------------------------------------------\n"

class List
{
	class Element
	{
		int Data;
		Element* pNext;
		Element* pPrev;
	public:
		Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr)
			:Data(Data), pNext(pNext), pPrev(pPrev)
		{
			cout << "EConstructor:\t" << this << endl;
		}
		~Element()
		{
			cout << "EDestructor:\t" << this << endl;
		}
		friend class List;
	}*Head, * Tail;	//Объекты классов и структур, и указателей на эти объекты можно объявлять непосредственно после описания классов и структур
	size_t size;	//Размер списка size_t - это typedef на 'unsigned int'.
public:
	List()
	{
		Head = Tail = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	~List()
	{
		/*while (Head)pop_front();*/
		while (Head)pop_back();
		cout << "EDestructor:\t" << this << endl;
	}

	//		Adding Elements:
	void push_front(int Data)
	{
		//1) Создаём элемент, в котором будет храниться добавляемое значение:
		Element* New = new Element(Data);

		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = New;
		}
		else
		{
			//2) Пристыковываем новый элемент к списку:
			New->pNext = Head;

			//3) Пристыковываем начальный элемент списка к новому элементу:
			Head->pPrev = New;

			//4) Делаем новый элемент начальным элементом списка:
			Head = New;
		}
		size++;
	}
	void push_back(int Data)
	{
		//1)Создаём новый элемент:
		Element* New = new Element(Data);
		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = New;
		}
		else
		{
			//2) Цепляем новый элемент за Хвост списка:
			New->pPrev = Tail;

			//3) Пристыковываем список к новому элементу:
			Tail->pNext = New;

			//4) Делаем новый элемент хвостом списка:
			Tail = New;
		}
		size++;
	}

	void insert(int Data, int Index)
	{
		if (Index < 0)return;
		if (Index == 0 || size == 0)return push_front(Data);
		if (Index >= size)return push_back(Data);
		//1) Доходим до нужного элемента:
		Element* Temp;
		if (Index < size / 2)
		{
			Temp = Head;
			for (int i = 0; i < Index; i++)Temp = Temp->pNext;
		}
		else
		{
			Temp = Tail;
			for (int i = 0; i < size - Index - 1; i++)Temp = Temp->pPrev;
		}
		//	Независимо от того, каким образом мы дошли до нужного элемента, с начала списка или с конца
		//	 Процедура добавления элемента будет идентичной:

		//2) Создаём новый элемент:
		Element* New = new Element(Data);

		//3) Пристыковываем новый элемент к списку:
		New->pNext = Temp;
		New->pPrev = Temp->pPrev;

		//4) Вклиниваем новый элемент в список:
		Temp->pPrev->pNext = New;
		Temp->pPrev = New;
		size++;
	}

	//		Removing Elements:
	void pop_front()
	{
		if (Head == nullptr && Tail == nullptr)return;
		if (Head == Tail)	//Если голова и хвост равны, значит они указывают либо на 0, либо на один и тот же элемент
							//Ситуацию с пустым списком обрабатывает предыдущее условие.
							//Ситуация с выраженным списком обрабатывает текущее условие, и в этом
							//if-e удаляется один элемент
		{
			delete Head;
			Head = Tail = nullptr;
		}
		else
		{
			//			Общий случай:

			//1) Смещаем голову на следующий элемент:
			Head = Head->pNext;

			//2) Удаляем элемент из памяти:
			delete Head->pPrev;

			//3) Обнуляем указатель на удалённый элемент (делаем Head последним элементом списка):
			Head->pPrev = nullptr;
		}
		size--;
	}
	void pop_back()
	{
		if (Head == nullptr && Tail == nullptr)return;
		if (Head == Tail)
		{
			delete Tail;
			Head = Tail = nullptr;
		}
		else
		{
			Tail = Tail->pPrev;

			delete Tail->pNext;
			Tail->pNext = nullptr;
		}
		size--;
	}

	//		Methods:
	void print()const
	{
		cout << delimiter << endl;
		cout << "Head: " << Head << endl;
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Tail: " << Tail << endl;
		cout << "Количество элементов списка: " << size;
		cout << delimiter << endl;
	}
	void reverse_print()const
	{
		cout << delimiter << endl;
		cout << "Tail: " << Tail << endl;
		for(Element* Temp = Tail; Temp; Temp = Temp->pPrev)
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Head: " << Head << endl;
		cout << "Количество элементов списка: " << size;
		cout << delimiter << endl;
	}
};

//#define BASE_CHECK
#define HOMEWORK


void main()
{
	setlocale(LC_ALL, "");

#ifdef BASE_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;
	List list;
	list.pop_front();
	list.print();
	for (int i = 0; i < n; i++)
	{
		//list.push_front(rand() % 100);
		list.push_back(rand() % 100);
	}

	list.print();
	list.reverse_print();
	/*list.pop_back();
	list.print();
	list.reverse_print();*/

	int index;
	int value;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	list.insert(value, index);
	list.print();
	list.reverse_print();
#endif // BASE_CHECK

#ifdef HOMEWORK

	List list1 = { 3, 5, 8, 13, 21 };
	List list2 = { 34, 55, 89 };
	List list3 = list1 + list2;
	for (int i : list1)cout << i << tab; cout << endl;
	for (int i : list2)cout << i << tab; cout << endl;
	for (int i : list3)cout << i << tab; cout << endl;

#endif

}