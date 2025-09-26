﻿#include<iostream>
#include<time.h>
//using namespace std;
using std::cin;
using std::cout;
using std::endl;


#define tab "\t"
#define AvG (Root->Data + sum(Root->pLeft) + sum(Root->pRight)) / (count(Root->pLeft) + count(Root->pRight) + 1)
//#define runtime double(t_end - t_start)/CLOCKS_PER_SEC
//#define DEBUG

class Tree
{
protected:
	class Element
	{
		int Data;
		Element* pLeft;
		Element* pRight;
	public:
		Element(int Data, Element* pLeft = nullptr, Element* pRight = nullptr) :
			Data(Data), pLeft(pLeft), pRight(pRight)
		{
#ifdef DEBUG
			cout << "EConstructor:\t" << this << endl;
#endif // DEBUG

		}
		~Element()
		{
#ifdef DEBUG
			cout << "EDestructor:\t" << this << endl;
#endif // DEBUG

		}
		friend class Tree;
		friend class UniqueTree;
	}*Root;
public:
	Element* getRoot()const
	{
		return Root;
	}
	Tree() :Root(nullptr)
	{
		cout << "TConstructor:\t" << this << endl;
	}
	Tree(const std::initializer_list<int>& il) :Tree()
	{
		for (int const* it = il.begin(); it != il.end(); ++it)
			insert(*it, Root);
		cout << "ILConstructor:\t" << this << endl;
	}
	~Tree()
	{
		clear();
		cout << "TDestructor:\t" << this << endl;
	}
	void clear()
	{
		clear(Root);
	}
	void insert(int Data)
	{
		insert(Data, Root);  
	}
	void erase(int Data)
	{
		erase(Data, Root);
	}
	int minValue()const
	{
		return minValue(Root);
	}
	int maxValue()const
	{
		return maxValue(Root);
	}
	int sum()const
	{
		return sum(Root);
	}
	double AVG()const
	{
		return (double)sum(Root) / count(Root);
	}
	int count()const
	{
		return count(Root);
	}
	int Depth()const
	{
		return Depth();
	}
	void print()const
	{
		print(Root);
		cout << endl;
	}
private:
	void clear(Element*& Root)
	{
		if (Root == nullptr)return;
		clear(Root->pLeft);
		clear(Root->pRight);
		delete Root;
		Root = nullptr;
	}
	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr) this->Root = new Element(Data);
		if (Root == nullptr)return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);
		}
		else
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}
	void erase(int Data, Element*& Root)
	{
		if (Root == nullptr)return;
		erase(Data, Root->pLeft);
		erase(Data, Root->pRight);
		if (Data == Root->Data)
		{
			if (Root->pLeft == Root->pRight)
			{
				delete Root;
				Root = nullptr;
			}
			else
			{
				//Для того чтобы дерево балансировалось при удалении элементов,
				//Перед удалением его нужно взвесить:
				if (count(Root->pLeft) > count(Root->pRight))
				{
					//И если левая ветка тяжелее чем правая, то берём значение из неё максимальное значение
					//Потому что оно ближе всего к удаляемому значению
					Root->Data = maxValue(Root->pLeft);
					erase(maxValue(Root->pLeft), Root->pLeft);
				}
				else
				{
					//В противном случае берём минимальное значение из правой ветки,
					//Потому что оно ближе всего к удаляемому значению:
					Root->Data = minValue(Root->pRight);
					erase(minValue(Root->pRight), Root->pRight);
				}
			}
		}
	}
	int minValue(Element* Root)const
	{
		return Root == nullptr ? INT_MIN : Root->pLeft == nullptr ? Root->Data : minValue(Root->pLeft);
	}
	int maxValue(Element* Root)const
	{
		return !Root ? INT_MIN : Root->pRight ? maxValue(Root->pRight) : Root->Data;
	}
	int count(Element* Root)const
	{
		return !Root ? 0 : count(Root->pLeft) + count(Root->pRight) + 1;
	}
	int sum(Element* Root)const
	{
		return Root == nullptr ? 0 : sum(Root->pLeft) + sum(Root->pRight) + Root->Data;
	}
	int Depth(Element* Root)const
	{
		return Root == nullptr ? 0 : Root->pLeft > Root->pRight ? 1 + Depth(Root->pLeft) : 1 + Depth(Root->pRight);
	}
	void print(Element* Root)const
	{
		if (Root == nullptr)return;
		print(Root->pLeft);
		cout << Root->Data << tab;
		print(Root->pRight);
	}
};

