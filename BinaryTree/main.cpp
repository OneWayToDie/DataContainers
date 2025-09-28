#include<iostream>
#include<time.h>
#include<algorithm>
using namespace std;
using std::cout;
using std::cin;
using std::endl;

#define tab "\t"
#define AvG (Root->Data + sum(Root->pLeft) + sum(Root->pRight)) / (count(Root->pLeft) + count(Root->pRight) + 1)
#define runtime double(end - start) / CLOCKS_PER_SEC
#define MAX(a,b)a>b?a:b

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
		return Depth(Root);
	}
	void depth_print(int depth, int width = 4)const
	{
		depth_print(depth, Root, width);
		cout << endl;
	}
	void tree_print()const
	{
		tree_print(Depth(), 4*Depth());
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
	/*	if (Root->pLeft == nullptr)return Root->Data;
		else return minValue(Root->pLeft);*/
		return Root == nullptr ? INT_MIN : Root->pLeft == nullptr ? Root->Data : minValue(Root->pLeft);
	}
	int maxValue(Element* Root)const
	{
		/*if (Root->pRight == nullptr) return Root->Data;
		else return maxValue(Root->pRight);*/
		return !Root ? INT_MIN : Root->pRight ? maxValue(Root->pRight) : Root->Data;
	}
	int count(Element* Root)const
	{
		/*if (Root == nullptr)return 0;
		else return count(Root->pLeft) + count(Root->pRight) + 1;*/
		//return Root == nullptr ? 0 : count(Root->pLeft) + count(Root->pRight) + 1;
		return !Root ? 0 : count(Root->pLeft) + count(Root->pRight) + 1;
	}
	int sum(Element* Root)const
	{
		/*if (Root == nullptr) return 0;
		else return Root->Data + sum(Root->pLeft) + sum(Root->pRight);*/
		return Root == nullptr ? 0 : sum(Root->pLeft) + sum(Root->pRight) + Root->Data;
		//return !Root ? 0 : Root->Data + sum(Root->pLeft) + sum(Root->pRight);
	}
	int Depth(Element* Root)const
	{
		//if (Root == nullptr)return 0;
		//else
		//{
		//	if(Depth(Root->pLeft) > Depth(Root->pRight))
		//		return 1 + Depth(Root->pLeft);
		//	else 
		//		return 1 + Depth(Root->pRight);
		//	//return Root->pLeft > Root->pRight ? 1 + Depth(Root->pLeft) : 1 + Depth(Root->pRight);
		//}
		//return Root == nullptr ? 0 : Depth(Root->pLeft) > Depth(Root->pRight) ? 1 + Depth(Root->pLeft) : 1 + Depth(Root->pRight);
	/*	if (Root == nullptr) return 0;
		int l_depth = Depth(Root->pLeft) + 1;
		int r_depth = Depth(Root->pRight) + 1;
		return l_depth < r_depth ? r_depth : l_depth;*/
		return Root == nullptr ? 0 : std::max(Depth(Root->pLeft) + 1, Depth(Root->pRight) + 1);
		/*return 
			Root == nullptr ? 0 : 
			Depth(Root->pLeft) + 1 > Depth(Root->pRight) + 1 ? 
			Depth(Root->pLeft) + 1 : 
			Depth(Root->pRight) + 1;*/
	}
	void depth_print(int depth, Element* Root, int width = 4)const
	{
		if (Root == nullptr)return;
		if (depth == 0)
		{
			cout.width(width);
			cout << Root->Data;
		}
		depth_print(depth - 1, Root->pLeft, width);
		depth_print(depth - 1, Root->pRight, width);
	}
	void tree_print(int depth, int width)const
	{
		if (depth == -1)return;
		tree_print(depth - 1, width * 1.5);
		depth_print(depth - 1, width);
		cout << "\n\n\n";

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


template<typename T>void measure_performance(const char message[], T(Tree::*function)()const, const Tree& tree)
{
	//int (*function)()) - указатель на функцию, которая ничего не принимает, и возвращает значение типа 'int'
	clock_t start = clock();
	T result = (tree.*function)();
	clock_t end = clock();
	cout << message << result << ", вычислено за " << runtime << " секунд/n" << endl;
}

//#define BASECHECK
//#define ERASE_CHECK
#define DEPTH_CHECK
//#define performance_check

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

	16,			32,		58,				85, 91, 98
	};
	tree.print();

	int value;
	//cout << "Введите удаляемое число: "; cin >> value;
	//tree.erase(value);
	//tree.erase(25);
	//tree.erase(32);
	//tree.erase(50);
	//tree.erase(75);
	tree.print();
	cout << "Глубина дерева равна: " << tree.Depth() << endl;
#endif // ERASE_CHECK

#ifdef DEPTH_CHECK
	//int n;
	//cout << "Введите глубину: "; cin >> n;
	Tree tree =
	{
					50,

		25,						75,

	16,			32,		58,				85 //, 91, 98
	};
	tree.print();
	cout << "Глубина дерева равна: " << tree.Depth() << endl;
	//tree.depth_print(3);
	tree.tree_print();
#endif // DEPTH_CHECK

#ifdef performance_check
	int n;
	cout << "Введите количество элементов: "; cin >> n;
	Tree tree;
	for (int i = 0; i < n; i++)
	{
		tree.insert(rand() % 100);
	}
	measure_performance("Минимальное значение в дереве: ", &Tree::minValue, tree);
	measure_performance("Максимальное значение в дереве: ", &Tree::maxValue, tree);
	measure_performance("Сумма элементов дерева: ", &Tree::sum, tree);
	measure_performance("Количество элементов дерева: ", &Tree::count, tree);
	measure_performance("Среднее значение элементов дерева: ", &Tree::AVG, tree);
	measure_performance("Глубина дерева: ", &Tree::Depth, tree);
#endif // performance_check
}
