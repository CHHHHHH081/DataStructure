#pragma once
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
typedef int BTDatatype;
//二叉树
typedef struct BinaryTree
{
	BTDatatype data;
	struct BinaryTree* left;
	struct BinaryTree* right;
}BTNode;
//创造节点
BTNode* BuyNode(BTDatatype x);
//前序遍历
void PreOrder(BTNode* root);
//中序遍历
void InOrder(BTNode* root);
//后序遍历
void PostOrder(BTNode* root);
//层序遍历
void LevelOrder(BTNode* root);
//结点数量
int TreeSize(BTNode* root);
//叶子结点数量
int TreeLeafSize(BTNode* root);
//树的高度
int TreeHeight(BTNode* root);
//查找值为x的节点
BTNode* TreeFind(BTNode* root, BTDatatype x);
//销毁树
void TreeDestroy(BTNode* root);