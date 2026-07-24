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
namespace zzt
{
	//节点类
	template<class T>
	struct RBTreeNode
	{
		T _data;
		RBTreeNode<T>* _parent;   
		RBTreeNode<T>* _left;
		RBTreeNode<T>* _right;
		Colour _col;
		RBTreeNode(const T& data)
			:_data(data), _parent(nullptr), _left(nullptr), _right(nullptr)
		{}
	};

	//迭代器类
	template<class T,class Ref,class Ptr>
	struct RBTreeIterator
	{
		typedef RBTreeNode<T> Node;
		typedef RBTreeIterator<T, Ref, Ptr> Self;
		Node* _node;
		Node* _root;
		RBTreeIterator(Node* node,Node* root)
			:_node(node),_root(root)
		{}
		Self& operator++()
		{
			if (_node->_right)
			{
				_node = _node->_right;
				while (_node->_left)
				{
					_node = _node->_left;
				}
			}
			else
			{
				Node* cur = _node;
				Node* parent = cur->_parent;
				while (parent&&cur==parent->_right)
				{
					cur = parent;
					parent = parent->_parent;
				}
				_node = parent;
			}
			return *this;
		}
		Self& operator--()
		{
			if (_node->_left)
			{
				_node = _node->_left;
				while (_node->_right)
				{
					_node = _node->_right;
				}
			}
			else
			{
				Node* cur = _node;
				Node* parent = cur->_parent;
				while (parent && cur == parent->_left)
				{
					cur = parent;
					parent = parent->_parent;
				}
				_node = parent;
			}
			return *this;
		}
		bool operator==(const Self& s) const { return _node == s._node; }
		bool operator!=(const Self& s) const { return _node != s._node; }
		Ref operator*() { return _node->_data; }
		Ptr operator->() { return &_node->_data; }
	};

	template<class K, class T,class KeyOfT>
	class RBTree
	{
		typedef RBTreeNode<T> Node;
	public:
		typedef RBTreeIterator<T, T&, T*> Iterator;
		typedef RBTreeIterator<T, const T&, const T*> Const_Iterator;
		RBTree()
			:_root(nullptr)
		{}
		~RBTree() { Destroy(_root); }
		Iterator Begin()
		{
			Node* cur = _root;
			while (cur->_left)
			{
				cur = cur->_left;
			}
			return Iterator(cur, _root);
		}
		Iterator End() { return Iterator(nullptr, _root); }
		Const_Iterator Begin() const
		{
			Node* cur = _root;
			while (cur->_left)
			{
				cur = cur->_left;
			}
			return Const_Iterator(cur, _root);
		}
		Const_Iterator End() const { return Const_Iterator(nullptr, _root); }

		pair<Iterator,bool> insert(const T& data)
		{
			KeyOfT kot;
			if (_root == nullptr)
			{
				_root = new Node(data);
				_root->_col = BLACK;
				return make_pair(Iterator(_root,_root),true);
			}
			else
			{
				//找插入位置
				Node* parent = nullptr;
				Node* cur = _root;
				while (cur)
				{
					if (kot(data) < kot(cur->_data))
					{
						parent = cur;
						cur = cur->_left;
					}
					else if (kot(data) > kot(cur->_data))
					{
						parent = cur;
						cur = cur->_right;
					}
					else return make_pair(Iterator(cur,_root),false);
				}
				//找到了
				Node* newnode = new Node(data);
				cur = newnode;
				cur->_parent = parent;
				cur->_col = RED;
				if (kot(data) > kot(parent->_data))
				{
					parent->_right = cur;
				}
				else if (kot(data) < kot(parent->_data))
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
				return make_pair(Iterator(newnode,_root),true);
			}
		}
		Iterator find(const K& k)
		{
			Node* cur = _root;
			KeyOfT kot;
			while (cur)
			{
				if (k > kot(cur->_data))
					cur = cur->_right;
				else if (k < kot(cur->_data))
					cur = cur->_left;
				else return Iterator(cur,_root);
			}
			return End();
		}
		void InOrder() { _InOrder(_root); }
		int Height() { return _Height(_root); }
		int Size() { return _Size(_root); }
		bool IsBalanceTree()
		{
			if (_root->_col == RED) return false;
			Node* cur = _root;
			int refnum = 0;
			while (cur)
			{
				if (cur->_col == BLACK) refnum++;
				cur = cur->_left;
			}
			return _IsBalanceTree(_root, 0, refnum);
		}
	private:
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
			cout << _root->_data.first << ':' << _root->_data.second << endl;
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
		bool _IsBalanceTree(Node* root, int num, const int refnum)
		{
			if (root == nullptr)
			{
				if (num != refnum) return false;
				return true;
			}
			if (root->_col == RED && root->_parent->_col == RED) return false;
			if (root->_col == BLACK) num++;
			return _IsBalanceTree(root->_left, num, refnum) && _IsBalanceTree(root->_right, num, refnum);
		}
		Node* _root;
	};
}

