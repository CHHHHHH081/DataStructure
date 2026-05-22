#define _CRT_SECURE_NO_WARNINGS
#include "Heap.h"
void Swap(HeapDataType* p1, HeapDataType* p2)
{
	HeapDataType tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}
void HPInit(HP* hp)
{
	assert(hp);
	hp->a = NULL;
	hp->size = hp->capacity = 0;
}
void HPDestroy(HP* hp)
{
	assert(hp);
	free(hp->a);
	hp->a = NULL;
	hp->size = hp->capacity = 0;
}
void HPPush(HP* hp, HeapDataType x)
{
	assert(hp);
	if (hp->size == hp->capacity)
	{
		int newCapacity = hp->capacity == 0 ? 4 : (2 * hp->capacity);
		HeapDataType* ptmp = (HeapDataType*)realloc(hp->a, hp->capacity * sizeof(HeapDataType));
		if (ptmp == NULL)
		{
			perror("Realloc fail!");
			return;
		}
		hp->a = ptmp;
		hp->capacity = newCapacity;
	}
	hp->a[hp->size] = x;
	AdjustUp(hp->a, hp->size);
	hp->size++;
}
void HPPop(HP* hp)
{
	assert(hp);
	assert(hp->size != 0);
	Swap(&(hp->a[0]), &(hp->a[hp->size - 1]));
	hp->size--;
	AdjustDown(hp->a, 0, hp->size);
}
void AdjustUp(HeapDataType* a,int child)
{
	assert(a);
	while (child > 0)
	{
		int parent = (child - 1) / 2;
		//此处大堆为>，小堆为<
		if (a[child] > a[parent])
		{
			Swap(&(a[child]), &(a[parent]));
			child = parent;
		}
		else
		{
			break;
		}
	}
}
void AdjustDown(HeapDataType* a, int parent,int n)
{
	assert(a);
	int child = parent * 2 + 1;
	while (child < n)
	{
		//此处是大堆，小堆条件反之
		if (child+1<n&&a[child] < a[child + 1])
		{
			child++;
		}
		//此处是大堆，小堆条件反之
		if (a[parent] < a[child])
		{
			Swap(&(a[parent]), &a[child]);
			parent = child;
			child = parent * 2 + 1;
		}
		else
		{
			break;
		}
	}
}
void HPSort(HeapDataType* a, int n)
{
	if (a == NULL || n <= 1)
	{
		return;
	}
	//建大堆
	for (int k = n / 2 - 1; k >= 0; --k)
	{
		AdjustDown(a, k, n);
	}
	//排序
	for (int i = n - 1; i > 0; --i)
	{
		Swap(&(a[0]), &(a[i]));
		AdjustDown(a, 0, i);
	}
}