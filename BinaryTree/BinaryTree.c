#include "BinaryTree.h"
#include "Queue.h"
//创造节点
BTNode* BuyNode(BTDatatype x)
{
	BTNode* newnode = (BTNode*)malloc(sizeof(BTNode));
	if (newnode == NULL)
	{
		perror("Malloc fail!");
		return;
	}
	newnode->data = x;
	newnode->left = NULL;
	newnode->right = NULL;
	return newnode;
}
//前序遍历
void PreOrder(BTNode* root)
{
	if (root == NULL)
	{
		printf("N ");
		return;
	}
	printf("%d ", root->data);
	PreOrder(root->left);
	PreOrder(root->right);
}
//中序遍历
void InOrder(BTNode* root)
{
	if (root == NULL)
	{
		printf("N ");
		return;
	}
	InOrder(root->left);
	printf("%d ", root->data);
	InOrder(root->right);
}
//后序遍历
void PostOrder(BTNode* root)
{
	if (root == NULL)
	{
		printf("N ");
		return;
	}
	PostOrder(root->left);
	PostOrder(root->right);
	printf("%d ", root->data);
}
//层序遍历
void LevelOrder(BTNode* root)
{
	if (root == NULL)
		printf("");
	Queue* pq=(Queue*)malloc(sizeof(Queue));
	QueueInit(pq);
	Queuepush(pq, root);
	while (!QueueEmpty(pq))
	{
		BTNode* front = QueueFront(pq);
		Queuepop(pq);
		printf("%d ", front->data);
		if (front->left)
			Queuepush(pq, front->left);
		if (front->right)
			Queuepush(pq, front->right);
	}
	QueueDestroy(pq);
	free(pq);
}
//结点数量
int TreeSize(BTNode* root)
{
	if (root == NULL)
	{
		return 0;
	}
	return TreeSize(root->left) + TreeSize(root->right) + 1;
}
//叶子结点数量
int TreeLeafSize(BTNode* root)
{
	if (root == NULL)
	{
		return 0;
	}
	if (root->left == NULL && root->right == NULL)
	{
		return 1;
	}
	return TreeLeafSize(root->left) + TreeLeafSize(root->right);
}
//树的高度
int TreeHeight(BTNode* root)
{
	if (root == NULL)
	{
		return 0;
	}
	int lefttree = TreeHeight(root->left);
	int righttree = TreeHeight(root->right);
	return lefttree > righttree ? (lefttree + 1) : (righttree + 1);
}
//查找值为x的节点
BTNode* TreeFind(BTNode* root, BTDatatype x)
{
	if (root == NULL)
	{
		return NULL;
	}
	if (root->data == x)
	{
		return root;
	}
	BTNode* node1=TreeFind(root->left, x);
	if (node1 != NULL)
	{
		return node1;
	}
	BTNode* node2 = TreeFind(root->right, x);
	if (node2 != NULL)
	{
		return node2;
	}
	return NULL;
}
//销毁树
void TreeDestroy(BTNode* root)
{
	if (root == NULL)
		return;
	TreeDestroy(root->left);
	TreeDestroy(root->right);
	free(root);
}