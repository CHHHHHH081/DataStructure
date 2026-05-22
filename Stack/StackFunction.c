#define _CRT_SECURE_NO_WARNINGS
#include "Stack.h"
//初始化栈
void STInit(ST* pst)
{
	assert(pst);
	pst->a = NULL;
	pst->top = -1;
	pst->Capacity = 0;
}
//销毁栈
void STDestroy(ST* pst)
{
	assert(pst);
	free(pst->a);
	pst->a = NULL;
	pst->top = -1;
	pst->Capacity = 0;
}
//x入栈
void STpush(ST* pst, STDatatype x)
{
	assert(pst);
	STDatatype* ptmp=pst->a;
	if (pst->top + 1 == pst->Capacity)
	{
		pst->Capacity=pst->Capacity == 0 ? 4 : (2 * pst->Capacity);
		ptmp = (STDatatype*)realloc(ptmp, pst->Capacity*sizeof(STDatatype));
		if (ptmp)
		{
			pst->a = ptmp;
		}
		else
		{
			perror("realloc fail!");
		}
	}
	pst->top++;
	pst->a[pst->top] = x;
}
//出栈
void STpop(ST* pst)
{
	assert(pst);
	assert(pst->top != -1);
	pst->top--;
}
//打印栈
void STPrint(ST* pst)
{
	assert(pst);
	int tmp=pst->top;
	while (tmp != -1)
	{
		printf("%d ", pst->a[tmp]);
		tmp--;
	}
	printf("\n");
}
//获取栈顶元素
STDatatype STTop(ST* pst)
{
	assert(pst);
	return pst->a[pst->top];
}
//获取栈内有效元素个数
int STSize(ST* pst)
{
	assert(pst);
	return (pst->top + 1);
}
//检测栈是否为空
bool STEmpty(ST* pst)
{
	assert(pst);
	return pst->top == -1;		//空的话返回true，非空的话返回false
}