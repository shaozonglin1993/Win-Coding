#include <iostream>
#include"BitMap.h"

using namespace std;
void test()
{
	BitMap bm1(100);
	bm1.Set(1);
	bm1.Set(33);
	bm1.Set(69);
	bm1.Set(100);

	bm1.ReSet(33);
}
int main()
{
	test();
	system("pause");
	return 0;
}