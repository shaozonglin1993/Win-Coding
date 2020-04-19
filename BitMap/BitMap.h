#pragma once
#include <iostream>
using namespace std;
#include <vector>

class BitMap
{
public:
	BitMap()
		:_size(0)
	{}

	BitMap(size_t size)
		:_size(0)
	{
		_array.resize((size >> 5) + 1); // size/32 + 1 
	}
	bool Test(size_t num) //查看次数是否存在
	{
		size_t index = num >> 5;
		size_t n = num % 32;

		return _array[index] & (1 << n);
	}

	void Set(size_t num)
	{
		size_t index = num >> 5;
		size_t n = num % 32;
		if (_array[index] & (1 << n)) //该数已经存在
		{
			return;
		}
		_array[index] |= (1 << n);
		_size++;
	}

	void ReSet(size_t num)
	{
		size_t index = num >> 5;
		size_t n = num % 32;
		if (!_array[index] & (1 << n))
		{
			return;
		}
		_array[index] &= ~(1 << n);
		++_size;
		return;
	}

	void Clear()
	{
		_array.assign(_array.size(), 0);
	}

protected:
	vector<size_t> _array;
	size_t _size;
};