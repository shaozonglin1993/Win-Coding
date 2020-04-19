/***************************************************************
**	Copyright(c) 2019 VisionMC
**	File Name: smartPointer.cpp
**	Auther: Zonglin Shao  Version: 1.0  Data: 2019-5-14
**	Description: 
**			smart pointer<shared_ptr,unique_ptr,weak_ptr>
**			a simple smart pointer demo and some test cases
**	History:null
***************************************************************/
#include <iostream>
#include <memory>
#include "smartPointer.h"

/*shared_ptr*/
void SharedSmartPointer(void)
{
	int liv_a = 10;
    std::shared_ptr<int> ptra = std::make_shared<int>(liv_a);
    std::shared_ptr<int> ptra2(ptra);	//copy construct
    std::cout << ptra.use_count() << std::endl;

	int liv_b = 20;
    int *pb = &liv_a;
    //std::shared_ptr<int> ptrb = pb;  //error
    std::shared_ptr<int> ptrb = std::make_shared<int>(liv_b);
    ptra2 = ptrb;
    pb = ptrb.get();	//The member function returns the stored pointer.

    std::cout << ptra.use_count() << std::endl;
    std::cout << ptrb.use_count() << std::endl;
}

/*unique_ptr*/
void uniqueSmartPointer(void)
{
	std::unique_ptr<int> uptr(new int(10));  //绑定动态对象
    //std::unique_ptr<int> uptr2 = uptr;  //不能赋值
    //std::unique_ptr<int> uptr2(uptr);  //不能拷贝
    std::unique_ptr<int> uptr2 = std::move(uptr); //转换所有权
    uptr2.release(); //释放所有权
}

/*weak_ptr*/
void WeakSmartPointer(void)
{
	std::shared_ptr<int> sh_ptr = std::make_shared<int>(10);
    std::cout << sh_ptr.use_count() << std::endl;

    std::weak_ptr<int> wp(sh_ptr);
    std::cout << wp.use_count() << std::endl;

	/*weak_ptr可以使用一个非常重要的成员函数lock()从被观测的
	shared_ptr获得一个可用的shared_ptr对象， 从而操作资源。
	但当expired()==true的时候，lock()函数将返回一个存储空指针的shared_ptr。*/

    if(!wp.expired())	//expired()等价于use_count()==0
	{
        std::shared_ptr<int> sh_ptr2 = wp.lock(); //get another shared_ptr
        *sh_ptr = 100;
        std::cout << wp.use_count() << std::endl;
    }
}

/*循环引用*/
class Parent
{
public:
	void SetChild(std::shared_ptr<Child> child) 
	{
		this->ChildPtr = child;
	}

    void doSomething() 
	{
        //new shared_ptr
        if (this->ChildPtr.lock())
		{

        }
    }

    ~Parent(){}
private:
	std::weak_ptr<Child> ChildPtr;
};

class Child
{
public:
	void SetParent(std::shared_ptr<Parent> parent)
	{
		this->ParentPtr = parent;
	}
	void doSomething()
	{
		if (this->ParentPtr.use_count())
		{

		}
	}

	~Child(){}
private:
	std::shared_ptr<Parent> ParentPtr;
};

void ReferenceLoop(void)
{
	std::weak_ptr<Parent> wpp;
    std::weak_ptr<Child>  wpc;
    {
        std::shared_ptr<Parent> p(new Parent);
        std::shared_ptr<Child>  c(new Child);
        p->SetChild(c);
        c->SetParent(p);
        wpp = p;
        wpc = c;
        std::cout << wpp.use_count() << std::endl; // 2
        std::cout << wpc.use_count() << std::endl; // 1
    }
    std::cout << wpp.use_count() << std::endl;  // 0
    std::cout << wpc.use_count() << std::endl;  // 0
}

/*smart pointer demo*/
template<typename T>
class SmartPointer 
{
private:
    T* _ptr;
    size_t* _count;
public:
    SmartPointer(T* ptr = nullptr) 
		:_ptr(ptr) 
	{
        if (_ptr) 
		{
            _count = new size_t(1);
        }
		else 
		{
            _count = new size_t(0);
        }
    }

    SmartPointer(const SmartPointer& ptr) 
	{
        if (this != &ptr) 
		{
            this->_ptr = ptr._ptr;
            this->_count = ptr._count;
            (*this->_count)++;
        }
    }

    SmartPointer& operator=(const SmartPointer& ptr) 
	{
        if (this->_ptr == ptr._ptr) 
		{
            return *this;
        }

        if (this->_ptr) 
		{
            (*this->_count)--;
            if (this->_count == 0) 
			{
                delete this->_ptr;
                delete this->_count;
            }
        }

        this->_ptr = ptr._ptr;
        this->_count = ptr._count;
        (*this->_count)++;
        return *this;
    }

    T& operator*() 
	{
        assert(this->_ptr == nullptr);
        return *(this->_ptr);

    }

    T* operator->() 
	{
        assert(this->_ptr == nullptr);
        return this->_ptr;
    }

    ~SmartPointer() 
	{
        (*this->_count)--;
        if (*this->_count == 0) 
		{
            delete this->_ptr;
            delete this->_count;
        }
    }

    size_t use_count()
	{
        return *this->_count;
    }
};

void SmartPointerDemo(void)
{
	SmartPointer<int> sp(new int(10));
    SmartPointer<int> sp2(sp);
    SmartPointer<int> sp3(new int(20));
    sp2 = sp3;
    std::cout << sp.use_count() << std::endl;
    std::cout << sp3.use_count() << std::endl;
}