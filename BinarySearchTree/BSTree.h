#pragma once
#include <iostream>
#include <algorithm>
using namespace std;
namespace key
{
	//节点类
	template<typename K>
	struct BSTNode
	{
		K _key;
		BSTNode<K>* _left;
		BSTNode<K>* _right;

		BSTNode(const K& key):_key(key),_left(nullptr),_right(nullptr)
		{}
	};

	//树类
	template<typename K>
	class BSTree
	{
		using Node = BSTNode<K>;
	public:
		BSTree():_root(nullptr){}
		BSTree(const BSTree<K>& bst) { _root = Copy(bst); }
		~BSTree()
		{
			Destroy(_root);
			_root = nullptr;
		}
		void Destroy(Node* _root)
		{
			if (_root == nullptr) return;
			Destroy(_root->_left);
			Destroy(_root->_right);
			delete _root;
		}
		BSTree<K>& operator=(const BSTree<K>& bst)
		{
			std::swap(_root, bst._root);
			return *this;
		}

		bool Insert(const K& key)
		{
			if (_root == nullptr)
			{
				_root = new Node(key);
				return true;
			}
			Node* parent = _root;
			Node* cur=_root;
			while (cur)
			{
				if (cur->_key > key)
				{
					parent = cur;
					cur = cur->_left;
				}
				else if(cur->_key < key)
				{
					parent = cur;
					cur = cur->_right;
				}
				else return false;
			}
			cur = new Node(key);
			if (parent->_key > key)
			{
				parent->_left = cur;
				return true;
			}
			else if (parent->_key < key)
			{
				parent->_right = cur;
				return true;
			}
			return false;
		}

		Node* find(const K& key)
		{
			if (_root == nullptr) return nullptr;
			Node* parent = _root;
			Node* cur = _root;
			while (cur)
			{
				if (cur->_key > key)
				{
					parent = cur;
					cur = cur->_left;
				}
				else if (cur->_key < key)
				{
					parent = cur;
					cur = cur->_right;
				}
				else return cur;
			}
			return nullptr;
		}

		bool erase(const K& key)
		{
			if (_root == nullptr) return false;
			Node* parent = _root;
			Node* cur = _root;
			//先查找节点
			while (cur)
			{
				if (cur->_key > key)
				{
					parent = cur;
					cur = cur->_left;
				}
				else if (cur->_key < key)
				{
					parent = cur;
					cur = cur->_right;
				}
				else
				{
					//找到了，执行删除
					//如果要删的是根节点：parent==cur
					if (parent == cur)
					{
						Node* keynodeparent = cur;
						Node* keynode = cur->_left;
						while (keynode->_right)
						{
							keynodeparent = keynode;
							keynode = keynode->_right;
						}
						cur->_key = keynode->_key;
						if (keynodeparent->_left == keynode) keynodeparent->_left = nullptr;
						else keynodeparent->_right = nullptr;
						delete keynode;
						return true;
					}
					//如果左右都不为空，情况4
					if (cur->_left && cur->_right)
					{
						Node* keynodeparent = cur;
						Node* keynode = cur->_left;
						while (keynode->_right)
						{
							keynodeparent = keynode;
							keynode = keynode->_right;
						}
						cur->_key = keynode->_key;
						if (keynodeparent->_left == keynode) keynodeparent->_left = nullptr;
						else keynodeparent->_right = nullptr;
						delete keynode;
						
					}
					//左右至少有一个为空，情况1,2,3
					else
					{
						if (parent->_left == cur)
						{
							if (cur->_left == nullptr) parent->_left = cur->_right;
							else parent->_left = cur->_left;
						}
						else
						{
							if (cur->_left == nullptr) parent->_right = cur->_right;
							else parent->_right = cur->_left;
						}
						delete cur;
					}
					return true;
				}
			}
			return false;
		}

		void InOrder()
		{
			_InOrder(_root);
			cout << endl;
		}
	private:
		void _InOrder(Node* _root)
		{
			if (_root == nullptr) return;
			_InOrder(_root->_left);
			cout << _root->_key << ' ';
			_InOrder(_root->_right);
		}
		Node* Copy(Node* root)
		{
			if (_root == nullptr) return;
			Node* newroot = new Node(root->_key);
			newroot->_left = Copy(root->_left);
			newroot->_right = Copy(root->_right);
			return newroot;
		}
		Node* _root;
	};
}

