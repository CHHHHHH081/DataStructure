#include "Sort.h"


void Test01()
{
	int arr[] = { 3,6,7,1,5,4,9,8,2 };
	InsertSort(arr, 9);
	PrintArr(arr, 9);
}

void Test02()
{
	int arr[] = { 3,6,7,1,5,4,9,8,2 };
	ShellSort(arr, 9);
	PrintArr(arr, 9);
}

void Test03()
{
	int arr[] = { 3,6,7,1,5,4,9,8,2,-9,6 };
	SelectSort(arr, 11);
	PrintArr(arr, 11);
}

void Test04()
{
	int arr[] = { 3,6,7,1,5,4,9,8,2,-9,6 };
	HeapSort(arr, 11);
	PrintArr(arr, 11);
}

void Test05()
{
	int arr[] = { 3,6,7,1,5,4,9,8,2,-9,6,-4 };
	STLHeapSort(arr, 12);
	PrintArr(arr, 12);
}

void Test06()
{
	int arr[] = { 3,6,7,1,5,4,9,8,2,-9,6,-4 };
	BubbleSort(arr, 12);
	PrintArr(arr, 12);
}

void Test07()
{
	int arr[] = { 3,6,7,1,5,4,9,8,2,-9,6,-4 };
	HoareQuickSort(arr, 0,11);
	PrintArr(arr, 12);
}

void Test08()
{
	int arr[] = { 3,6,7,1,5,4,9,8,2,-9,6,-4 };
	TwoPointerQuickSort(arr, 0, 11);
	PrintArr(arr, 12);
}

void Test09()
{
	int arr[] = { 3,6,7,1,5,4,9,8,2,-9,6,-4 };
	BetterHoareQuickSort(arr, 0, 11);
	PrintArr(arr, 12);
}

void Test10()
{
	int arr[] = { 3,6,7,1,5,4,9,8,2,-9,6,-4 };
	QuickSortNonR(arr, 0, 11);
	PrintArr(arr, 12);
}

void Test11()
{
	int arr[] = { 3,6,7,1,5,4,9,8,2,-9,6,-4 };
	MergeSort(arr, 12);
	PrintArr(arr, 12);
}

void Test12()
{
	int arr[] = { 3,6,7,1,5,4,9,8,2,-9,6,-4 };
	MergeSortNonR(arr, 12);
	PrintArr(arr, 12);
}

void Test13()
{
	int arr[] = { 3,6,7,1,5,4,9,8,2,-9,6,-4 };
	CountSort(arr, 12);
	PrintArr(arr, 12);
}

int main()
{
	Test13();
	return 0;
}