#pragma once
#include<assert.h>

template<class T>
class Vector
{
	typedef T ValueType;			
public:
	typedef ValueType* Iterator;
	typedef const ValueType* ConstIterator;

	Vector()
		:_start(NULL)
		, _finish(NULL)
		, _endOfStorage(NULL)
	{}

	void PushBack(const ValueType& x)
	{
		_CheckCapacity();

		*_finish = x;
		_finish++;
	}

	void PopBack()
	{
		_finish--;
	}

	//插入x，在pos前面
	void Insert(Iterator pos, const ValueType& x)
	{
		_CheckCapacity();
		assert(pos <= _finish + 1);

		if (pos == _finish + 1 || pos == _finish)
		{
			PushBack(x);
			return;
		}

		Iterator cur = _finish;
		Iterator prev = _finish - 1;
		while (cur != pos)
		{
			*cur-- = *prev--;
		}

		*cur = x;
		_finish++;

	}

	void Erase(Iterator pos)
	{
		assert(pos < _finish);

		if (pos == _finish - 1)
		{
			PopBack();
		}

		Iterator cur = _start;
		while (cur != pos)
		{
			cur++;
		}
		Iterator next = cur + 1;
		while (next != _finish)
		{
			*cur++ = *next++;
		}
		--_finish;
	}

	Iterator Begin()
	{
		return _start;
	}

	Iterator End()
	{
		return _finish;
	}
	
	size_t Size()
	{
		return _finish - _start;
	}

	ValueType& operator[](size_t index)
	{
		assert(_start + index < _finish);
		return _start[index];
	}

protected:
	void _CheckCapacity()
	{
		if (_finish == _endOfStorage)
		{
			size_t oldStorage = _finish - _start;
			size_t newStorage = oldStorage * 2 + 3;

			ValueType* tmp = new ValueType[newStorage];
			for (int i = 0; i < oldStorage; i++)
			{
				tmp[i] = _start[i];
			}
			delete[] _start;
			_start = tmp;
			_finish = _start + oldStorage;
			_endOfStorage = _start + newStorage;
		}
	}

protected:
	Iterator _start;			//目前使用空间的头
	Iterator _finish;			//目前使用空间的尾
	Iterator _endOfStorage;	//目前可用空间的尾
};


void TestVector()
{
	Vector<int> v;
	v.PushBack(1);
	v.PushBack(2);
	v.PushBack(3);
	v.PushBack(4);
	//v.PopBack();
	
	Vector<int>::Iterator it = v.Begin();
	while (it != v.End())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;
	
	v.Insert(it, 5);

	it = v.Begin();
	while (it != v.End())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;

	v.Erase(v.Begin()+2);
	it = v.Begin();
	while (it != v.End())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;
}