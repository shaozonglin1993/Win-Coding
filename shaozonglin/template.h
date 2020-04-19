#ifndef _TEMPLATE_H_
#define _TEMPLATE_H_

/*ordinary function*/
bool IsEqual(int left, int right);
bool IsEqual(const std::string& left, const std::string& right);
void test1(void);

/*template function*/
template<typename T>
bool _IsEqual(const T& left, const T& right);
void test2(void);
void test3(void);

/*overload template function*/
template<class T1, class T2>
bool _IsEqual(const T1& left, const T2& right);

/*ordinary class*/
typedef int DataType;
class SeqList;

/*template class*/
template<typename T>
class _SeqList;
/*动态顺序表*/
void test4(void);

/*Container adapter*/
/*模板参数*/
template<class T,class Container>
	class Stack;
void test5(void);

/*模板的模板参数*/
template<class T,template<class> class container>
class _Stack;
void test6(void);

/*标准容器适配器使用*/
void test9(void);

/*非类型的类模板参数*/
template<class T,size_t MAX_SIZE>
class __SeqList;
void test7(void);

/*非类型的模板函数参数*/
template <class T, int value>
T Add(const T& x );
void test8(void);

/*浮点数和类对象是不允许作为非类型模板参数的*/



#endif	/*end of file*/