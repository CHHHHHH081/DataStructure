#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
typedef int HeapDataType;
//堆
typedef struct Heap 
{
	HeapDataType* a;
	int size;
	int capacity;
}HP;
//交换两数
void Swap(HeapDataType* p1, HeapDataType* p2);
//初始化堆
void HPInit(HP* hp);
//销毁堆
void HPDestroy(HP* hp);
//将x入堆
void HPPush(HP* hp, HeapDataType x);
//删除堆顶
void HPPop(HP* hp);
//将指定节点向上调整
void AdjustUp(HeapDataType* a,int child);
//将指定节点向下调整
void AdjustDown(HeapDataType* a, int parent,int n);
//堆排序
void HPSort(HeapDataType* a,int n);