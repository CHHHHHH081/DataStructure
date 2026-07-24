#define _CRT_SECURE_NO_WARNINGS
#include "Queue.h"
Queue q;
QDataType data;
void Test()
{
	QueueInit(&q);
	Queuepush(&q, 1);
	printf("%d ", QueueBack(&q));
	Queuepush(&q, 2);
	printf("%d ", QueueBack(&q));
	Queuepush(&q, 3);
	printf("%d ", QueueBack(&q));
	Queuepush(&q, 4);
	printf("%d ", QueueBack(&q));
	QueueDestroy(&q);
	/*Queuepop(&q);
	printf("%d ", QueueFront(&q));
	Queuepop(&q);
	printf("%d ", QueueFront(&q));
	Queuepop(&q);
	printf("%d ", QueueFront(&q));
	Queuepop(&q);
	printf("%d ", QueueFront(&q));*/
}
int main()
{
	Test();
	return 0;
}