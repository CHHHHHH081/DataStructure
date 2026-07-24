#include "Sort.h"
#include <climits>
#include <iostream>
#include <ostream>
#include <queue>
#include <stack>
#include <utility>
#include <vector>

int BinarySearch(int *arr, int n, int key)
{
	int left = 0, right = n - 1, mid;
	while (left <= right)
	{
		mid = (left + right) / 2;
		if (arr[mid] > key)
			right = mid - 1;
		else if (arr[mid < key])
			left = mid + 1;
		else
			return mid;
	}
	return -1;
}

void PrintArr(int *arr, int n)
{
	for (int i = 0; i < n; i++)
		cout << arr[i] << ' ';
	cout << endl;
}

void InsertSort(int *arr, int n)
{
	int key, end;
	for (int i = 0; i < n - 1; i++)
	{
		end = i;			// 已排序区间为[0,end]
		key = arr[end + 1]; // 记录arr[end+1]
		while (end >= 0 && arr[end] > key)
		{
			// 比key大，移位
			arr[end + 1] = arr[end];
			end--;
		}
		arr[end + 1] = key;
	}
}

void ShellSort(int *arr, int n)
{
	int gap = n, key, end;
	while (gap > 1)
	{
		gap = gap / 3 + 1;
		for (int j = 0; j < gap; j++)
		{
			for (int i = j; i < n - gap; i += gap)
			{
				end = i;
				key = arr[end + gap];
				while (end >= 0 && arr[end] > key)
				{
					arr[end + gap] = arr[end];
					end -= gap;
				}
				arr[end + gap] = key;
			}
		}
	}
}

void SelectSort(int *arr, int n)
{
	int minj, mink = INT_MAX;
	for (int i = 0; i < n - 2; i++)
	{
		minj = i;
		mink = arr[minj];
		for (int j = i; j < n; j++)
		{
			if (arr[j] < mink)
			{
				minj = j;
				mink = arr[j];
			}
		}
		swap(arr[i], arr[minj]);
	}
}

// 向下调整
void AdjustDown(int *arr, int parent, int n)
{
	int child = parent * 2 + 1;
	while (child < n)
	{
		if (child + 1 < n && arr[child + 1] > arr[child])
			++child;
		if (arr[parent] < arr[child])
			swap(arr[parent], arr[child]);
		else
			break;
		parent = child;
		child = parent * 2 + 1;
	}
}

void HeapSort(int *arr, int n)
{
	// 建大堆，从第一个非叶子节点开始向下调整
	for (int k = (n - 1) / 2; k >= 0; k--)
	{
		AdjustDown(arr, k, n);
	}
	for (int i = n - 1; i >= 0; i--)
	{
		swap(arr[i], arr[0]);
		AdjustDown(arr, 0, i);
	}
}

void STLHeapSort(int *arr, int n)
{
	priority_queue<int, vector<int>, greater<int>> pq;
	for (int i = 0; i < n; i++)
		pq.push(arr[i]);
	for (int i = 0; i < n; i++)
	{
		arr[i] = pq.top();
		pq.pop();
	}
}

void BubbleSort(int *arr, int n)
{
	int flag = 0;
	for (int i = n - 1; i >= 0; i--)
	{
		for (int j = 0; j < i; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				swap(arr[j], arr[j + 1]);
				flag = 1;
			}
		}
		if (flag == 0)
			break;
	}
}

void HoareQuickSort(int *arr, int left, int right)
{
	if (left >= right)
		return;
	int keyi = left;
	int begin = keyi, end = right;
	while (begin < end)
	{
		// end找小
		while (begin < end && arr[end] >= arr[keyi])
			end--;
		// begin找大
		while (begin < end && arr[begin] <= arr[keyi])
			begin++;
		swap(arr[begin], arr[end]);
	}
	swap(arr[keyi], arr[end]);
	keyi = end;
	HoareQuickSort(arr, left, keyi - 1);
	HoareQuickSort(arr, keyi + 1, right);
}

void TwoPointerQuickSort(int *arr, int left, int right)
{
	if (left > right)
		return;
	int keyi = left;
	int prev = keyi, cur = prev + 1;
	while (cur <= right)
	{
		// cur找小，找到后prev++，如果prev!=cur，再与prev交换
		if (arr[cur] < arr[keyi] && ++prev != cur)
			swap(arr[cur], arr[prev]);
		cur++;
	}
	swap(arr[keyi], arr[prev]);
	keyi = prev;
	TwoPointerQuickSort(arr, left, keyi - 1);
	TwoPointerQuickSort(arr, keyi + 1, right);
}

