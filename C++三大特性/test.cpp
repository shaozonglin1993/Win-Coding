//#include <iostream>
//#include <stdlib.h>
//#include <string>
//
//using namespace std;
//
//class Person
//{
//public:
//	Person(const string &_name)
//		:name(_name)
//	{}
//	Person();
//	void Display()
//	{
//		cout << name << endl;
//	}
//
//public:
//	string name;
//};
//
//class Student:public Person
//{
//public:
//	Student(const int &_num)
//		:num(_num)
//	{}
//
//public:
//	int num;
//};
//
//
//int main()
//{
//	/*Person Tom("Tom");
//	Tom.Display();*/
//	Student s;
//	system("pause");
//	return 0;
//}


//#include <iostream>
//#include <stdlib.h>
//
//using namespace std;
//
//class A
//{
//public:
//
//	void fun1()
//	{
//		cout << "fun1" << endl;
//	}
//
//	void fun2()
//	{
//		cout << "fun2" << endl;
//	}
//};
//
//class B:public A
//{
//public:
//	void fun3()
//	{
//		cout << "fun3" << endl;
//	}
//
//	void fun4()
//	{
//		cout << "fun4" << endl;
//	}
//};
//
//int main()
//{
//	B b;
//	b.fun1();
//	b.fun2();
//	b.fun3();
//	b.fun4();
//	system("pause");
//	return 0;
//}


//#include <iostream>
//using namespace std;
//#include <string>
//
//
//class Person
//{
//public:
//	void Display()
//	{
//		cout << _name << endl;	
//	}
//protected:
//	string _name;
//private:
//	int _age;
//};
//
//class Student :public Person
//{
//protected:
//	int _num;
//};
//
//int main()
//{
//	Student s;
//	s.Display();
//
//	Person p;
//
//	//p = s;
//	s = (Student&)p;
//
//	Person *p1 = &s;
//	Person &p2 = s;
//
//	system("pause");
//	return 0;
//}


//#include <iostream>
//using namespace std;
//
//class animal
//{
//public:
//	 void eat()
//	{
//		cout << "animal eat many things" << endl;
//	}
//	void move()
//	{}
//
//};
//
//class cat:public animal
//{
//public:
//	/*void eat()
//	{
//		cout << "cat eat mouse" << endl;
//	}*/
//
//};
//
//int main()
//{
//	cat c;
//	c.eat();
//
//	animal a;
//	a.eat();
//
//	system("pause");
//	return 0;
//}

/********************************************************************************************************************
指向基类的指针在操作它的多态类对象时，会根据不同的类对象，调用其相应的函数，这个函数就是虚函数
********************************************************************************************************************/

//#include <iostream>
//using namespace std;
//
//class A
//{
//public:
//	virtual void fun()
//	{
//		cout << "this is A" << endl;
//	}
//};
//
//
//class B:public A
//{
//public:
//	virtual void fun()
//	{
//		cout << "this is B" << endl;
//	}
//};
//
//int main()
//{
//	A a;
//	B b;
//	a.fun();
//	b.fun();
//
//	A *p1 = &a;
//	A *p2 = &b;
//	p1->fun();
//	p2->fun();
//
//	system("pause");
//	return 0;
//}

