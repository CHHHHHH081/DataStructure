#pragma once
#pragma once
#include <iostream>
#include <vector>
#include <assert.h>
using namespace std;

template <typename K, typename V>
struct AVLTreeNode
{
	pair<K, V> _kv;
	AVLTreeNode<K, V>* _left;
	AVLTreeNode<K, V>* _right;
	AVLTreeNode<K, V>* _parent;
	int _bf;

	AVLTreeNode(const pair<K, V>& kv)
		: _kv(kv), _left(nullptr), _right(nullptr), _parent(nullptr), _bf(0)
	{}
};

template <typename K, typename V>
class AVLTree
{
	typedef AVLTreeNode<K, V> Node;

public:
	~AVLTree() { Destroy(_root); }
	void InOrder() { _InOrder(_root); }
	int Height() { return _Height(_root); }
	int Size() { return _Size(_root); }

	// 右单旋
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
		subL->_bf = 0;
		parent->_bf = 0;
	}

	// 左单旋
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
		subR->_parent = pParent;
		parent->_parent = subR;
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
		subR->_bf = 0;
		parent->_bf = 0;
	}

	// 左右双旋
	void RotateLR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		int bf = subLR->_bf;
		RotateL(subL);
		RotateR(parent);
		if (bf == -1)
		{
			subLR->_bf = 0;
			subL->_bf = 0;
			parent->_bf = 1;
		}
		else if (bf == 1)
		{
			subLR->_bf = 0;
			subL->_bf = -1;
			parent->_bf = 0;
		}
		else if (bf == 0)
		{
			subLR->_bf = 0;
			subL->_bf = 0;
			parent->_bf = 0;
		}
		else
			assert(false);
	}

	// 右左双旋
	void RotateRL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		int bf = subRL->_bf;
		RotateR(parent->_right);
		RotateL(parent);
		if (bf == 0)
		{
			subR->_bf = 0;
			subRL->_bf = 0;
			parent->_bf = 0;
		}
		else if (bf == 1)
		{
			subR->_bf = 0;
			subRL->_bf = 0;
			parent->_bf = -1;
		}
		else if (bf == -1)
		{
			subR->_bf = 1;
			subRL->_bf = 0;
			parent->_bf = 0;
		}
		else
		{
			assert(false);
		}
	}

	pair<bool, Node*> insert(const pair<K, V>& kv)
	{
		if (_root == nullptr)
		{
			_root = new Node(kv);
			return { true, _root };
		}
		else
		{
			// 找到位置
			Node* parent = nullptr;
			Node* cur = _root;
			while (cur)
			{
				if (kv.first > cur->_kv.first)
				{
					parent = cur;
					cur = cur->_right;
				}
				else if (kv.first < cur->_kv.first)
				{
					parent = cur;
					cur = cur->_left;
				}
				else
				{
					return { false, nullptr };
				}
			}
			// 已经找到，开始插入
			cur = new Node(kv);
			if (kv.first > parent->_kv.first)
				parent->_right = cur;
			else if (kv.first < parent->_kv.first)
				parent->_left = cur;
			else
				assert(false);
			cur->_parent = parent;
			Node* newnode = cur;
			// 更新平衡因子
			while (parent)
			{
				if (parent->_right == cur)
					parent->_bf++;
				else
					parent->_bf--;
				// 判断是否需要调整
				if (parent->_bf == 1 || parent->_bf == -1)
				{
					cur = parent;
					parent = parent->_parent;
				}
				else if (parent->_bf == 0)
					break;
				else if (parent->_bf == 2 || parent->_bf == -2)
				{
					// 旋转
					if (cur->_bf == -1 && parent->_bf == -2) // 右单旋
						RotateR(parent);
					else if (cur->_bf == 1 && parent->_bf == 2) // 左单旋
						RotateL(parent);
					else if (cur->_bf == 1 && parent->_bf == -2) // 左右双旋
						RotateLR(parent);
					else if (cur->_bf == -1 && parent->_bf == 2) // 右左双旋
						RotateRL(parent);
					else
						assert(false);
					break;
				}
				else
					assert(false);
			}
			return { true, newnode };
		}
	}

	pair<bool, Node*> find(const K& k)
	{
		Node* parent = nullptr;
		Node* cur = _root;
		while (cur)
		{
			if (k < cur->_kv.first)
			{
				parent = cur;
				cur = cur->_left;
			}
			else if (k > cur->_kv.first)
			{
				parent = cur;
				cur = cur->_right;
			}
			else
			{
				return { true, cur };
			}
		}
		return { false, nullptr };
	}

	bool IsBalanceTree() { return _IsBalanceTree(_root); }

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
	bool _IsBalanceTree(Node* _root)
	{
		if (_root == nullptr)
			return true;
		int Left = _Height(_root->_left);
		int Right = _Height(_root->_right);
		if (abs(Left - Right) >= 2)
			return false;
		if (Right - Left != _root->_bf)
			return false;
		return _IsBalanceTree(_root->_left) && _IsBalanceTree(_root->_right);
	}

	Node* _root;
};