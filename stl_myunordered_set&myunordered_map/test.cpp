#include "myunordered_set.h"
#include "myunordered_map.h"

int  main()
{
	zzt::unordered_set<int> st({ 1,4,7,2,9 });
	for (auto i : st)
		cout << i<<endl;
	zzt::unordered_map<int, int> mp;
	mp.insert({ 1,1 });
	mp.insert({ 2,2 });
	mp.insert({ 3,3 });
	mp.insert({ 4,4 });
	mp.insert({ 5,5 });
	for (auto i : mp)
		cout << i.first << ':' << i.second<<endl;
	return 0;
}