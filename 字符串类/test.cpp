#define _CRT_SECURE_NO_WARNINGS 

#include <iostream>
#include <assert.h>
using namespace std;

class String
{
public:
	String(const char* str = "")
	{
		int len = strlen(str);
		_capacity = len + 1;
		_size = len;
		_str = new char[_capacity];
		strcpy(_str, str);
	}

	void _Swap(String& s)
	{
		swap(_str, s._str);
		swap(_size, s._size);
		swap(_capacity, s._capacity);
	}

	String(const String& s)
		:_str(new char[1]())
	{
		String tmp = s._str;
		_Swap(tmp);
	}

	//String 析构函数
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

	//重载运算符 =
	String& operator=(String s)
	{
		String _Swap(s);
		return *this;
	} 

	bool operator>(const String& s)
	{
		return strcmp(_str, s._str) > 0 ? true : false;
	}

	bool operator<(const String& s)
	{
		return strcmp(_str, s._str)>0 ? false : true;
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

	//PushBack
	void PushBack(char ch)
	{
		// ?
		_CheckCapacity(_size + 2);

		_str[_size++] = ch;
		_str[_size] = '\0';

		//Insert(_size, ch);
	}

	//Insert一个字符
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

		/*int len = 1;
		_size += len;
		_str = _CheckCapacity();

		for (size_t i = _size; i >= pos; i--)
		{
			_str[i] = _str[i - 1];
		}
		_str[pos - 1] = ch;
	}*/
	//Insert 一个字符串
		void Insert(size_t pos, const char* str)
		{
			assert(pos <= _size);

			size_t strSize = strlen(str);
			_CheckCapacity(_size + 1 + strSize);

			// 挪动数据
			int end = _size;
			while (end >= (int)pos)   // end 与 pos 类型不同，防止死循环
			{
				_str[end + strSize] = _str[end];
				--end;
			}
			// strcpy;?
			while (*str)
			{
				_str[pos++] = *str++;
			}

			_size += strSize;
		}

	//void Insert(size_t pos,const char* str)
	//{
	//	assert(pos <= _size);

	//	int len = strlen(str);
	//	_size += len;
	//	_str = _CheckCapacity();

	//	for (size_t i = _size; i >= pos; i--)
	//	{
	//		_str[i] = _str[i - len];
	//	}
	//	for (size_t i = 0; i < len; i++)
	//	{
	//		_str[pos + 1] = str[i];
	//	}
	//}

	//重载[]
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

	//Erase n个字符
	void Erase(size_t pos, size_t n)
	{
		assert(pos < _size);
		for (size_t i = pos; i < _size; i++)
		{
			_str[i] = _str[i + n];
		}
		_size -= n;
	}

	//Erase pos 一个字符
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
	void _CheckCapacity(size_t size)
	{
		if (size >= _capacity)
		{
			//size_t NewCapacity = (_capacity * 2 > (_size + 1) ? _capacity * 2 : (_size + 1));
			int newCapacity = size > 2 * _capacity ? size : 2 * _capacity;
			_str = (char*)realloc(_str, newCapacity);
			_capacity = newCapacity;
		}
	}

	char *_str;
	size_t _size;
	size_t _capacity;
};



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
	s1.Insert(1, 'H');
	s1.Display();
}
void Test3()
{
	String s1("hello rld");
	char *str = "wo";
	s1.Insert(6, str);
	s1.Display();
}
void Test4()
{
	String s1("Hello");
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

int main()
{
	//Test1();
	Test2();
	//Test3();
	//Test4();
	//Test5();
	//Test6();
	system("pause");
	return 0;
}

//#include <iostream>
//#include <windows.h>
//using namespace std;
//
//class String
//{
//public:
//	String(const char* str)
//		:_str(new char[strlen(str) + 1])		//'\0'要加1
//		, _pCount(new int(1))
//	{
//		strcpy(_str, str);
//	}
//
//	String(String& s)
//		:_str(s._str)
//		, _pCount(s._pCount)
//	{
//		++(*_pCount);
//	}
//
//	String& operator=(const String& s)
//	{
//		if (_str != s._str)
//		{
//			//释放原对象
//			if (--(*_pCount) == 0)  
//			{
//				delete _pCount;
//				delete[] _str;
//			}
//
//			//浅拷贝并增加引用计数
//			_str = s._str;
//			_pCount = s._pCount;
//			++(*_pCount);
//		}
//
//		return *this;
//	}
//
//	~String()
//	{
//		if (--(*_pCount) == 0)
//		{
//			delete _pCount;
//			delete[] _str;
//		}
//	}
//
//private:
//	char* _str;
//	int* _pCount;		//引用计数
//};
//
//namespace COW
//{
//	class String
//	{
//	public:
//		String(const char* str)
//			:_str(new char[strlen(str) + 5])
//		{
//			_str += 4;
//			strcpy(_str, str);
//
//			_GetRefCount(_str) = 1;
//		}
//
//		String(const String& s)
//			:_str(s._str)
//		{
//			++_GetRefCount(_str);
//			
//		}
//
//		String&  operator=(const String& s)
//		{
//			if (_str != s._str)
//			{
//				_Release();
//
//				_str = s._str;
//				++_GetRefCount(_str);
//			}
//
//			return *this;
//		}
//		~String()
//		{
//			_Release();
//		}
//
//		char& operator[](size_t pos)
//		{
//			//引用计数大于1，需要完成写实拷贝
//			if (_GetRefCount(_str) > 1)
//			{
//				char* tmp = new char[strlen(_str) + 5];  //5: 计数空间+'\0'
//				tmp += 4;
//				strcpy(tmp, _str);
//				_GetRefCount(tmp) = 1;
//
//				--_GetRefCount(_str);
//				_str = tmp;
//			}
//			return _str[pos];
//		}
//
//		//const String* this
//		const char& operator[](size_t pos) const
//		{
//			return _str[pos];
//		}
//
//		int Find(const String& s)
//		{
//			return -1;
//		}
//
//	private:
//		int& _GetRefCount(char* str)
//		{
//			return *((int*)(str - 4));
//		}
//
//		void _Release()
//		{
//			if (--_GetRefCount(_str) == 0)
//			{
//				delete[](_str - 4);
//			}
//		}
//
//	private:
//		char* _str;
//	};
//}
//
//void Test5()
//{
//	int begin = GetTickCount();
//
//	COW::String s1("1111111111111111111111111111111111111111");
//	for (int i = 0; i < 1000000; ++i)
//	{
//		COW::String s2(s1);
//		// cout<<s2<<endl;
//		//...
//	}
//
//	int end = GetTickCount();
//
//	cout << end - begin << endl;
//}
//
//int main()
//{
//	String s1 = "111111111111111111111";
//	String s2(s1);
//	String s3 = "222222222222222222222";
//	String s4(s3);
//
//	Test5();
//	system("pause");
//	return 0;
//}