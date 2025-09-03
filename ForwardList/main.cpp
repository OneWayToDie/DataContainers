#include<iostream>
using namespace std;

#define tab "\t"


	class Element
	{
		int Data;
		Element* pNext;
		Element* pPrev;	//���������� �������
		
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
		Element* Tail;	//�����
		//int SIZE;
	public:
		ForwardList()
		{
			//����������� �� ��������� - ������ ������ ������
			Head = nullptr; //���� ������ ����, �� ��� ������ ��������� �� ����
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
			//1)������ ������� � ��������� � ���� ����������� ��������:
			Element* New = new Element(Data);

			//2)����������� �����, ��������� ������� � ������ ������
			New->pNext = Head;

			//3) ��������� ������ �� ����� ������� (���������� ����� ������� � ������):
			Head = New;
			//SIZE++;
		}

		void push_back(int Data)
		{
			Element* New = new Element(Data);
			//��������� ���������� ������ � ������ ��������
			if (Tail)
			{
				Tail->pNext = New;
				New->pPrev = Tail;
				Tail = New;
			}
			else
			{
				Head = Tail = New;		//���� ������ ���� - ������������� ����� ������� ��� ������ � �����
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
				cout << "������ ����, ��������� ��� ��� ������." << endl;
			}
			//���� ������� ������ ��������� � ��������� ������
			if (Head == Tail)
			{
				delete Head;
				Head = nullptr;
				Tail = nullptr;
			}
			//������� ������� �� ������ ������
			Element* New_Delete = Head;	//������������ ����� ������� � �������
			Head = Head->pNext;	//��� ������ ����� ���������� ��������
			Head->pPrev = nullptr;	//��������� ��������� ������
			delete New_Delete;	//������� �������
		}
		void pop_back()
		{
			if (Head == nullptr)
			{
				cout << "������ ����, ��������� ��� ��� ������." << endl;
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
			Element* Temp = Head;	// Temp - ��� ��������.
			//�������� - ��� ���������, ��� ������ �������� ����� ���������� �������� ��������� ������.
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
	cout << "������� ������ ������: "; cin >> n;
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