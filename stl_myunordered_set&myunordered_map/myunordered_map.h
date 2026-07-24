#pragma once
#include "HashTable.h"
namespace zzt
{
	template<class K, class V, class Hash = HashFunc<K>>
	class unordered_map
	{
		struct MapKeyOfT
		{
			const K& operator()(const pair<K,V>& kv) { return kv.first; }
		};
		typedef typename HashBucket::HashTable<K, pair<const K, V>, MapKeyOfT, Hash>::Iterator iterator;
		typedef typename HashBucket::HashTable<K, pair<const K, V>, MapKeyOfT, Hash>::ConstIterator const_iterator;
	public:
		iterator begin() { return _ht.Begin(); }
		const_iterator begin() const { return _ht.Begin(); }
		iterator end() { return _ht.End(); }
		const_iterator end() const { return _ht.End(); }
		pair<iterator, bool> insert(const pair<const K, V>& kv) { return _ht.insert(kv); }
		bool erase(const K& k) { return _ht.erase(k); }
		iterator find(const K& k) { return _ht.find(k); }
		const_iterator find(const K& k) const { return _ht.find(k); }
		V& operator[](const K& k)
		{
			pair<iterator, bool> ret = _ht.insert(pair<const K, V>(k, V()));
			return ret.first->second;
		}
	private:
		HashBucket::HashTable<K, pair<const K, V>, MapKeyOfT, Hash> _ht;
	};
}
