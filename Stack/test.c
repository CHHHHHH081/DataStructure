#define _CRT_SECURE_NO_WARNINGS
#include "Stack.h"
ST st;
bool flag;
void Test01()
{
	STInit(&st);
	STpush(&st, 1);
	STpush(&st, 2);
	STpush(&st, 3);
	STpush(&st, 4);
	STpush(&st, 5);
	STPrint(&st);
	STDatatype data = STTop(&st);
	printf("%d", data);
	STpop(&st);
	STPrint(&st);
	flag = STEmpty(&st);
	STpop(&st);
	STPrint(&st);
	flag = STEmpty(&st);
	STpop(&st);
	STPrint(&st);
	flag = STEmpty(&st);
	STpop(&st);
	STPrint(&st);
	flag = STEmpty(&st);
	STpop(&st);
	STPrint(&st);
	flag = STEmpty(&st);
	//STpop(&st);
	//STPrint(&st);
	STDestroy(&st);
}

int main()
{
	Test01();
	return 0;
}