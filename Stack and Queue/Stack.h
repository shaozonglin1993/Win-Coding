#pragma once

#include "TypeTraits.h"
#include <iostream>
#include <assert.h>
using namespace std;

template<class T>
class Stack
{
public:
	Stack()
		:_array(NULL)
		, _capacity(0)
		, _size(0)
	{}

	~Stack()
	{
		if (_array)
		{
			delete[]_array;
		}
	}

	Stack(const Stack<T>& s);
	Stack<T>& operator= (const Stack<T>& s);

public:
	void Push(const T& x)
	{
		_CheckCapacity();

		_array[_size++] = x;
	}

	void Pop()
	{
		assert(_size > 0);
		--_size;
	}

	size_t Size()
	{
		return _size;
	}

	bool Empty()
	{
		return _size == 0;
	}

	const T& Top()
	{
		assert(_size > 0);
		return _array[_size - 1];
	}

protected:
	void _CheckCapacity()
	{
		if (_size >= _capacity)
		{
			_capacity = _capacity * 2 + 3;
			T* tmp = new T[_capacity];
			//识别T是什么类型 -->类型萃取 -->特化
			if (TypeTraits<T>::__IsPODType().Get())
			{
				cout << "POD" << endl;
				memcpy(tmp, _array, sizeof(T)*_size);
			}
			else
			{
				cout << "NON_POD" << endl;
				for (size_t i = 0; i < _size; i++)
				{
					tmp[i] = _array[i];
				}
			}

			delete[] _array;
			_array = tmp;

		}
	}

	T* _array;
	size_t _size;
	size_t _capacity;

};

void Test1()
{
	Stack<char> s1;
	s1.Push('a');
	s1.Push('b');
	s1.Push('c');
	s1.Push('d');

	while (!s1.Empty())
	{
		cout << s1.Top() << " ";
		s1.Pop();
	}
	cout << endl;

	Stack<string> s2;
	s2.Push("ssssss");
	s2.Push("ssssss");
	s2.Push("ssssss");
	s2.Push("ssssss");
	s2.Push("ssssss");
	s2.Push("ssssss");

	while (!s1.Empty())
	{
		cout << s1.Top() << " ";
		s1.Pop();
	}

	cout << endl;
}