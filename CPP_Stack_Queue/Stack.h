#pragma once

using namespace std;
namespace zzt
{
	template <class T,class Container=vector<T>>
	class stack
	{
		void push(const T& x)
		{
			_c.push_back(x);
			x.pp();
		}
	private:
		Container _c;
	};
}