namespace key_value
{
	template<typename K,typename V>
	struct BSTNode
	{
		K _key;
		V _value;
		BSTNode<K,V>* _left;
		BSTNode<K,V>* _right;

		BSTNode(const K& key,const V& value) :_key(key), _value(value), _left(nullptr), _right(nullptr)
		{}
	};

	template<typename K,typename V>
	class BSTree
	{
		using Node = BSTNode<K,V>;
	public:
		BSTree() :_root(nullptr) {}
		BSTree(const BSTree<K,V>& bst) { _root = Copy(bst); }
		~BSTree()
		{
			Destroy(_root);
			_root = nullptr;
		}
		void Destroy(Node* _root)
		{
			if (_root == nullptr) return;
			Destroy(_root->_left);
			Destroy(_root->_right);
			delete _root;
		}
		BSTree<K, V>& operator=(const BSTree<K, V>& bst)
		{
			swap(_root, bst._root);
			return *this;
		}

		bool Insert(const K& key,const V& value)
		{
			if (_root == nullptr)
			{
				_root = new Node(key,value);
				return true;
			}
			Node* parent = _root;
			Node* cur = _root;
			while (cur)
			{
				if (cur->_key > key)
				{
					parent = cur;
					cur = cur->_left;
				}
				else if (cur->_key < key)
				{
					parent = cur;
					cur = cur->_right;
				}
				else return false;
			}
			cur = new Node(key,value);
			if (parent->_key > key)
			{
				parent->_left = cur;
				return true;
			}
			else if (parent->_key < key)
			{
				parent->_right = cur;
				return true;
			}
			return false;
		}

		Node* find(const K& key)
		{
			if (_root == nullptr) return nullptr;
			Node* parent = _root;
			Node* cur = _root;
			while (cur)
			{
				if (cur->_key > key)
				{
					parent = cur;
					cur = cur->_left;
				}
				else if (cur->_key < key)
				{
					parent = cur;
					cur = cur->_right;
				}
				else return cur;
			}
			return nullptr;
		}

		bool erase(const K& key)
		{
			if (_root == nullptr) return false;
			Node* parent = _root;
			Node* cur = _root;
			while (cur)
			{
				if (cur->_key > key)
				{
					parent = cur;
					cur = cur->_left;
				}
				else if (cur->_key < key)
				{
					parent = cur;
					cur = cur->_right;
				}
				else
				{
					//删除
					if (parent == cur)
					{
						Node* keynodeparent = cur;
						Node* keynode = cur->_left;
						while (keynode->_right)
						{
							keynodeparent = keynode;
							keynode = keynode->_right;
						}
						cur->_key = keynode->_key;
						if (keynodeparent->_left == keynode) keynodeparent->_left = nullptr;
						else keynodeparent->_right = nullptr;
						delete keynode;
						return true;
					}
					if (cur->_left && cur->_right)
					{
						Node* keynodeparent = cur;
						Node* keynode = cur->_left;
						while (keynode->_right)
						{
							keynodeparent = keynode;
							keynode = keynode->_right;
						}
						cur->_key = keynode->_key;
						if (keynodeparent->_left == keynode) keynodeparent->_left = nullptr;
						else keynodeparent->_right = nullptr;
						delete keynode;

					}
					else
					{
						if (parent->_left == cur)
						{
							if (cur->_left == nullptr) parent->_left = cur->_right;
							else parent->_left = cur->_left;
						}
						else
						{
							if (cur->_left == nullptr) parent->_right = cur->_right;
							else parent->_right = cur->_left;
						}
						delete cur;
					}
					return true;
				}
			}
			return false;
		}

		void InOrder()
		{
			_InOrder(_root);
			cout << endl;
		}
	private:
		void _InOrder(Node* _root)
		{
			if (_root == nullptr) return;
			_InOrder(_root->_left);
			cout << _root->_key << ' ';
			_InOrder(_root->_right);
		}
		Node* Copy(Node* root)
		{
			if (_root == nullptr) return;
			Node* newroot = new Node(root->_key, root->_value);
			newroot->_left = Copy(root->_left);
			newroot->_right = Copy(root->_right);
			return newroot;
		}
		Node* _root;
	};
}