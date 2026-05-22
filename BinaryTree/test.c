#include "BinaryTree.h"
BTNode* CreatBinaryTree()
{
	BTNode* node1=BuyNode(1);
	BTNode* node2=BuyNode(2);
	BTNode* node3=BuyNode(3);
	BTNode* node4=BuyNode(4);
	BTNode* node5=BuyNode(5);
	BTNode* node6=BuyNode(6);
	node1->left = node2;
	node2->left = node4;
	node1->right = node3;
	node3->left = node5;
	node3->right = node6;
	return node1;
}
void test()
{
	BTNode* root = CreatBinaryTree();
	printf("PreOrder Traversal:");
	PreOrder(root);
	printf("\n");
	printf("InOrder Traversal:");
	InOrder(root);
	printf("\n");
	printf("PostOrder Traversal:");
	PostOrder(root);
	printf("\n");
	printf("LevelOrder Traversal:");
	LevelOrder(root);
	printf("\n");
	int size = TreeSize(root);
	printf("Size:%d\n", size);
	int leafsize = TreeLeafSize(root);
	printf("LeafSize:%d\n", leafsize);
	int height = TreeHeight(root);
	printf("Height:%d\n", height);
	TreeDestroy(root);
}
int main()
{
	test();
	return 0;
}