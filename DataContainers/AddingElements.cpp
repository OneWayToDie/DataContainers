#include"stdafx.h"

//		Adding Elements:
template<typename T>void List<T>::push_front(T Data)
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
template<typename T>void List<T>::push_back(T Data)
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

template<typename T>void List<T>::insert(T Data, int Index)
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