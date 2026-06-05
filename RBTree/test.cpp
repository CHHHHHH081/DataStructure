#define _CRT_SECURE_NO_WARNINGS
#include "RBTree.h"
void TestRBTree1()
{
	RBTree<int, int> t;
	// 常规的测试⽤例
	//int a[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	// 特殊的带有双旋场景的测试⽤例
	int a[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
	for (auto e : a)
	{
		t.insert({ e, e });
	} 
	t.InOrder();
	cout << t.IsRBTree() << endl;
}
void TestRBTree2()
{
	const int N = 100000;
	vector<int> v;
	v.reserve(N);
	srand(time(0));
	for (size_t i = 0; i < N; i++)
	{
		v.push_back(rand() + i);
	}
	size_t begin2 = clock();
	RBTree<int, int> t;
	for (auto e : v)
	{
		t.insert(make_pair(e, e));
	} 
	size_t end2 = clock();
	cout << "Insert:" << end2 - begin2 << endl;
	cout << t.IsRBTree() << endl;
	cout << "Height:" << t.Height() << endl;
	cout << "Size:" << t.Size() << endl;
	size_t begin1 = clock();
	// 确定在的值
	for (auto e : v)
	{
		t.find(e);
	}
	// 随机值
	/*for (size_t i = 0; i < N; i++)
	{
		t.find((rand() + i));
	} */
	size_t end1 = clock();
	cout << "Find:" << end1 - begin1 << endl;
}
int main()
{
	TestRBTree2();
	/*RBTree<int, int> rbt;
	rbt.insert({ 29,29 });
	rbt.insert({ 2,2 });
	rbt.insert({ 9,9 });
	rbt.InOrder();
	cout << rbt.IsBalanceTree() << endl;*/
	return 0;
}
