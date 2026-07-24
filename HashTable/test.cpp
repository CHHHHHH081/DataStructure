#include "HashTable.h"
using namespace HashBucket;
int main()
{
	/*HashBucket::HashTable<int, int> ht;
	for (int i = 0; i < 100; i++)
	{
		ht.insert(make_pair(i, i));
	}
	cout << ht[79] << endl;
	cout << ht.find(65) << endl;*/
	
	/*HashBucket::HashTable<char, int> ht1;
	ht1.insert({ 'f',5 });
	ht1.insert({ 'e',114514 });
	ht1.insert({ 'r',5678 });
	cout << ht1['r'] << endl;*/

	HashBucket::HashTable<string, int> ht2;
	ht2.insert({ "hello",1 });
	ht2.insert({ "C++",2 });
	ht2.insert({ "Linux",3 });
	cout << ht2["Linux"] << endl;
	return 0;
}