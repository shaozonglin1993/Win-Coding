/***************************************************************
**	Copyright(c) 2019 VisionMC
**	File Name: typeConversion.cpp
**	Auther: Zonglin Shao  Version: 1.0  Data: 2019-5-14
**	Description: 
**		 C++四种强制类型转换
**		 static_cast/reinterpret_cast/const_cast/dynamic_cast
**        explicit关键字
**	History:null
***************************************************************/
#include <iostream>
#include "typeConversion.h"


void staticCast()
{
	int liv_i = 10;
	double ldv_d = static_cast<double>(liv_i);
	printf("%s \n","static_cast用于非多态类型的转换（静态转换）,任何标准转换都可以用它，但它不能用于两个不相关的类型进行转换。");
	//std::cout<<liv_i<<", "<<ldv_d<<std::endl;
	printf("int liv_i = %d, double ldv_d = %2f\n",liv_i,ldv_d);
}

int DoSomething (int i)
{
	std::cout<<"_FUNC_: DoSomething"<<std::endl;
	return 0;
}

void reinterpretCast()
{
	//
	// reinterpret_cast可以让编译器以FUNC的定义方式去看待 DoSomething函数
	// 所以非常的BUG，下面转换函数指针的代码是不可移植的，所以不建议这样用
	// C++不保证所有的函数指针都被一样的使用，所以这样用有时会产生不确定的结果
	//
	printf("%s \n","reinterpret_cast操作符用于将一种类型转换为另一种不同的类型。");
	FUNC f = reinterpret_cast< FUNC>(DoSomething );
	f();
}

void constCast()
{
	printf("%s\n","const_cast最常用的用途就是删除变量的const属性，方便赋值。");
	const int liv_a = 2;
	int* p = const_cast<int*>(&liv_a);
	*p = 3;//未定义行为

	std::cout<<"&liv_a = "<<&liv_a<<std::endl<<"p = "<<p<<std::endl;
	std::cout<<"liv_a的值没有改变 "<<liv_a<<std::endl;
}

/*另外一种情况*/
void InputInt(int *num)
{
	//
}
void constCastTest1(void)
{
	printf("在函数参数的传递上const_cast的作用才显现出来。\n");
	const int liv_num = 10;
	//InputInt(&liv_num); /*类型不兼容*/
	 InputInt(const_cast<int*>(&liv_num)); /*OK*/
}

/*再有一种情况*/
void constCastTest2(void)
{
	printf("定义一个非const的变量，却使用一个指向const值的指针来指向它，在程序的某处改变这个变量的值，使用const_cast。\n");
	std::cout<<"会出现constCast()中的未定义行为"<<std::endl;
}


class Base
{
public:
	virtual void f()
	{}
};

class Device:public Base
{
};

void fun(Base *pb)
{
	// dynamic_cast会先检查是否能转换成功，能成功则转换，不能则返回
	Device* pd1 = static_cast<Device*>(pb);
	Device* pd2 = dynamic_cast<Device*>(pb);
	std::cout<<"pd1:" <<pd1<<std::endl;
	std::cout<<"pd2:" <<pd2<<std::endl;
}


void dynamicCast()
{
	printf("dynamic_cast用于将一个父类对象的指针转换为子类对象的指针或引用（动态转换）\n\
	向上转型：子类对象指针->父类指针/引用（不需要转换）\n\
	向下转型：父类对象指针->子类指针/引用（用dynamic_cast转型是安全的）\n\
	1.  dynamic_cast只能用于含有虚函数的类\n\
	2.  dynamic_cast会先检查是否能转换成功，能成功则转换，不能则返回0\n");
	Base b;
	Device d;
	fun(&b);
	fun(&d);
}


/*
** 在强转中，对于单参数的构造函数，支持隐式类型的转换，所以当我们不
**需要隐式类型的转换的时候，我们就可以加上explicit关键字来防止，在
**构造函数的时候发生隐式类型的转换。
*/
class A
{
public :
	/*单参数的类构造函数的隐式类型转换。*/
	//explicit A (int a)
	A(int a)
	{
		std::cout<<"A(int a)" <<std::endl;
	}
	A(const A& a)
	{
		std::cout<<"A(const A& a)" <<std::endl;
	}
private :
	int _a ;
};

/*我们加上关键字后，用 = 来进行隐式类型转换，是编译不能通过的。*/
/*如果我们不加就可以通过*/
void ExplicitTest(void)
{
	A a1(1);
	// 隐式转换-> A tmp(1); A a2(tmp);
	A a2 = 1;
}