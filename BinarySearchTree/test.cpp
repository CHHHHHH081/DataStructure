#define _CRT_SECURE_NO_WARNINGS
#include "BSTree.h"

int main()
{
	int arr[9] = { 8,3,10,1,6,14,4,7,13 };
	key::BSTree<int> t;
	for (auto i : arr)
	{
		t.Insert(i);
	}
	t.InOrder();
	t.erase(10);
	t.erase(1);
	t.InOrder();
	key::BSTree<int> t1=t;
	t1.InOrder();

	return 0;
}