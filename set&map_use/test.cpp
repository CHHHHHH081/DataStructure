#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <set>
#include <map>
#include <vector>
using namespace std;
//int main()
//{
	//set<int> s;
	///*set<int, greater<int>> s;*/
	//s.insert(2);
	//s.insert(1);
	//s.insert(4);
	//s.insert(3);
	//s.insert(2);
	//for (auto i : s)
	//{
	//	cout << i << ' ';
	//}
	//cout << endl;
	//s.insert({ 3,2,6,7 });
	//for (auto i : s)
	//{
	//	cout << i << ' ';
	//}
	//cout << endl;
	// 
	// 
	//set<int> s = { 4,2,6,5,7,6,8 };
	//for (auto i : s)
	//{
	//	cout << i << ' ';
	//}
	//cout << endl;
	////删最小
	//s.erase(s.begin());
	//for (auto i : s)
	//{
	//	cout << i << ' ';
	//}
	//cout << endl;
	////删5
	//s.erase(5);
	//for (auto i : s)
	//{
	//	cout << i << ' ';
	//}


	//set<int> s = { 10,20,30,40,50 };
	//for (auto i : s)
	//{
	//	cout << i << ' ';
	//}
	//cout << endl;
	//auto it1 = s.find(20);
	//auto it2 = s.find(40);
	//auto it3 = s.find(60);
	//if (it1 != s.end() && it2 != s.end()) s.erase(it1, it2);
	//for (auto i : s)
	//{
	//	cout << i << ' ';
	//}
	//cout << endl;


	//set<int> s = { 1,2,3,4,5,6,7,8,9 };

	//int x;
	//cin >> x;
	//// 算法库的查找 O(N)
	//auto pos1 = find(s.begin(), s.end(), x);

	//// set自身实现的查找 O(logN)
	//auto pos2 = s.find(x);

	//// 利用count间接实现快速查找
	//if (s.count(x))
	//{
	//	cout << x << "在！" << endl;
	//}
	//else
	//{
	//cout << x << "不存在！" << endl;
	//}

	//set<int> s = { 1,2,3,4,5 };
	//auto it = s.begin();
	//s.erase(it);
	//cout << *it << endl;

	//set<int> s = { 10,20,30,40,50,60,70,80,90 };
	//for (auto i : s)
	//{
	//	cout << i << ' ';
	//}
	//cout << endl;
	//auto itlow = s.lower_bound(30);
	//auto itup = s.upper_bound(60);
	//s.erase(itlow, itup);
	//for (auto i : s)
	//{
	//	cout << i << ' ';
	//}
	//cout << endl;


	//// 相?set不同的是，multiset是排序，但是不去重
	//multiset<int> s = { 4,2,7,2,4,8,4,5,4,9 };
	//auto it = s.begin();
	//while (it != s.end())
	//{
	//	cout << *it << " ";
	//	++it;
	//} 
	//cout << endl;
	//// 相?set不同的是，x可能会存在多个，find查找中序的第?个
	//int x;
	//cin >> x;
	//auto pos = s.find(x);
	//while (pos != s.end() && *pos == x)
	//{
	//	cout << *pos << " ";
	//	++pos;
	//} 
	//cout << endl;
	//// 相?set不同的是，count会返回x的实际个数
	//cout << s.count(x) << endl;
	//// 相?set不同的是，erase给值时会删除所有的x
	//s.erase(x);
	//for (auto e : s)
	//{
	//	cout << e << " ";
	//} 
	//cout << endl;
//	return 0;
//}

//int main()
//{
//	/*map<int, int> mp;
//	mp.insert({ 1,2 });*/
//	//单个pair构造
//	map<int, int> mp1({ 1,2 });
//	//多参数类型转换
//	map<int, int> mp2(1, 2);
//
//	//迭代区间构造
//	vector<pair<int, int>> v({ {1,2},{2,3},{3,4} });
//	map<int, int> mp3(v.begin(),v.end());
//
//	//initializer_list<pair>构造
//	map<int, int> mp4({ {1,2},{2,3},{3,4} });
//	
//	return 0;
//}

template<typename T1,typename T2>
class Less
{
public:
	bool operator()(T1 x, T2 y)
	{

	}
};

int main()
{
	multimap<int, int> mmp({ {1,2},{1,4},{1,3} });
	for (auto i : mmp)
	{
		cout << i.second << ' ';
	}
	return 0;
}
