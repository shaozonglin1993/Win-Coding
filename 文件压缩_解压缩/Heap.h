/**************************************************************************
堆：以小堆的方式建立二叉树
**************************************************************************/
#pragma once
#include <vector>
#include <cassert>


template<class T, class Compare>
class Heap
{
public:
	Heap()
	{}

	Heap(const T* array, size_t size)
	{
		assert(array);

		for (int i = 0; i< size; ++i)
		{
			_array.push_back(array[i]);
		}

		for (int i = _array.size() / 2 - 1; i >= 0; --i)
		{
			_AdjustDown(_array, i, _array.size());
		}
	}

	Heap(const vector<T>& vec)
	{
		_array.swap(vec);

		for (int i = _array.size() / 2 - 1; i >= 0; --i)
		{
			_AdjustDown(_array, i, _array.size());
		}
	}

	// 插入一个数据x到最小堆中
	void Push(const T& x)
	{
		_array.push_back(x);

		if (_array.size() > 1)
		{
			_AdjustUp(_array, _array.size() - 1);
		}
	}

	// 删除堆顶元素
	void Pop()
	{
		int size = _array.size();
		assert(size > 0);

		swap(_array[0], _array[size - 1]);
		_array.pop_back();

		if (_array.size() > 1)
		{
			_AdjustDown(_array, 0, _array.size());
		}
	}

	const T& Top()
	{
		return _array[0];
	}

/**************************************************************************
函数名称：_AdjustDown
哈数参数：vector<T>& vec		vector<T>实例引用
		 int root			根节点（即数组下表标值）
		 int size			实例大小（即数组大小）
返回值类型：void
函数功能：将根节点向下调整（小堆举例）
**************************************************************************/
	void _AdjustDown(vector<T>& vec, int root, int size)
	{
		// 1.child指向左孩子节点
		int child = root * 2 + 1;
		while (child < size)
		{
			// 2.child指向左右孩子中小的节点
			if (child + 1 < size && Compare()(vec[child + 1], vec[child]))
			//if (child + 1 < size && vec[child+1] < vec[child])
			{
				++child;
			}

			// 3.若child小于根节点，则交换child和root节点，并继续向下调整
			if (Compare()(vec[child], vec[root]))
				//if (vec[child] < vec[root])
			{
				swap(vec[child], vec[root]);
				root = child;
				child = root * 2 + 1;
			}
			else
			{
				break;
			}
		}
	}

/**************************************************************************
函数名称：_AdjustUp
函数参数：vector<T>& vec		vector<T> 实例的引用
		 int pos				数组最后一个值的下标
返回值类型：void
函数功能：一个节点向上调整（小堆举例说明）
**************************************************************************/
	void _AdjustUp(vector<T>& vec, int pos)
	{
		// 1.parent指向父节点
		int child = pos;
		int parent = (child - 1) / 2;

		// 当child==0时，则上调完成。不能使用parent来判断，parent不会小于0
		//while(parent >= 0)
		while (child > 0)
		{
			// 2.若child小于父节点，则交换父子节点，并继续向上调整，直到根节点
			if (Compare()(vec[child], vec[parent]))
			//if (vec[child] < vec[parent])
			{
				swap(vec[child], vec[parent]);
				child = parent;
				parent = (child - 1) / 2;
			}
			else
			{
				break;
			}
		}
	}

	// 判断是否为空
	bool Empty()
	{
		return _array.empty();
	}

	size_t Size()
	{
		return _array.size();
	}

private:
	vector<T> _array;
};