//#include <iostream>
//using namespace std;
//
//class Base {
//public:
//	virtual void f() { cout << "Base::f" << endl; }
//	virtual void g() { cout << "Base::g" << endl; }
//	virtual void h() { cout << "Base::h" << endl; }
//};
//
//class Drev :public Base
//{
//public:
//	//virtual void f()  { cout << "this is f()" << endl; }
//	virtual void f1() { cout << "Drev::f1" << endl; }
//	virtual void g1() { cout << "Drev::g1" << endl; }
//	virtual void h1() { cout << "Drev::h1" << endl; }
//};
//
//typedef void(*Fun)(void);
//
//int main()
//{
//
//	Drev d;
//	cout << "虚函数表地址：" << (int*)(&d) << endl;
//	cout << "虚函数表 — 第一个函数地址：" << (int*)*(int*)(&d) << endl;
//	Fun pFun0 = NULL;
//	Fun pFun1 = NULL;
//	Fun pFun2 = NULL;
//	Fun pFun3 = NULL;
//	Fun pFun4 = NULL;
//	Fun pFun5 = NULL;
//
//	pFun0 = (Fun)*((int*)*(int*)(&d) + 0);
//	pFun1 = (Fun)*((int*)*(int*)(&d) + 1);
//	pFun2 = (Fun)*((int*)*(int*)(&d) + 2);
//	pFun3 = (Fun)*((int*)*(int*)(&d) + 3);
//	pFun4 = (Fun)*((int*)*(int*)(&d) + 4);
//	pFun5 = (Fun)*((int*)*(int*)(&d) + 5);
//
//	pFun0();
//	pFun1();
//	pFun2();
//	pFun3();
//	pFun4();
//	pFun5();
//
//
//	Drev *p = new Drev;
//	p->f();
//
//	system("pause");
//	return 0;
//}



#include <iostream>
using namespace std;

class Base1 {
public:
	virtual void f() { cout << "Base1::f" << endl; }
	virtual void g() { cout << "Base1::g" << endl; }
	virtual void h() { cout << "Base1::h" << endl; }

};

class Base2 {
public:
	virtual void f() { cout << "Base2::f" << endl; }
	virtual void g() { cout << "Base2::g" << endl; }
	virtual void h() { cout << "Base2::h" << endl; }
};

class Base3 {
public:
	virtual void f() { cout << "Base3::f" << endl; }
	virtual void g() { cout << "Base3::g" << endl; }
	virtual void h() { cout << "Base3::h" << endl; }
};


class Derive : public Base1, public Base2, public Base3 {
public:
	virtual void f() { cout << "Derive::f" << endl; }
	virtual void g1() { cout << "Derive::g1" << endl; }
};


typedef void(*Fun)(void);

int main()
{
	Fun pFun = NULL;

	Derive d;
	int** pVtab = (int**)&d;

	//Base1's vtable
	//pFun = (Fun)*((int*)*(int*)((int*)&d+0)+0);
	pFun = (Fun)pVtab[0][0];
	pFun();

	//pFun = (Fun)*((int*)*(int*)((int*)&d+0)+1);
	pFun = (Fun)pVtab[0][1];
	pFun();

	//pFun = (Fun)*((int*)*(int*)((int*)&d+0)+2);
	pFun = (Fun)pVtab[0][2];
	pFun();

	//Derive's vtable
	//pFun = (Fun)*((int*)*(int*)((int*)&d+0)+3);
	pFun = (Fun)pVtab[0][3];
	pFun();

	//The tail of the vtable
	pFun = (Fun)pVtab[0][4];
	cout << pFun << endl;


	//Base2's vtable
	//pFun = (Fun)*((int*)*(int*)((int*)&d+1)+0);
	pFun = (Fun)pVtab[1][0];
	pFun();

	//pFun = (Fun)*((int*)*(int*)((int*)&d+1)+1);
	pFun = (Fun)pVtab[1][1];
	pFun();

	pFun = (Fun)pVtab[1][2];
	pFun();

	//The tail of the vtable
	pFun = (Fun)pVtab[1][3];
	cout << pFun << endl;



	//Base3's vtable
	//pFun = (Fun)*((int*)*(int*)((int*)&d+1)+0);
	pFun = (Fun)pVtab[2][0];
	pFun();

	//pFun = (Fun)*((int*)*(int*)((int*)&d+1)+1);
	pFun = (Fun)pVtab[2][1];
	pFun();

	pFun = (Fun)pVtab[2][2];
	pFun();

	//The tail of the vtable
	pFun = (Fun)pVtab[2][3];
	cout << pFun << endl;

	system("pause");
	return 0;
}

