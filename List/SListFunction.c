#define _CRT_SECURE_NO_WARNINGS
#include "SList.h"
void SLTprint(SLTNode* phead)
{
	SLTNode* pcur = phead;
	while (pcur)
	{
		printf("%d->", pcur->data);
		pcur = pcur->next;
	}
	printf("NULL\n");
}
SLTNode* SLTNodeBuy(SLTDataType x)
{
	SLTNode* newnode = (SLTNode*)malloc(sizeof(SLTNode));
	if (newnode == NULL)
	{
		perror("malloc fail!");
		exit(1);
	}
	newnode->data = x;
	newnode->next = NULL;
	return newnode;
}
void SLTpushback(SLTNode** pphead, SLTDataType x)
{
	assert(pphead);
	SLTNode* new=SLTNodeBuy(x);
	if (*pphead)
	{
		SLTNode* ptail = *pphead;
		while (ptail->next != NULL)
		{
			ptail = ptail->next;
		}
		ptail->next = new;
	}
	else
	{
		*pphead = new;
	}
}
void SLTpushFront(SLTNode** pphead, SLTDataType x)
{
	assert(pphead);
	SLTNode* new = SLTNodeBuy(x);
	new->next = *pphead;
	*pphead = new;
}
void SLTpopBack(SLTNode** pphead)
{
	assert(pphead && *pphead);
	if ((*pphead)->next == NULL)
	{
		free(*pphead);
		*pphead = NULL;
	}
	else
	{
		SLTNode* ptail = *pphead;
		SLTNode* prev = *pphead;
		while (ptail->next != NULL)
		{
			prev = ptail;
			ptail = ptail->next;
		}
		free(ptail);
		ptail = NULL;
		prev->next = NULL;
	}
}
void SLTpopFront(SLTNode** pphead)
{
	assert(pphead && *pphead);
	SLTNode* Next = (*pphead)->next;
	free(*pphead);
	*pphead = Next;
}
SLTNode* SLTFind(SLTNode* phead, SLTDataType x)
{
	SLTNode* pcur = phead;
	while (pcur->data != x && pcur->next==NULL)
	{
		pcur = pcur->next;
	}
	if (pcur == NULL)
	{
		return NULL;
	}
	else
	{
		return pcur;
	}
}
void SLTInsert(SLTNode** pphead, SLTNode* pos, SLTDataType x)
{
	assert(pphead && *pphead);
	if (pos == *pphead)
	{
		SLTpushFront(pphead, x);
		exit(0);
	}
	SLTNode* prev = *pphead;
	while (prev->next != pos)
	{
		prev = prev->next;
	}
	SLTNode* newnode = SLTNodeBuy(x);
	newnode->next = pos;
	prev->next = newnode;
}
void SLTInsertAfter(SLTNode* pos, SLTDataType x)
{
	assert(pos);
	SLTNode* Next = pos->next;
	SLTNode* newnode = SLTNodeBuy(x);
	newnode->next = Next;
	pos->next = newnode;
}
void SLTErase(SLTNode** pphead, SLTNode* pos)
{
	assert(pphead && *pphead);
	assert(pos);
	if (pos == *pphead)
	{
		SLTpopFront(pphead);
	}
	else
	{
		SLTNode* prev = *pphead;
		while (prev->next != pos)
		{
			prev = prev->next;
		}
		prev->next = pos->next;
		free(pos);
		pos = NULL;
	}
}
void SLTEraseAfter(SLTNode* pos)
{
	assert(pos && pos->next);
	SLTNode* del = pos->next;
	pos->next = pos->next->next;
	free(del);
	del = NULL;
}
void SListDestroy(SLTNode** pphead)
{
	assert(pphead && *pphead);
	SLTNode* pcur = *pphead;
	while (pcur)
	{
		SLTNode* next = pcur->next;
		free(pcur);
		pcur = next;
	}
	*pphead = NULL;
}