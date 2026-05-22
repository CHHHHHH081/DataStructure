#include "Queue.h"
//队列初始化
void QueueInit(Queue* pq)
{
	assert(pq);
	pq->phead = NULL;
	pq->ptail = NULL;
	pq->size = 0;
}
//出队
void Queuepop(Queue* pq)
{
	assert(pq);
	assert(pq->size != 0);
	if (pq->phead->next == NULL)
	{
		free(pq->phead);
		pq->phead = pq->ptail = NULL;
	}
	else
	{
		QNode* next = pq->phead->next;
		free(pq->phead);
		pq->phead = next;
	}
	pq->size--;
}
//入队
void Queuepush(Queue* pq, QDataType x)
{
	assert(pq);
	QNode* newnode = (QNode*)malloc(sizeof(QNode));
	if (newnode == NULL)
	{
		perror("malloc fail!");
		return;
	}
	newnode->val = x;
	newnode->next = NULL;
	if (pq->ptail == NULL)
	{
		pq->ptail = newnode;
		pq->phead = newnode;
	}
	else
	{
		pq->ptail->next = newnode;
		pq->ptail = newnode;
	}
	pq->size++;
}
//获取队头元素
QDataType QueueFront(Queue* pq)
{
	assert(pq);
	assert(pq->size!=0);
	return pq->phead->val;
}
//获取队尾元素
QDataType QueueBack(Queue* pq)
{
	assert(pq);
	assert(pq->size != 0);
	return pq->ptail->val;
}
//获取队列元素个数
int QueueSize(Queue* pq)
{
	assert(pq);
	return pq->size;
}
//判断队列是否为空，非空返回0，空返回1
bool QueueEmpty(Queue* pq)
{
	assert(pq);
	return pq->size!=0 ? false : true;
}
//销毁队列
void QueueDestroy(Queue* pq)
{
	assert(pq);
	QNode* pcur=pq->phead;
	while (pcur)
	{
		QNode* next = pcur->next;
		free(pcur);
		pcur = next;
	}
	pq->phead = NULL;
	pq->ptail = NULL;
	pq->size = 0;
}