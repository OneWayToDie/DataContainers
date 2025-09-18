#include"stdafx.h"


//		Removing Elements:
template<typename T>void List<T>::Erase(int Index)
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
template<typename T>void List<T>::pop_front()
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
template<typename T>void List<T>::pop_back()
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