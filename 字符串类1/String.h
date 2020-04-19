#pragma once

#include <assert.h>

class String
{
public:
	String(const char* str = "")
	{
		int len = strlen(str);			//字符串长度
		_capacity = len + 1;				//字符串容量'\0'加1
		_size = len;						//字符串长度
		_str = new char[_capacity];		//开辟空间
		strcpy(_str, str);				//将_str的内容拷贝到_str中
	}

	//交换函数
	void _Swap(String& s)			//引用传参
	{
		swap(_str, s._str);
		swap(_size, s._size);
		swap(_capacity, s._capacity);
	}

	String(const String& s)
		:_str(new char[1]()) //new char[1](NULL)
	{
		String tmp = s._str;
		_Swap(tmp);
	}

	//析构函数
	~String()  
	{
		if (_str)
		{
			delete[]_str;
			_str = NULL;
		}
	}

	void Display()
	{
		cout << _str << endl;
	}

	/********************************************************/
	/***********************重载各个运算符*******************/
	/********************************************************/
	
	String& operator=(String s)
	{
		String _Swap(s);
		return* this;
	}

	bool operator>(const String& s)
	{
		return strcmp(_str, s._str) > 0 ? true : false;
	}

	bool operator<(const String& s)
	{
		return strcmp(_str, s._str) > 0 ? false : true;
	}

	bool operator==(const String& s)
	{
		return strcmp(_str, s._str) == 0 ? true : false;
	}

	bool operator>=(const String& s)
	{
		return strcmp(_str, s._str) >= 0 ? true : false;
	}

	bool operator<=(const String& s)
	{
		return strcmp(_str, s._str) <= 0 ? true : false;
	}

	/************************************************************/
	/***********************实现String常见函数*******************/
	/************************************************************/

	//尾插
	void PushBack(char ch)
	{
		_CheckCapacity(_size + 2);

		_str[_size++] = ch;
		_str[_size] = '\0';
	}

	//pos位置插入字符ch
	void Insert(size_t pos, char ch)
	{
		assert(pos <= _size);
		_CheckCapacity(_size + 2);
		int end = _size + 1;
		while (end >= pos)
		{
			_str[end] = _str[end - 1];
			--end;
		}
		_str[pos - 1] = ch;
		++_size;
	}

	/*
	int len = 1;
	_size += len;
	_str = _CheckCapacity();
	for (size_t i = _size; i >= pos; i++)
	{
		_str[i] = _str[i - 1];
	}
	_str[pos - 1] = ch;
	*/

	//pos位置插入一个字符串* str
	void Insert(size_t pos, const char* str)
	{
		assert(pos <= _size);

		size_t strSize = strlen(str);
		_CheckCapacity(_size + 1 + strSize);

		int end = _size;
		while (end >= (int)pos)
		{
			_str[end + strSize] = _str[end];
			--end;
		}
		while (*str)
		{
			_str[pos++] = *str++;
		}
		_size += strSize;
	}

	char& operator[](size_t index)
	{
		return _str[index];
	}

	//Find一个字符
	int Find(char ch)
	{
		for (size_t i = 0; i < _size; i++)
		{
			if (_str[i] == ch)
			{
				return i;
			}
		}
		return -1;
	}

	//Find一个字符串
	int Find(const char* str)
	{
		const char* pscr = _str;
		const char* psub =  str;

		int scrlen = _size;
		int sublen = strlen(str);

		int scrIndex = 0;
		while (scrIndex <= scrlen - sublen)
		{
			int i = scrIndex;
			int j = 0;
			while (scrlen > i && j < sublen && pscr[i] == psub[j])
			{
				i++;
				j++;
			}
			if (j == sublen)
			{
				return scrIndex;
			}
			scrIndex++;
		}
		return -1;
	}

	//删除pos位置后的n个字符
	void Erase(size_t pos, size_t n)
	{
		assert(pos < _size);
		for (size_t i = pos; i < _size; i++)
		{
			_str[i] = _str[i + n];
		}
		_size -= n;
	}

	//删除pos位置的字符
	void Erase(size_t pos)
	{
		assert(pos < _size);
		for (size_t i = pos; i < _size; i++)
		{
			_str[i] = _str[i + 1];
		}
		_size--;
	}


private:
	//检查指针指向空间的大小并进行扩容
	void _CheckCapacity(size_t size)
	{
		if (size >= _capacity)
		{
			int newCapacity = size > 2 * _capacity ? size : 2 * _capacity;
			_str = (char*)realloc(_str, newCapacity);
			_capacity = newCapacity;
		}
	}

	char *_str;          //字符串指针
	size_t _size;		//字符串容量
	size_t _capacity;		//字符串空间大小
};


//测试
void Test1()
{
	String s1("hello world");
	s1.Display();
	String s2(s1);
	s2.Display();
	String s3("change world");
	s1 = s3;
	s1.Display();
}

void Test2()
{
	String s1("ello world");
	s1.Insert(1, 'h');
	s1.Display();
}

void Test3()
{
	String s1("hello rld");
	char* str = "wo";
	s1.Insert(6, str);
	s1.Display();
}

void Test4()
{
	String s1("hello");
	cout << s1[0] << endl;
}
void Test5()
{
	String s1("hello world");
	cout << s1.Find("ll") << endl;
}

void Test6()
{
	String s1("hello world");
	s1.Erase(2, 3);
	s1.Display();
}