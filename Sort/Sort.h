#pragma once
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
//交换两数
void Swap(int* x, int* y);
//堆排序向下调整
void AdjustDown(int* arr, int parent, int n);
//打印数组
void PrintArr(int* arr,int n);
//冒泡排序（升序）O(n^2)（效率很低）
void BubbleSort(int* arr,int n);
//冒泡排序优化（升序）O(n^2)
void BetterBubbleSort(int* arr, int n);
//堆排序O(nlogn)
void HeapSort(int* arr, int n);
//插入排序（升序）O(n^2)
void InsertSort(int* arr,int n);
//希尔排序（升序）O(n^1.3)
void ShellSort(int* arr, int n);
//选择排序（升序）O(n^2)（效率很低）
void SelectSort(int* arr, int n);
//三数取中
int GetMidi(int* arr,int left,int right);
//霍尔法快速排序（升序）O(nlogn)
void HoareQuickSort(int* arr, int left, int right);
//双指针快速排序（升序）O(nlogn)
void TwoPointerQuickSort(int* arr, int left, int right);
//单趟快速排序
int PartQuickSort(int* arr, int left, int right);
//非递归快速排序（升序）O(nlogn)
void QuickSortNonR(int* arr, int left, int right);
//归并递归过程
void _MergeSort(int* arr, int* tmparr, int begin, int end);
//归并排序（升序）O(nlogn)
void MergeSort(int* arr, int n);
//非递归归并排序
void MergeSortNonR(int* arr,int n);
//计数排序
void CountSort(int* arr, int n);