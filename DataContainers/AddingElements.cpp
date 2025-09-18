#include"stdafx.h"

//		Adding Elements:
template<typename T>void List<T>::push_front(T Data)
{
	//1) ������ �������, � ������� ����� ��������� ����������� ��������:
	Element* New = new Element(Data);

	if (Head == nullptr && Tail == nullptr)
	{
		Head = Tail = New;
	}
	else
	{
		//2) �������������� ����� ������� � ������:
		New->pNext = Head;

		//3) �������������� ��������� ������� ������ � ������ ��������:
		Head->pPrev = New;

		//4) ������ ����� ������� ��������� ��������� ������:
		Head = New;
	}
	size++;
}
template<typename T>void List<T>::push_back(T Data)
{
	//1)������ ����� �������:
	Element* New = new Element(Data);
	if (Head == nullptr && Tail == nullptr)
	{
		Head = Tail = New;
	}
	else
	{
		//2) ������� ����� ������� �� ����� ������:
		New->pPrev = Tail;

		//3) �������������� ������ � ������ ��������:
		Tail->pNext = New;

		//4) ������ ����� ������� ������� ������:
		Tail = New;
	}
	size++;
}

template<typename T>void List<T>::insert(T Data, int Index)
{
	if (Index < 0)return;
	if (Index == 0 || size == 0)return push_front(Data);
	if (Index >= size)return push_back(Data);
	//1) ������� �� ������� ��������:
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
	//	���������� �� ����, ����� ������� �� ����� �� ������� ��������, � ������ ������ ��� � �����
	//	 ��������� ���������� �������� ����� ����������:

	//2) ������ ����� �������:
	Element* New = new Element(Data);

	//3) �������������� ����� ������� � ������:
	New->pNext = Temp;
	New->pPrev = Temp->pPrev;

	//4) ���������� ����� ������� � ������:
	Temp->pPrev->pNext = New;
	Temp->pPrev = New;
	size++;
}