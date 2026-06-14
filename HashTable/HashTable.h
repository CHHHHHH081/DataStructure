#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
namespace HashBucket
{
	template<typename K,typename V>
	struct HashNode
	{
		HashNode(const pair<K,V>& kv)
			:_kv(kv),_next(nullptr)
		{}

		typedef HashNode<K, V> Node;
		pair<K, V> _kv;
		Node* _next;
	};

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
			size_t sum=0;
			for (auto i : s)
				sum += (int)i;
			return sum;
		}
	};

	template<typename K,typename V,class Hash=HashFunc<K>>
	class HashTable
	{
	public:
		typedef HashNode<K, V> Node;

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

		bool insert(const pair<K, V>& kv)
		{
			Hash hs;
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
						int hash0 = hs(cur->_kv.first) % newtable.size();
						cur->_next = newtable[hash0];
						newtable[hash0] = cur;
						cur = cur->_next;
					}
					_table[i] = nullptr;
				}
				_table.swap(newtable);
			}
			int hash1 = hs(kv.first) % _table.size();
			Node* newnode = new Node(kv);
			newnode->_next = _table[hash1];
			_table[hash1] = newnode;
			++_n;
			return true;
		}

		bool erase(const K& k)
		{
			Hash hs;
			int hash = hs(k) % _table.size();
			Node* cur = _table[hash],prev=nullptr;
			while (cur)
			{
				if (cur->_kv.first == k)
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

		Node* find(const K& k)
		{
			Hash hs;
			int hash = hs(k) % _table.size();
			Node* cur = _table[hash];
			while (cur)
			{
				if (cur->_kv.first == k)
					return cur;
				cur = cur->_next;
			}
			return nullptr;
		}

		V& operator[](const K& k)
		{
			if (find(k) == nullptr)
				insert(make_pair(k, V()));
			else
				return find(k)->_kv.second;
		}

	private:
		vector<Node*> _table;
		size_t _n = 0;
	};
}
