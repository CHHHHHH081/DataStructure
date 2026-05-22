#pragma once
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
typedef int STDatatype;
typedef struct Stack
{
	STDatatype* a;
	int top;
	int Capacity;
}ST;
//初始化栈
void STInit(ST* pst);
//销毁栈
void STDestroy(ST* pst);
//x入栈
void STpush(ST* pst, STDatatype x);
//出栈
void STpop(ST* pst);
//打印栈
void STPrint(ST* pst);
//获取栈顶元素
STDatatype STTop(ST* pst);
//获取栈内有效元素个数
int STSize(ST* pst);
//检测栈是否为空
bool STEmpty(ST* pst);