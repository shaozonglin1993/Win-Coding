#ifndef _TYPE_TRAITS_H_
#define _TYPE_TRAITS_H_


struct __TrueType
{
	bool Get()
	{
		return true ;
	}
};

struct __FalseType
{
	bool Get()
	{
		return false ;
	}
};
//
// 使用参数推到的萃取处理
//
template<class T>
void Copy(const T* src, T* dst, size_t size, __FalseType);

template<class T>
void _Copy(const T* src, T* dst, size_t size, __TrueType);

//
// 使用萃取判断类型的Get函数判断是否是POD类型来处理
//
template<class T>
void __Copy(const T* src, T* dst, size_t size);

/*Test Case*/
void typeTraits_test1(void);



#endif	/*end of file*/