#pragma once
#include <list>
#include <iostream>
#include <initializer_list>
using namespace std;

namespace zzt
{
	//List节点类
	template<class T>
	struct ListNode
	{
		ListNode(const T& data = T())
			:_prev(nullptr),
			_next(nullptr),
			_data(data)
		{}
		ListNode<T>* _prev;
		ListNode<T>* _next;
		T _data;
	};

	//List迭代器类
	template<class T, class Ref, class Ptr>
	struct ListIterator
	{
		typedef ListIterator<T, T&, T*> iterator;
		typedef const ListIterator<T, const T&, const T*> const_iterator;
		typedef ListNode<T> Node;
		typedef ListIterator self;
		Node* _pnode;

		ListIterator(Node* pnode = nullptr)
			:_pnode(pnode)
		{}

		self& operator=(const self& s) { _pnode = s._pnode; return *this; }
		Ref operator*() { return _pnode->_data; }
		self& operator++()
		{
			_pnode = _pnode->_next;
			return *this;
		}
		self operator++(int)
		{
			auto tmp = *this;
			_pnode = _pnode->_next;
			return tmp;
		}
		self& operator--()
		{
			_pnode = _pnode->_prev;
			return *this;
		}
		self& operator--(int)
		{
			auto tmp = *this;
			_pnode = _pnode->_prev;
			return tmp;
		}
		Ptr operator->() { return &(_pnode->_data); }
		bool operator==(const self& s) const { return s._pnode == _pnode; }
		bool operator!=(const self& s) const { return s._pnode != _pnode; }
	};

	//List类
	template<class T>
	class List
	{
		typedef ListNode<T> Node;
	public:
		typedef ListIterator<T, T&, T*> iterator;
		typedef const ListIterator<T, const T&, const T*> const_iterator;

		List()
		{
			empty_init();
		}

		List(size_t n, const T& value = T())
		{
			empty_init();
			while (n--)
			{
				push_back(value);
			}
		}

		List(std::initializer_list<T> il)
		{
			empty_init();
			for (auto i : il)
			{
				push_back(i);
			}
		}

		void empty_init()
		{
			_head = new Node;
			_head->_next = _head;
			_head->_prev = _head;
			_size = 0;
		}

		template<class InputIterator>
		List(InputIterator begin, InputIterator end)
		{
			InputIterator i = begin;
			while (i != end)
			{
				push_back(*i);
				i++;
			}
		}

		List(List<T>& lt)
		{
			empty_init();
			swap(lt);
		}

		~List()
		{
			clear();
			delete _head;
			_head = nullptr;
		}

		List<T>& operator=(List<T>& lt)
		{
			swap(lt);
			return *this;
		}

		iterator begin() { return iterator(_head->_next); }
		iterator end() { return iterator(_head); }
		const_iterator begin() const { return const_iterator(_head->_next); }
		const_iterator end() const { return const_iterator(_head); }

		iterator insert(iterator pos, const T& val)
		{
			Node* node = pos._pnode;
			Node* newnode = new Node(val);
			Node* prev = node->_prev;
			prev->_next = newnode;
			newnode->_prev = prev;
			newnode->_next = node;
			node->_prev = newnode;
			++_size;
			return iterator(newnode);
		}

		iterator erase(iterator pos)
		{
			Node* node = pos._pnode;
			if (node == _head) return end();
			Node* prev = node->_prev;
			Node* next = node->_next;
			prev->_next = next;
			next->_prev = prev;
			delete node;
			--_size;
			return iterator(next);
		}

		void push_back(const T& val) { insert(end(), val); }
		void pop_back() { if (!empty()) erase(--end()); }
		void push_front(const T& val) { insert(begin(), val); }
		void pop_front() { if (!empty()) erase(begin()); }

		size_t size() const { return _size; }
		void clear()
		{
			auto it = begin();
			while (it != end())
			{
				it = erase(it);
			}
		}
		bool empty() const { return _size == 0; }
		T& back() { return _head->_prev->_data; }
		const T& back() const { return _head->_prev->_data; }
		T& front() { return _head->_next->_data; }
		const T& front() const { return _head->_next->_data; }
		List<T>& operator=(List<T> lt)
		{
			swap(lt);
			return *this;
		}
		void swap(List<T>& lt)
		{
			std::swap(_head, lt._head);
			std::swap(_size, lt._size);
		}
		void Display()
		{
			auto it = begin();
			while (it != end())
			{
				std::cout << *it << " ";
				it++;
			}
			std::cout << std::endl;
		}
		T GetElement(size_t pos)
		{
			if (pos >= _size) return T();
			auto it = begin();
			while (pos--)
			{
				it++;
			}
			return *it;
		}
		void Delete(size_t pos)
		{
			if (pos >= _size) return;
			auto it = begin();
			while (pos--)
			{
				it++;
			}
			erase(it);
		}
		void Reverse()
		{
			auto it = begin();
			while (it != end())
			{
				std::swap(it._pnode->_prev, it._pnode->_next);
				it++;
			}
			std::swap(_head->_prev, _head->_next);
		}
	private:
		Node* _head;
		size_t _size;
	};
}
