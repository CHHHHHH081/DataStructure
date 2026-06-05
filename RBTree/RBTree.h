#pragma once
#include <iostream>
#include <cassert>
#include <algorithm>
#include <vector>
using namespace std;
enum Colour
{
	RED, BLACK
};

template<typename K, typename V>
struct RBTreeNode
{
	pair<K, V> _kv;
	RBTreeNode<K, V>* _parent;
	RBTreeNode<K, V>* _left;
	RBTreeNode<K, V>* _right;
	Colour _col;
	RBTreeNode(const pair<K,V>& _kv)
		:_kv(_kv), _parent(nullptr), _left(nullptr), _right(nullptr)
	{}
};

template<typename K, typename V>
class RBTree
{
	typedef RBTreeNode<K, V> Node;
public:
	RBTree()
		:_root(nullptr)
	{}
	~RBTree() { Destroy(_root); }
	void RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		Node* pParent = parent->_parent;
		parent->_left = subLR;
		if (subLR)
		{
			subLR->_parent = parent;
		}
		subL->_right = parent;
		parent->_parent = subL;
		subL->_parent = pParent;
		if (_root == parent)
		{
			_root = subL;
		}
		else
		{
			if (pParent->_left == parent)
			{
				pParent->_left = subL;
			}
			else
			{
				pParent->_right = subL;
			}
		}
	}

	void RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		Node* pParent = parent->_parent;
		parent->_right = subRL;
		if (subRL)
		{
			subRL->_parent = parent;
		}
		subR->_left = parent;
		parent->_parent = subR;
		subR->_parent = pParent;
		if (_root == parent)
		{
			_root = subR;
		}
		else
		{
			if (pParent->_left == parent)
			{
				pParent->_left = subR;
			}
			else
			{
				pParent->_right = subR;
			}
		}
	}

	bool insert(const pair<K,V>& kv)
	{
		if (_root == nullptr)
		{
			_root = new Node(kv);
			_root->_col = BLACK;
			return true;
		}
		else
		{
			//找插入位置
			Node* parent = nullptr;
			Node* cur = _root;
			while (cur)
			{
				if (kv.first < cur->_kv.first)
				{
					parent = cur;
					cur = cur->_left;
				}
				else if (kv.first > cur->_kv.first)
				{
					parent = cur;
					cur = cur->_right;
				}
				else return false;
			}
			//找到了
			cur = new Node(kv);
			cur->_parent = parent;
			cur->_col = RED;
			if (kv.first > parent->_kv.first)
			{
				parent->_right = cur;
			}
			else if (kv.first < parent->_kv.first)
			{
				parent->_left = cur;
			}
			else assert(false);
			//调整
			while (parent && parent->_col == RED)
			{
				//parent为红，parent必然不为根，grandfather为黑
				Node* grandfather = parent->_parent;
				Node* uncle;
				if (grandfather->_left == parent) uncle = grandfather->_right;
				else uncle = grandfather->_left;
				//判断uncle情况
				if (uncle && uncle->_col == RED)
				{
					parent->_col = BLACK;
					uncle->_col = BLACK;
					grandfather->_col = RED;
				}
				else
				{
					if (grandfather->_left == parent)
					{
						if (parent->_left == cur)
						{
							//	   g
							//	 p
							// c
							//右单旋+变色
							RotateR(grandfather);
							parent->_col = BLACK;
							grandfather->_col = RED;
							cur->_col = RED;
						}
						else
						{
							//		g
							//	 p
							//	   c
							//左右双旋+变色
							RotateL(parent);
							RotateR(grandfather);
							cur->_col = BLACK;
							grandfather->_col = RED;
							parent->_col = RED;
						}
					}
					else
					{
						if (parent->_right == cur)
						{
							// g
							//	 p
							//	   c
							//左单旋+变色
							RotateL(grandfather);
							parent->_col = BLACK;
							cur->_col = RED;
							grandfather->_col = RED;
						}
						else
						{
							//  g
							//     p
							//   c
							//右左双旋+变色
							RotateR(parent);
							RotateL(grandfather);
							cur->_col = BLACK;
							parent->_col = RED;
							grandfather->_col = RED;
						}
					}
					break;
				}
				cur = grandfather;
				parent = cur->_parent;
			}
			_root->_col = BLACK;
			return true;
		}
	}
	Node* find(const K& k)
	{
		Node* cur = _root;
		while (cur)
		{
			if (k > cur->_kv.first)
				cur = cur->_right;
			else if (k < cur->_kv.first)
				cur = cur->_left;
			else return cur;
		}
		return nullptr;
	}
	void InOrder() { _InOrder(_root); }
	int Height() { return _Height(_root); }
	int Size() { return _Size(_root); }
	bool IsRBTree()
	{
		if (_root->_col == RED) return false;
		Node* cur = _root;
		int refnum = 0;
		//以最左路线为参考
		while (cur)
		{
			if (cur->_col == BLACK) refnum++;
			cur = cur->_left;
		}
		return _IsRBTree(_root,0,refnum);
	}
private:
	void Destroy(Node* _root)
	{
		if (_root == nullptr)
			return;
		Destroy(_root->_left);
		Destroy(_root->_right);
		delete _root;
	}
	void _InOrder(Node* _root)
	{
		if (_root == nullptr)
			return;
		_InOrder(_root->_left);
		cout << _root->_kv.first << ':' << _root->_kv.second << endl;
		_InOrder(_root->_right);
	}
	int _Height(Node* _root)
	{
		if (_root == nullptr)
			return 0;
		int Left = _Height(_root->_left);
		int Right = _Height(_root->_right);
		return max(Left, Right) + 1;
	}
	int _Size(Node* _root)
	{
		if (_root == nullptr)
			return 0;
		int Left = _Size(_root->_left);
		int Right = _Size(_root->_right);
		return Left + Right + 1;
	}
	bool _IsRBTree(Node* root,int num,const int refnum)
	{
		if (root == nullptr)
		{
			if (num != refnum) return false;
			return true;
		}
		if (root->_col == RED && root->_parent->_col == RED) return false;
		if (root->_col == BLACK) num++;
		return _IsRBTree(root->_left,num,refnum) && _IsRBTree(root->_right,num,refnum);
	}
	Node* _root;
};
