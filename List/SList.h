#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
typedef int SLTDataType;
typedef struct SListNode
{
	SLTDataType data;
	struct SListNode* next;
}SLTNode;
//打印链表
void SLTprint(SLTNode* phead);
//尾插
void SLTpushback(SLTNode** pphead, SLTDataType x);
//头插
void SLTpushFront(SLTNode** pphead, SLTDataType x);
//尾删
void SLTpopBack(SLTNode** pphead);
//头删
void SLTpopFront(SLTNode** pphead);
//查找x
SLTNode* SLTFind(SLTNode* phead, SLTDataType x);
//在指定位置pos之前插入x
void SLTInsert(SLTNode** pphead, SLTNode* pos, SLTDataType x);
//在指定位置pos之后插入x
void SLTInsertAfter(SLTNode* pos, SLTDataType x);
//删除pos节点
void SLTErase(SLTNode** pphead, SLTNode* pos);
//删除pos之后的节点
void SLTEraseAfter(SLTNode* pos);
//销毁链表
void SListDestroy(SLTNode** pphead);