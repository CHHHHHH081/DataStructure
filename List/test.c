#define _CRT_SECURE_NO_WARNINGS
#include "SList.h"
void SLTtest()
{
	SLTNode* node1 = (SLTNode*)malloc(sizeof(SLTNode));
	node1->data = 1;
	SLTNode* node2 = (SLTNode*)malloc(sizeof(SLTNode));
	node2->data = 2;
	SLTNode* node3 = (SLTNode*)malloc(sizeof(SLTNode));
	node3->data = 3;
	SLTNode* node4 = (SLTNode*)malloc(sizeof(SLTNode));
	node4->data = 4;
	node1->next = node2;
	node2->next = node3;
	node3->next = node4;
	node4->next = NULL;
	SLTNode* plist = node1;
	SLTpushback(&plist, 5);
	SLTprint(plist);
	SLTpushback(&plist, 6);
	SLTprint(plist);
	SLTpushFront(&plist, 7);
	SLTprint(plist);
	SLTpopBack(&plist);
	SLTprint(plist);
	SLTpopBack(&plist);
	SLTprint(plist);
	SLTpopFront(&plist);
	SLTprint(plist);
	SLTpopFront(&plist);
	SLTprint(plist);
}
int main()
{
	SLTtest();
	return 0;
}