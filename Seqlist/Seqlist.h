#pragma once

typedef int DataType;
class SeqList
{
public:
	SeqList(DataType* array, size_t size)
	: _array(array)
	,_size(size)
	, _capacity(size)
	{
		//memcpy();
	}
	~SeqList()
	{
		delete[] _array;
	}
	void PushBack(const DataType& x);

private:
	DataType* _array;
	size_t _size;
	size_t _capacity;
};