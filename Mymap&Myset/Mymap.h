#pragma once
#include "RBTree.h"
namespace zzt
{
	template<class K,class V>
	class map
	{
		struct MapKeyOfT
		{
			const K& operator()(const pair<const K, V>& kv) { return kv.first; }
		};
	public:
		typedef typename RBTree<K, pair<const K, V>, MapKeyOfT>::Iterator iterator;
		typedef typename RBTree<K, pair<const K, V>, MapKeyOfT>::Const_Iterator const_iterator;
		iterator begin() { return _t.Begin(); }
		iterator end() { return _t.End(); }
		const_iterator begin() const { return _t.Begin(); }
		const_iterator end() const { return _t.End(); }

		pair<iterator,bool> insert(const pair<K, V>& kv) { return _t.insert(kv); }
		iterator find(const K& k) { return _t.find(k); }
		V& operator[](const K& k)
		{
			pair<iterator, bool> ret = insert(make_pair(k, V()));
			return ret.first->second;
		}
	private:
		RBTree<K, pair<const K, V>, MapKeyOfT> _t;
	};
}
