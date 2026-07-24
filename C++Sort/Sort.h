#pragma once
#include <iostream>
#include <climits>
#include <queue>
#include  <stack>
using namespace std;

int BinarySearch(int* arr, int n, int key);

void PrintArr(int* arr, int n);

void InsertSort(int* arr, int n);

void ShellSort(int* arr, int n);

void SelectSort(int* arr, int n);

void AdjustDown(int* arr, int n);

void HeapSort(int* arr, int n);

void STLHeapSort(int* arr, int n);

void BubbleSort(int* arr, int n);

void HoareQuickSort(int* arr, int left, int right);

void TwoPointerQuickSort(int* arr, int left, int right);

int GetMidi(int* arr, int left, int right);

void BetterHoareQuickSort(int* arr, int left, int right);

int PartQuickSort(int* arr, int left, int right);

void QuickSortNonR(int* arr, int left, int right);

void _MergeSort(int* arr, int* tmparr, int begin, int end);

void MergeSort(int* arr, int n);

void MergeSortNonR(int* arr, int n);

void CountSort(int* arr, int n);
