#define _CRT_SECURE_NO_WARNINGS
#include "Sort.h"
void test01()
{
	int arr[] = { 2,3,6,1,0,5,9,8,7,4,4,4,90,38 };
	PrintArr(arr, sizeof(arr)/sizeof(int));
	/*BubbleSort(arr, 10);*/
	/*InsertSort(arr, 10);*/
	/*HeapSort(arr, 10);*/
	/*ShellSort(arr, 40);*/
	/*SelectSort(arr, 40);*/
	/*HoareQuickSort(arr, 0, 39);*/
	TwoPointerQuickSort(arr, 0, 13);
	/*QuickSortNonR(arr, 0, 39);*/
	/*MergeSort(arr, 10);*/
	/*MergeSortNonR(arr, sizeof(arr)/sizeof(int));*/
	/*CountSort(arr, sizeof(arr) / sizeof(int));*/
	PrintArr(arr, sizeof(arr)/sizeof(int));
}
int main()
{
	test01();
	return 0;
}