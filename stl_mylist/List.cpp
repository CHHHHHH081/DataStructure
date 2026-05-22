#include <iostream>
#include "List.h"
#include <list>
#include <initializer_list>
using namespace std;
int main()
{
	/*zzt::List<int> a = { 1,2,004 };
	zzt::List<int> b = { 4,5,6,7 };
	cout << a.size()<<endl;
	a.Display();
	cout << b.size() << endl;
	b.Display();
	int result = 1;
	if (a.GetElement(1) == result) cout << result << endl;
	cout << b.GetElement(6) << endl;
	a.insert(a.begin(), 5);
	a.Display();
	a.Delete(3);
	a.Display();*/
	int i, j;
	zzt::List<int> c;
	for (i = 0; i < 10; i++)
	{
		c.push_back(i);
	}
	c.Display();
	c.Reverse();
	c.Display();
	return 0;
}
