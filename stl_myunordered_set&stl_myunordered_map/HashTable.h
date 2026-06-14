#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
template<typename K>
struct HashFunc
{
	size_t operator()(const K& k) { return (size_t)k; }
};

template<>
struct HashFunc<string>
{
	size_t operator()(const string& s)
	{
		size_t sum = 0;
		for (auto i : s)
			sum += (int)i;
		return sum;
	}
};
namespace HashBucket
{
	template<typename T>
	struct HashNode
	{
		HashNode(const T& data)
			:_data(data),_next(nullptr)
		{}

		typedef HashNode<T> Node;
		T _data;
		Node* _next;
	};

	template<typename K, typename T, class KeyOfT, class Hash = HashFunc<K>>
	class HashTable;

	template<typename K,typename T,typename Ref,typename Ptr,typename KeyOfT,typename Hash>
	struct Hash_Iterator
	{
		typedef HashNode<T> Node;
		typedef Hash_Iterator<K, T, Ref, Ptr, KeyOfT, Hash> Self;

		Hash_Iterator(const HashTable<K, T, KeyOfT, Hash>* pht, Node* node)
			:_pht(pht),_node(node)
		{}

		Ref operator*() { return _node->_data; }
		Ptr operator->() { return &_node->_data; }
		bool operator==(const Self& s) { return _node == s._node; }
		bool operator!=(const Self& s) { return _node != s._node; }
		Self& operator++()
		{
			if (_node->_next)
				_node = _node->_next;
			else
			{
				Hash hs;
				KeyOfT kot;
				int k = hs(kot(_node->_data)) % _pht->_table.size()+1;
				while (k < _pht->_table.size() && _pht->_table[k] == nullptr)
					k++;
				if (k < _pht->_table.size())
					_node = _pht->_table[k];
				else
					_node = nullptr;
			}
			return *this;
		}

		const HashTable<K, T, KeyOfT, Hash>* _pht;
		Node* _node;
	};

	template<typename K,typename T,class KeyOfT,class Hash>
	class HashTable
	{
		typedef HashNode<T> Node;

		//友元 Iterator _pht取值
		template<typename K, typename T, typename Ref, typename Ptr, typename KeyOfT, typename Hash>
		friend struct Hash_Iterator;

	public:
		typedef Hash_Iterator<K, T, T&, T*, KeyOfT, Hash> Iterator;
		typedef Hash_Iterator<K, T, const T&, const T*, KeyOfT, Hash> ConstIterator;

		inline unsigned long __stl_next_prime(unsigned long n)
		{
			static const int __stl_num_primes = 28;
			static const unsigned long __stl_prime_list[__stl_num_primes] =
			{
			53, 97, 193, 389, 769,
			1543, 3079, 6151, 12289, 24593,
			49157, 98317, 196613, 393241, 786433,
			1572869, 3145739, 6291469, 12582917, 25165843,
			50331653, 100663319, 201326611, 402653189, 805306457,
			1610612741, 3221225473, 4294967291
			};
			const unsigned long* first = __stl_prime_list;
			const unsigned long* last = __stl_prime_list +__stl_num_primes;
			const unsigned long* pos = lower_bound(first, last, n);
			return pos == last ? *(last - 1) : *pos;
		}

		HashTable()
		{
			_table.resize(__stl_next_prime(0), nullptr);
		}

		HashTable(initializer_list<T> il)
		{
			for (auto i : il)
				this->insert(i);
		}

		~HashTable()
		{
			Node* cur=nullptr,*next=nullptr;
			for (int i = 0; i < _table.size(); i++)
			{
				cur = _table[i];
				while (cur)
				{
					next = cur->_next;
					delete cur;
					cur = next;
				}
				_table[i] = nullptr;
			}
		}

		Iterator Begin()
		{
			int hashi = 0;
			Node* cur = _table[hashi];
			while (hashi<_table.size()&&cur == nullptr)
			{
				hashi++;
				cur = _table[hashi];
			}
			if (cur)
				return Iterator(this,cur);
			return Iterator(this, nullptr);
		}

		ConstIterator Begin() const
		{
			int hashi = 0;
			Node* cur = _table[hashi];
			while (hashi < _table.size() && cur == nullptr)
			{
				hashi++;
				cur = _table[hashi];
			}
			if (cur)
				return cur;
			return nullptr;
		}

		Iterator End() { return Iterator(this,nullptr); }

		ConstIterator End() const { return Iterator(this, nullptr); }

		pair<Iterator, bool> insert(const T& data)
		{
			Hash hs;
			KeyOfT kot;
			if (_n == _table.size())
			{
				//扩容
				vector<Node*> newtable(__stl_next_prime(_table.size()+1));
				Node* cur;
				for (int i = 0; i < _table.size(); i++)
				{
					cur = _table[i];
					while (cur)
					{
						int hash0 = hs(kot(cur->_data)) % newtable.size();
						cur->_next = newtable[hash0];
						newtable[hash0] = cur;
						cur = cur->_next;
					}
					_table[i] = nullptr;
				}
				_table.swap(newtable);
			}
			int hash1 = hs(kot(data)) % _table.size();
			Node* newnode = new Node(data);
			newnode->_next = _table[hash1];
			_table[hash1] = newnode;
			++_n;
			return { Iterator(this,newnode),true };
		}

		bool erase(const K& k)
		{
			Hash hs;
			KeyOfT kot;
			int hash = hs(k) % _table.size();
			Node* cur = _table[hash],prev=nullptr;
			while (cur)
			{
				if (kot(cur->_data) == k)
				{
					if (prev == nullptr)
						_table[hash] = cur->_next;
					else
						prev->_next = cur->_next;
					delete cur;
					--_n;
					return true;
				}
				prev = cur;
				cur = cur->_next;
			}
			return false;
		}

		Iterator find(const K& k)
		{
			Hash hs;
			KeyOfT kot;
			int hash = hs(k) % _table.size();
			Node* cur = _table[hash];
			while (cur)
			{
				if (kot(cur->_data) == k)
					return Iterator(this,cur);
				cur = cur->_next;
			}
			return Iterator(this,nullptr);
		}

		ConstIterator find(const K& k) const
		{
			Hash hs;
			KeyOfT kot;
			int hash = hs(k) % _table.size();
			Node* cur = _table[hash];
			while (cur)
			{
				if (kot(cur->_data) == k)
					return Iterator(this, cur);
				cur = cur->_next;
			}
			return Iterator(this, nullptr);
		}

	private:
		vector<Node*> _table;
		size_t _n = 0;
	};
}
