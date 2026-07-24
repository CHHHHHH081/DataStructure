#include <list>
#include <vector>
#include <iostream>
#include "Stack.h"

template <class Compare>
void BubbleSort(int* a, size_t n, Compare com)
{
    int flag = 1;
    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            if (com(a[i], a[j]))
            {
                swap(a[i], a[j]);
                flag = 0;
            }
        }
        if (flag == 1) break;
    }
}
int main()
{
    less<int> ls;
    greater<int> gr;
    int a[8] = {0,3,4,2,6,7,1,5};
    BubbleSort(a, 8, ls);
    return 0;
}