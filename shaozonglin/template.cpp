/***************************************************************
**	Copyright(c) 2019 VisionMC
**	File Name: template.cpp
**	Auther: Zonglin Shao  Version: 1.0  Data: 2019-5-15
**	Description: 
**			template
**	History:null
***************************************************************/
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include "template.h"

bool IsEqual(int left, int right)
{
	return left == right;
}

bool IsEqual(const std::string& left, const std::string& right)
{
	return left == right;
}

void test1(void)
{
	std::string s1("s1"),s2("s2");
	std::cout<<IsEqual(s1,s2)<<std::endl;
	std::cout<<IsEqual(1,1)<<std::endl;
}

//模板形参的定义既可以使用class，也可以使用typename，含义是相同的
//template <class 形参名1, class 形参名2, class 形参名n>
//返回类型 函数名(参数列表)
//{...}

template<typename T>
bool _IsEqual(const T& left, const T& right)
{
	return left == right;
}

void test2(void)
{
	std::string s1("s1"),s2("s2");
	std::cout<<_IsEqual(s1,s2)<<std::endl;
	std::cout<<_IsEqual(1,1)<<std::endl;
}

/*模板参数匹配及显示实例化*/
void test3(void)
{
	std::string s1("s1"),s2("s2");
	std::cout<<_IsEqual<std::string>(s1,s2)<<std::endl;
	std::cout<<_IsEqual<int>(1,1)<<std::endl;
}

/*overload template function*/
template<class T1, class T2>
bool _IsEqual(const T1& left, const T2& right)
{
	return left == right;
}


//template<class 形参名1, class 形参名2, ...class 形参名n>
//class 类名
//{ ... };

typedef int DataType;
class SeqList
{
public:
	SeqList();
	~SeqList();
private:
	DataType* data;
	int _size;
	int _capacity;
};

template<typename T>
class _SeqList
{
public:
	_SeqList();
	~_SeqList();
private:
	int _size;
	int _capacity;
	T* data;
};

/*动态顺序表*/
template<typename T>
_SeqList<T>::_SeqList()
	:_size(0)
	,_capacity(10)
	,data(new T[_capacity])
{}

template<typename T>
_SeqList<T>::~_SeqList()
{
	delete[] data;
}

void test4(void)
{
	_SeqList<int> s11;
	_SeqList<double> s22;
}

template<class T, class Container = _SeqList<T>>
	class Stack
	{
	public:
		void Push(const T& x);
		void Pop();
		const T& Top();
		bool Empty();
	private:
		Container _con;
	};

void test5(void)
{
	Stack<int> s1;
	Stack<int, _SeqList<int>> s2;
	Stack<int, _SeqList<char>> s3;
}

template<class T, template<class> class Container=_SeqList>
class _Stack
{
public:
	void Push(const T& x);
	void Pop();
	const T& Top();
	bool Empty();
private:
	Container<T> _con;
};

void test6(void)
{
	_Stack<int> s1;
	_Stack<int , _SeqList> s2;
}

/*容器适配器使用*/
void test9(void)
{
	std::vector<int> v;
	for (int i=0; i<10; i++)
    {
		v.push_back(i);
	}
    std::cout <<"输出Vector容器："<<std::endl;
	for(std::vector<int>::iterator it = v.begin();it != v.end(); it++)
	{
		std::cout<<*it<<" ";
	}
	std::cout<<std::endl;

	/*为vector v配置容器适配器*/
	std::stack<int, std::vector<int>> s(v);

	/*
	 * 使用stack提供的方法处理数据
	*/
	std::cout<<"自顶向下输出栈(stack容器适配器)"<<std::endl;
	while(!s.empty())
	{
		std::cout<<s.top()<<" ";
		s.pop();
	}
	std::cout<<std::endl;
	std::cout<<"说明"<<std::endl;
	std::cout<<"1. 容器适配器只适用于一定的容器而不是所有容器。"<<std::endl;
	std::cout<<"2. 容器适配器的函数实现其实也是基于其参数容器的函数，而不是自己重新定义的。"<<std::endl;
	std::cout<<std::endl;
}


template<class T,size_t MAX_SIZE=10>
class __SeqList
{
public:
	__SeqList();
private :
	T _array [MAX_SIZE];
	int _size ;
};

template <class T, size_t MAX_SIZE>
__SeqList<T, MAX_SIZE>::__SeqList()
	:_size(0)
{}

void test7(void)
{
	__SeqList<int> s1;
	__SeqList<int , 20> s2;
}


template <class T, int value>
T Add(const T& x)
{
	return x+value;
}

void test8(void)
{
	std::cout<<Add<int,10>(10)<<std::endl;
}