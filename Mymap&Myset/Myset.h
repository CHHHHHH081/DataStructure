#pragma once
#include "RBTree.h"
namespace zzt
{
	template<class K>
	class set
	{
		struct SetKeyOfK
		{
			const K& operator()(const K& Key) { return Key; }
		};
	public:
		typedef typename RBTree<K, const K, SetKeyOfK>::Iterator iterator;
		typedef typename RBTree<K, const K, SetKeyOfK>::Const_Iterator const_iterator;
		iterator begin() { return _t.Begin(); }
		iterator end() { return _t.End(); }
		const_iterator begin() const { return _t.Begin(); }
		const_iterator end() const { return _t.End(); }

		pair<iterator,bool> insert(const K& k) { return _t.insert(k); }
		iterator find(const K& k) { return _t.find(k); }

	private:
		RBTree<K, const K, SetKeyOfK> _t;
	};
}
