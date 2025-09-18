#include"FullConection.h"
using namespace std;

//#define BASE_CHECK
//#define HOMEWORK
#define	CODE_CHECK

void main()
{
	setlocale(LC_ALL, "");

#ifdef BASE_CHECK
	int n;
	cout << "¬ведите размер списка: "; cin >> n;
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
	//cout << "¬ведите индекс добавл€емого элемента: "; cin >> index;
	//cout << "¬ведите значение добавл€емого элемента: "; cin >> value;
	//list.insert(value, index);
	//list.print();
	//list.reverse_print();
	cout << "¬ведите индекс удал€емого элемента: "; cin >> index;
	list.Erase(index);
	list.print();
#endif // BASE_CHECK
#ifdef HOMEWORK
	List<int> list1 = { 3, 5, 8, 13, 21 };
	List<int> list2 = { 34, 55, 89 };
	//list1.print();
	//list2.print();
	List<int> list3 = list1 + list2;
	for (int i : list1)cout << i << tab; cout << endl;
	for (int i : list2)cout << i << tab; cout << endl;
	for (int i : list3)cout << i << tab; cout << endl;
	for (List<int>::ConstIterator it = list1.begin(); it != list1.end(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;
	for (List<int>::Iterator it = list1.begin(); it != list1.end(); ++it)
	{
		*it *= 100;
	}
	for (List<int>::ConstReverseIterator it = list1.rbegin(); it != list1.rend(); ++it)
	{
		//*it *= 100;
		cout << *it << tab;
	}
	cout << endl;
#endif

#ifdef CODE_CHECK
	List<double> d_list = { 2.7, 3.14, 5.8, 8.3 };
	for (double i : d_list)cout << i << tab; cout << endl;

	List<std::string> s_list = { "’орошо", "живЄт", "на", "свете", "¬инни", "ѕух" };
	for (std::string i : s_list)cout << i << tab; cout << endl;
	for (List<std::string>::ReverseIterator it = s_list.rbegin(); it != s_list.rend(); ++it)
		cout << *it << tab;
	cout << endl;
#endif // CODE_CHECK

}