// 三数取中
int GetMidi(int *arr, int left, int right)
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
	else // arr[midi]<arr[left]
	{
		if (arr[left] < arr[right])
			return left;
		else if (arr[midi] < arr[right])
			return right;
		else
			return midi;
	}
}

void BetterHoareQuickSort(int *arr, int left, int right)
{
	if (left >= right)
		return;
	// 小区间优化
	if (right - left + 1 <= 16)
	{
		InsertSort(arr, right - left + 1);
		return;
	}
	// 三数取中
	int midi = GetMidi(arr, left, right);
	swap(arr[midi], arr[left]);
	int keyi = left;
	int begin = keyi + 1, end = right;
	while (begin < end)
	{
		// end找小
		while (begin < end && arr[end] >= arr[keyi])
			end--;
		// begin找大
		while (begin < end && arr[begin] <= arr[keyi])
			begin++;

		swap(arr[begin], arr[end]);
	}
	swap(arr[keyi], arr[end]);
	keyi = end;
	BetterHoareQuickSort(arr, left, keyi - 1);
	BetterHoareQuickSort(arr, keyi + 1, right);
}

int PartQuickSort(int *arr, int left, int right)
{
	int midi = GetMidi(arr, left, right);
	swap(arr[midi], arr[left]);
	int keyi = left;
	int begin = keyi, end = right;
	while (begin < end)
	{
		// end找小
		while (begin < end && arr[end] >= arr[keyi])
			end--;
		// begin找大
		while (begin < end && arr[begin] <= arr[keyi])
			begin++;
		swap(arr[begin], arr[end]);
	}
	swap(arr[keyi], arr[end]);
	keyi = end;
	return keyi;
}

void QuickSortNonR(int *arr, int left, int right)
{
	stack<int> st;
	st.push(right);
	st.push(left);
	int begin, end, keyi;
	while (!st.empty())
	{
		begin = st.top();
		st.pop();
		end = st.top();
		st.pop();
		keyi = PartQuickSort(arr, begin, end);
		if (begin < keyi - 1)
		{
			st.push(keyi - 1);
			st.push(begin);
		}
		if (end > keyi + 1)
		{
			st.push(end);
			st.push(keyi + 1);
		}
	}
}

void _MergeSort(int *arr, int *tmparr, int begin, int end)
{
	if (begin >= end)
		return;
	int midi = (begin + end) / 2;
	_MergeSort(arr, tmparr, begin, midi);
	_MergeSort(arr, tmparr, midi + 1, end);
	int begin1 = begin, end1 = midi, begin2 = midi + 1, end2 = end, cur = begin;
	while (begin1 <= end1 && begin2 <= end2)
	{
		if (arr[begin1] < arr[begin2])
			tmparr[cur++] = arr[begin1++];
		else
			tmparr[cur++] = arr[begin2++];
	}
	while (begin1 <= end1)
		tmparr[cur++] = arr[begin1++];
	while (begin2 <= end2)
		tmparr[cur++] = arr[begin2++];
	memcpy(arr + begin, tmparr + begin, (end - begin + 1) * sizeof(int));
}

void MergeSort(int *arr, int n)
{
	int *tmparr = new int[n];
	_MergeSort(arr, tmparr, 0, n - 1);
	delete[] tmparr;
}

void MergeSortNonR(int *arr, int n)
{
	int *tmparr = new int[n];
	// gap表示每次的元素个数
	int gap = 1;
	while (gap < n)
	{
		// i表示每次的起始位置
		for (int i = 0; i < n; i += 2 * gap)
		{
			int begin1 = i;
			int end1 = i + gap - 1;
			int begin2 = i + gap;
			int end2 = i + 2 * gap - 1;
			// 第二组数据不存在，第一组已经有序
			if (end1 >= n)
				break;
			// 第二组存在，需要修正end2
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
			memcpy(arr + i, tmparr + i, (end2 - i + 1) * sizeof(int));
		}
		gap *= 2;
	}
	delete[] tmparr;
}

void CountSort(int *arr, int n)
{
	if (n <= 0)
		return;

	int min = arr[0];
	int max = arr[0];
	for (int i = 1; i < n; i++)
	{
		if (arr[i] < min)
			min = arr[i];
		if (arr[i] > max)
			max = arr[i];
	}

	int range = max - min + 1;
	int *count = new int[range]();
	for (int i = 0; i < n; i++)
	{
		count[arr[i] - min]++;
	}

	int idx = 0;
	int j = 0;
	while (j < n && idx < range)
	{
		if (count[idx] == 0)
			idx++;
		else
		{
			arr[j] = idx + min;
			count[idx]--;
			j++;
		}
	}
	delete[] count;
}
