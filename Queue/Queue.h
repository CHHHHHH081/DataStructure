#pragma once
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
typedef int QDataType;
typedef struct QListNode
{
	struct QListNode* next;
	QDataType val;
}QNode;
typedef struct Queue
{
	QNode* phead;
	QNode* ptail;
	int size;
}Queue;
//队列初始化
void QueueInit(Queue* pq);
//出队
void Queuepop(Queue* pq);
//入队
void Queuepush(Queue* pq, QDataType x);
//获取队头元素
QDataType QueueFront(Queue* pq);
//获取队尾元素
QDataType QueueBack(Queue* pq);
//获取队列元素个数
int QueueSize(Queue* pq);
//判断队列是否为空，非空返回0，空返回1
int QueueEmpty(Queue* pq);
//销毁队列
void QueueDestroy(Queue* pq);