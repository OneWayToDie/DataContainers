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
	class ConstBaseIterator
	{
		//Этот класс обобщает свойства разных итераторов
	protected:
		Element* Temp;
	public:
		ConstBaseIterator(Element* Temp = nullptr) :Temp(Temp) {}
		~ConstBaseIterator() {}

		//			Comparison operators:
		bool operator==(const ConstBaseIterator& other)const
		{
			return this->Temp == other.Temp;
		}
		bool operator!=(const ConstBaseIterator& other)const
		{
			return this->Temp != other.Temp;
		}

		int operator*()const		//В константном итераторе должен быть только константный оператор разыменования,
									//здесь ни в коем случае НЕ должно быть обычного оператор разыменования
		{
			return Temp->Data;
		}
	};
public:
	class ConstIterator	:public ConstBaseIterator
	{
	public:
		ConstIterator(Element* Temp = nullptr) :ConstBaseIterator(Temp) {}
		~ConstIterator() {}

		ConstIterator& operator++()
		{
			Temp = Temp->pNext;
			return *this;
		}
		ConstIterator operator++(int)
		{
			ConstIterator old = *this;
			Temp = Temp->pNext;
			return old;
		}
		ConstIterator& operator--()
		{
			Temp = Temp->pPrev;
			return *this;
		}
		ConstIterator operator--(int)
		{
			ConstIterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}
	};
	class ConstReverseIterator	:public ConstBaseIterator
	{
	public:
		ConstReverseIterator(Element* Temp = nullptr) :ConstBaseIterator(Temp) {}
		~ConstReverseIterator() {}

		//		Increment/Decrement:
		ConstReverseIterator& operator++()
		{
			Temp = Temp->pPrev;
			return *this;
		}
		ConstReverseIterator operator++(int)
		{
			ConstReverseIterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}
		ConstReverseIterator& operator--()
		{
			Temp = Temp->pNext;
			return *this;
		}
		ConstReverseIterator operator--(int)
		{
			ConstReverseIterator old = *this;
			Temp = Temp->pNext;
			return old;
		}
	};
	class Iterator :public ConstIterator
	{
	public:
		Iterator(Element* Temp) :ConstIterator(Temp) {}
		~Iterator() {}
		int& operator*()
		{
			return Temp->Data;
		}
	};
	class ReverseIterator :public ConstReverseIterator
	{
	public:
		ReverseIterator(Element* Temp) :ConstReverseIterator(Temp) {}
		~ReverseIterator() {}
		int& operator*()
		{
			return Temp->Data;
		}
	};
	ConstIterator begin()const
	{
		return Head;
	}
	ConstIterator end()const
	{
		return nullptr;
	}
	ConstReverseIterator rbegin()const
	{
		return Tail;
	}	ConstReverseIterator rend()const
	{
		return nullptr;
	}
	Iterator begin()
	{
		return Head;
	}
	Iterator end()
	{
		return nullptr;
	}
	ReverseIterator rbegin()
	{
		return Tail;
	}
	ReverseIterator rend()
	{
		return nullptr;
	}

	List()
	{
		Head = Tail = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	List(const std::initializer_list<int>& il) :List()
	{
		for (int const* it = il.begin(); it != il.end(); ++it)
		{
			push_back(*it);
		}
		cout << "ILConstructor:\t" << this << endl;
	}
	List(const List& other) :List()
	{
		*this = other;
		cout << "LCopyConstructor:\t" << this << endl;
	}
	~List()
	{
		/*while (Head)pop_front();*/
		while (Head)pop_back();
		cout << "EDestructor:\t" << this << endl;
	}

	//		Operators:
	List& operator=(const List& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_back(Temp->Data);
		cout << "LCopyAssignment:\t" << this << endl;
		return *this;
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
	void Erase(int Index)
	{
		if (Index < 0)return;
		if (Index == 0 || size == 0)return pop_front();
		if (Index >= size - 1)return pop_back();
		Element* Temp;
		if (Index < size / 2)
		{
			Temp = Head;
			for (int i = 0; i < Index; i++)Temp = Temp->pNext;
			Element* Erased = Temp;
			Temp = Temp->pPrev;
			Temp->pNext = Erased->pNext;
			delete Erased;
			Temp = nullptr;
		}
		else
		{
			Temp = Tail;
			for (int i = 0; i < size - Index - 1; i++)Temp = Temp->pPrev;
			Element* Erased = Temp;
			Erased->pPrev = Temp->pPrev;
			Temp = Temp->pPrev;
			Temp->pNext = Erased->pNext;
			delete Erased;
			Temp = nullptr;
		}
		size--;
	}
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

List operator+(const List& left, const List& right)
{
	List fusion = left;
	for (List::ConstIterator it = right.begin(); it != right.end(); ++it)
	{
		//*it *= 100;
		fusion.push_back(*it);

	}
	return fusion;
}


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

	//list.reverse_print();
	/*list.pop_back();
	list.print();
	list.reverse_print();*/

	int index;
	//int value;
	//cout << "Введите индекс добавляемого элемента: "; cin >> index;
	//cout << "Введите значение добавляемого элемента: "; cin >> value;
	//list.insert(value, index);
	//list.print();
	//list.reverse_print();
	cout << "Введите индекс удаляемого элемента: "; cin >> index;
	list.Erase(index);
	list.print();
#endif // BASE_CHECK

#ifdef HOMEWORK
	List list1 = { 3, 5, 8, 13, 21 };
	List list2 = { 34, 55, 89 };
	//list1.print();
	//list2.print();
	List list3 = list1 + list2;
	for (int i : list1)cout << i << tab; cout << endl;
	for (int i : list2)cout << i << tab; cout << endl;
	for (int i : list3)cout << i << tab; cout << endl;
	for (List::ConstIterator it = list1.begin(); it != list1.end(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;
	for (List::Iterator it = list1.begin(); it != list1.end(); ++it)
	{
		*it *= 100;
	}
	for (List::ConstReverseIterator it = list1.rbegin(); it != list1.rend(); ++it)
	{
		//*it *= 100;
		cout << *it << tab;
	}
	cout << endl;
#endif
}