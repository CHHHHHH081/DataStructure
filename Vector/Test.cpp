#include <vector>
#include <iostream>
using namespace std;
void test01()
{
	vector<int> v = { 1,2,3 };
	v.reserve(10);
	auto it = v.begin();
	v.push_back(4);
	cout << *it;
}
void test02()
{
	vector<int> v = { 0,1,2,3,4,5,6,7,8 };
	for (auto i = v.begin(); i < v.end(); i++)
	{
		if (*i % 2 == 0)
		{
			i=v.erase(i);
		}
		else
		{
			++i;
		}
	}
}
int main()
{
	test01();
	return 0;
}