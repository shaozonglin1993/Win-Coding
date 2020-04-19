#include <iostream>
#include "smartPointer.h"
#include "template.h"
#include "typeTraits.h"
#include "typeConversion.h"
#include "ioStream.h"
//#include <pthread.h>

using namespace std;

//#define SMART_POINTER
//#define TEMPLATE
#define TYPR_TRAITS
//#define TYPE_CONVERSION
//#define IO_STREAM



void main()
{
#ifdef SMART_POINTER
	SharedSmartPointer();
	uniqueSmartPointer();
	WeakSmartPointer();
	ReferenceLoop();
	SmartPointerDemo();
#endif

#ifdef TEMPLATE
	//test1();
	//test2();
	//test3();
	//test4();
	//test5();
	//test6();
	//test7();
	//test8();
	test9();
#endif

#ifdef TYPR_TRAITS
	typeTraits_test1();
#endif

#ifdef TYPE_CONVERSION
	//staticCast();
	//reinterpretCast();
	//constCast();
	//constCastTest1();
	//constCastTest2();
	//dynamicCast();
	ExplicitTest();
#endif

#ifdef IO_STREAM
	test_io();
#endif


	system("pause");
}