#pragma once 

#include <iostream>
#include <vector>
using namespace std;

template<class T>
class Heap
{
	Heap()
	{}

	Heap(const T* a, size_t size)
	{
		for (int i = 0; i < size; i++)
		{
			_array.push_back(_array[i]);
		}
		for (int root = (size - 2) / 2; root >= 0; root--)
		{
			AdjustDown(root);
		}
	}

	void AdjustDown(int root)
	{
		int child = root * 2 + 1;
		while (child <= _array.size())
		{
			if (child + 1 < _array.size() && _array[child+1] > _array[child])
			{
				child = child + 1;
			}
			
			if (child + 1 < _array.size() && _array[child] > _array[root])
			{
				swap(_array[child], _array[root]);
				root = child + 1;
				child = root * 2 + 1;
			}
		}
	}

protected:
	vector<T> _array;
};


void Test1()
{
	int arr[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
	Heap<int> hp1 (arr, 10);
}