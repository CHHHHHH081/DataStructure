#pragma once
#include "HashTable.h"
namespace zzt
{
	template<class K,class Hash=HashFunc<K>>
	class unordered_set
	{
		struct SetKeyOfT
		{
			const K& operator()(const K& key) { return key; }
		};
		typedef typename HashBucket::HashTable<K, const K, SetKeyOfT, Hash>::Iterator iterator;
		typedef typename HashBucket::HashTable<K, const K, SetKeyOfT, Hash>::ConstIterator const_iterator;
	public:
		unordered_set(initializer_list<K> il)
		{
			for (auto i : il)
				this->insert(i);
		}
		iterator begin() { return _ht.Begin(); }
		const_iterator begin() const { return _ht.Begin(); }
		iterator end() { return _ht.End(); }
		const_iterator end() const { return _ht.End(); }
		pair<iterator, bool> insert(const K& k) { return _ht.insert(k); }
		bool erase(const K& k) { return _ht.erase(k); }
		iterator find(const K& k) { return _ht.find(k); }
		const_iterator find(const K& k) const { return _ht.find(k); }
	private:
		HashBucket::HashTable<K, const K, SetKeyOfT, Hash> _ht;
	};
}