class UniqueTree :public Tree
{
	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr) this->Root = new Element(Data);
		if (Root == nullptr)return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);
		}
		else if(Data > Root->Data)
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}
public:
	void insert(int Data)
	{
		insert(Data, Root);
	}
};

#define BASECHECK
//#define ERASE_CHECK
//#define PeRfOrMaNcE

void main()
{
	setlocale(LC_ALL, "");
#ifdef BASECHECK
	int n;
	cout << "Введите количество элементов: "; cin >> n;
	Tree tree;
	for (int i = 0; i < n; i++)
	{
		tree.insert(rand() % 100);
	}
	tree.print();
	cout << endl;
	cout << "Минимальное значение в дереве: " << tree.minValue() << endl;
	cout << "Максимальное значение в дереве: " << tree.maxValue() << endl;
	cout << "Количество элементов дерева: " << tree.count() << endl;
	cout << "Сумма элементов дерева: " << tree.sum() << endl;
	cout << "Среднее значение элементов дерева: " << tree.AVG() << endl;
	cout << "Глубина дерева равна: " << tree.Depth() << endl;

	UniqueTree u_tree;
	for (int i = 0; i < n; i++)
	{
		u_tree.insert(rand() % 100);
	}
	u_tree.print();
	cout << "Минимальное значение в дереве: " << u_tree.minValue() << endl;
	cout << "Максимальное значение в дереве: " << u_tree.maxValue() << endl;
	cout << "Количество элементов дерева: " << u_tree.count() << endl;
	cout << "Сумма элементов дерева: " << u_tree.sum() << endl;
	cout << "Среднее значение элементов дерева: " << u_tree.AVG() << endl;
	cout << "Глубина дерева равна: " << tree.Depth() << endl;
#endif // BASECHECK

#ifdef ERASE_CHECK
	Tree tree =
	{
					50,

		25,						75,

	16,			32,		58,				85
	};
	tree.print();

	int value;
	//cout << "Введите удаляемое число: "; cin >> value;
	//tree.erase(value);
	tree.erase(25);
	tree.erase(32);
	tree.erase(50);
	tree.erase(75);
	tree.print();
	cout << "Глубина дерева равна: " << tree.Depth() << endl;
#endif // ERASE_CHECK

#ifdef PeRfOrMaNcE
	int n;
	cout << "Введите количество элементов: "; cin >> n;
	Tree tree;
	clock_t t_start_element = clock();
	for (int i = 0; i < n; i++)
	{
		tree.insert(rand() % 100);
	}
	clock_t t_end_element = clock();
	cout << "Бинарное дерево заполнено за " << double(t_end_element - t_start_element) / CLOCKS_PER_SEC << " секунд" << endl;
	system("PAUSE");
	cout << "\nВывод производительности методов: " << "\n\n";
	clock_t t_start_depth = clock();
	tree.Depth();
	clock_t t_end_depth = clock();
	cout << "Глубина дерева посчитана за " << double(t_end_depth - t_start_depth) / CLOCKS_PER_SEC << " секунд" << endl;	
	clock_t t_start_min = clock();
	tree.minValue();
	clock_t t_end_min = clock();
	cout << "Минимальное значение дерева посчитано за " << double(t_end_min - t_start_min) / CLOCKS_PER_SEC << " секунд" << endl;	
	clock_t t_start_max = clock();
	tree.maxValue();
	clock_t t_end_max = clock();
	cout << "Максимальное значение дерева посчитано за " << double(t_end_max - t_start_max) / CLOCKS_PER_SEC << " секунд" << endl;
	clock_t t_start_count = clock();
	tree.count();
	clock_t t_end_count = clock();
	cout << "Количество элементов дерева посчитано за " << double(t_end_count - t_start_count) / CLOCKS_PER_SEC << " секунд" << endl;	
	clock_t t_start_sum = clock();
	tree.sum();
	clock_t t_end_sum = clock();
	cout << "Сумма элементов дерева посчитано за " << double(t_end_sum - t_start_sum) / CLOCKS_PER_SEC << " секунд" << endl;
	clock_t t_start_avg = clock();
	tree.AVG();
	clock_t t_end_avg = clock();
	cout << "Среднее арифметическое элементов дерева посчитано за " << double(t_end_avg - t_start_avg) / CLOCKS_PER_SEC << " секунд" << "\n\n";
	system("PAUSE");
#endif // PeRfOrMaNcE

}