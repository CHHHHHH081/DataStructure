#include "Sort.h"
#include"Stack.h"
//交换两数
void Swap(int* x, int* y)
{
	int tmp = *x;
	*x = *y;
	*y = tmp;
}
//堆排序向下调整
void AdjustDown(int* arr,int parent,int n)
{
	int child = parent * 2 + 1;
	while (child < n)
	{
		if (child + 1 < n && arr[child + 1] > arr[child])
			child++;
		if (arr[parent] < arr[child])
		{
			Swap(&(arr[parent]), &(arr[child]));
			parent = child;
			child = parent * 2 + 1;
		}
		else
			break;
	}
}
//打印数组
void PrintArr(int* arr,int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
}
//冒泡排序（升序）
void BubbleSort(int* arr,int n)
{
	for (int i = n-1; i>=0 ; i--)
	{
		for (int j = 0; j < i; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				Swap(&(arr[j]), &(arr[j + 1]));
			}
		}
	}
}
//冒泡排序优化（升序）
void BetterBubbleSort(int* arr, int n)
{
	bool flag = false;
	for (int i = n - 1; i >= 0; i--)
	{
		flag = false;
		for (int j = 0; j < i; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				Swap(&(arr[j]), &(arr[j + 1]));
				flag = true;
			}
		}
		if (flag == true)
			break;
	}
}
//堆排序（升序）
void HeapSort(int* arr, int n)
{
	//建大堆
	for (int k = (n - 1) / 2; k >= 0; k--)
	{
		AdjustDown(arr, k, n);
	}
	for (int i = n - 1; i > 0; i--)
	{
		Swap(&(arr[0]), &arr[i]);
		AdjustDown(arr, 0, i);
	}
}
//插入排序（升序）
void InsertSort(int* arr,int n)
{
	int end;
	int key;
	for (int i = 0; i < n-1; i++)
	{
		end = i;
		key = arr[end+1];
		while (end >= 0)
		{
			if (key < arr[end])
			{
				arr[end + 1] = arr[end];
				end--;
			}
			else
				break;
		}
		arr[end+1] = key;
	}
}
//希尔排序（升序）O(n^1.3)
void ShellSort(int* arr, int n)
{
	int gap = n;
	int end;
	int key;
	while (gap > 1)
	{
		gap = gap / 3 + 1;
		for (int j = 0; j < gap; j++)
		{
			for (int i = j; i < n - gap; i += gap)
			{
				end = i;
				key = arr[end + gap];
				while (end >= 0)
				{
					if (key < arr[end])
					{
						arr[end + gap] = arr[end];
						end -= gap;
					}
					else
					{
						break;
					}
				}
				arr[end + gap] = key;
			}
		}
	}
}
//选择排序（升序）O(n^2)（效率很低）
void SelectSort(int* arr, int n)
{
	int mini = 0;
	for (int i = 0; i < n; i++)
	{
		mini = i;
		for (int j = i; j < n; j++)
		{
			if (arr[j] < arr[mini])
				mini = j;
		}
		Swap(&arr[i], &arr[mini]);
	}
}
//三数取中
int GetMidi(int* arr, int left, int right)
{
	int midi = (left + right) / 2;
	if (arr[left] < arr[midi])
	{
		if (arr[midi] < arr[right])
			return midi;
		else if (arr[left] < arr[right])
			return right;
		else
			return left;
	}
	else//arr[midi]<arr[left]
	{
		if (arr[left] < arr[right])
			return left;
		else if (arr[midi] < arr[right])
			return right;
		else
			return midi;
	}
}
//快速排序（升序）O(nlogn)
void HoareQuickSort(int* arr, int left, int right)
{
	if (left >= right)
		return;
	//小区间优化
	if (right - left + 1 < 10)
		InsertSort(arr + left, right - left + 1);
	//三数取中
	int midi = GetMidi(arr, left, right);
	Swap(&arr[left], &arr[midi]);
	int keyi = left;
	int begin = keyi;
	int end = right;
	while (begin < end)
	{
		//右边找小
		while (begin < end && arr[end] >= arr[keyi])
		{
			end--;
		}
		//左边找大
		while (begin < end && arr[begin] <= arr[keyi])
		{
			begin++;
		}
		Swap(&arr[begin], &arr[end]);
	}
	Swap(&arr[keyi], &arr[begin]);
	keyi = begin;
	HoareQuickSort(arr, left, keyi - 1);
	HoareQuickSort(arr, keyi + 1, right);
}
//双指针快速排序（升序）O(nlogn)
void TwoPointerQuickSort(int* arr, int left, int right)
{
	if (left >= right)
		return;
	//小区间优化
	if (right - left + 1 < 10)
		InsertSort(arr+left, right - left + 1);
	//三数取中
	int midi = GetMidi(arr, left, right);
	Swap(&arr[midi], &arr[left]);
	int keyi = left;
	int prev = left;
	int cur = prev + 1;
	while (cur <= right)
	{
		//cur找小，与prev交换
		if (arr[cur] < arr[keyi] && ++prev != cur)
			Swap(&arr[cur], &arr[prev]);
		cur++;
	}
	Swap(&arr[keyi], &arr[prev]);
	keyi = prev;
	TwoPointerQuickSort(arr, left, keyi - 1);
	TwoPointerQuickSort(arr, keyi + 1, right);
}
//单趟快速排序
int PartQuickSort(int* arr, int left, int right)
{
	int midi = GetMidi(arr, left, right);
	Swap(&arr[midi], &arr[left]);
	int keyi = left;
	int begin = left;
	int end = right;
	while (begin < end)
	{
		//右边找小
		while (begin<end && arr[end] >= arr[keyi])
			end--;
		//左边找大
		while (begin<end && arr[begin] <= arr[keyi])
			begin++;
		Swap(&arr[begin], &arr[end]);
	}
	Swap(&arr[keyi], &arr[begin]);
	keyi = begin;
	return keyi;
}
//非递归快速排序（升序）O(nlogn)
void QuickSortNonR(int* arr, int left, int right)
{
	ST st;
	STInit(&st);
	STpush(&st, right);
	STpush(&st, left);
	int keyi;
	int begin, end;
	while (!STEmpty(&st))
	{
		begin = STTop(&st);
		STpop(&st);
		end = STTop(&st);
		STpop(&st);
		keyi = PartQuickSort(arr, begin, end);
		if (begin < keyi-1)
		{
			STpush(&st, keyi - 1);
			STpush(&st, begin);
		}
		if (keyi + 1 < end)
		{
			STpush(&st, end);
			STpush(&st, keyi + 1);
		}
	}
	STDestroy(&st);
}
//归并过程
void _MergeSort(int* arr, int* tmparr, int begin, int end)
{
	if (begin >= end)
		return;
	int midi = (begin + end) / 2;
	_MergeSort(arr,tmparr, begin, midi);
	_MergeSort(arr,tmparr, midi + 1, end);
	int begin1 = begin;
	int end1 = midi;
	int begin2 = midi + 1;
	int end2 = end;
	int i = begin;
	while ((begin1 <= end1) && (begin2 <= end2))
	{
		if (arr[begin1] < arr[begin2])
			tmparr[i++] = arr[begin1++];
		else
			tmparr[i++] = arr[begin2++];
	}
	while (begin1 <= end1)
	{
		tmparr[i++] = arr[begin1++];
	}
	while (begin2 <= end2)
	{
		tmparr[i++] = arr[begin2++];
	}
	memcpy(arr+begin, tmparr+begin, (end - begin + 1) * sizeof(int));
}
//归并排序（升序）O(nlogn)
void MergeSort(int* arr, int n)
{
	int* tmparr = (int*)malloc(n * sizeof(int));
	if (tmparr == NULL)
	{
		perror("Malloc fail!");
		return;
	}
	_MergeSort(arr, tmparr, 0, n - 1);
	free(tmparr);
}
//非递归归并排序
void MergeSortNonR(int* arr, int n)
{
	int* tmparr = (int*)malloc(n * sizeof(int));
	if (tmparr == NULL)
	{
		perror("Malloc fail!");
		return;
	}
	//gap表示每次的元素个数
	int gap = 1;
	while(gap < n)
	{
		//i表示每次的起始位置
		for (int i = 0; i < n; i += 2 * gap)
		{
			int begin1 = i;
			int end1 = i + gap - 1;
			int begin2 = i + gap;
			int end2 = i + 2 * gap - 1;
			//第二组数据不存在，第一组已经有序
			if (end1 >= n)
				break;
			//第二组存在，需要修正end2
			if (end2 >= n)
				end2 = n - 1;
			int j = i;
			while (begin1 <= end1 && begin2 <= end2)
			{
				if (arr[begin1] < arr[begin2])
					tmparr[j++] = arr[begin1++];
				else
					tmparr[j++] = arr[begin2++];
			}
			while (begin1 <= end1)
			{
				tmparr[j++] = arr[begin1++];
			}
			while (begin2 <= end2)
			{
				tmparr[j++] = arr[begin2++];
			}
			memcpy(arr + i, tmparr + i, (end2 - i + 1)* sizeof(int));
		}
		gap *= 2;
	}
	free(tmparr);
}
//计数排序
void CountSort(int* arr, int n)
{
	int min = 1e6;
	int max = -1e6;
	for (int i = 0; i < n; i++)
	{
		if (arr[i] < min)
			min = arr[i];
		if (arr[i] > max)
			max = arr[i];
	}
	int* count = (int*)calloc(max - min + 1, sizeof(int));
	if (count == NULL)
	{
		perror("Malloc fail!");
		return;
	}
	for (int i = 0; i < n; i++)
	{
		count[arr[i] - min]++;
	}
	int i = 0;
	int j = 0;
	while (j < n)
	{
		if (count[i] == 0)
			i++;
		else
		{
			arr[j] = i+min;
			count[i]--;
			j++;
		}
	}
	free(count);
}