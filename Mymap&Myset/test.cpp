#include "Mymap.h"
#include "Myset.h"
void test_set()
{
	zzt::set<int> s;
	int a[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
	for (auto e : a)
	{
		s.insert(e);
	} 
	for (auto e : s)
	{
		cout << e << " ";
	} 
	cout << endl;
	//Print(s);
}
void test_map()
{
	zzt::map<string, string> dict;
	dict.insert({ "sort", "排序" });
	dict.insert({ "left", "左边" });
	dict.insert({ "right", "右边" });
	dict["left"] = "左边，剩余";
	dict["insert"] = "插入";
	dict["string"];
	zzt::map<string, string>::iterator it = dict.begin();
	while (it != dict.end())
	{
		// 不能修改first，可以修改second
		//it->first += 'x';
		it->second += 'x';
		cout << it->first << ":" << it->second << endl;
		++it;
	} 
	cout << endl;
}
int main()
{
	//test_set();
	test_map();
	return 0;
}