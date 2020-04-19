#include <iostream>
#include<windows.h>
using namespace std;
#include "FileCompress.h"

void test()
{
	FileCompress<CharInfo> f;
	int begin1 = GetTickCount();
	f.Compress("test.txt");
	int end1 = GetTickCount();

	cout << "Compress Time:"<<end1 - begin1 << endl;

	int begin2 = GetTickCount();
	f.UnCompress("test.txt");
	int end2 = GetTickCount();

	cout <<"UnCompress Time:"<< end2 - begin2 << endl;
}
int main()
{
	test();
	//long long l;
	//printf("%d\n", sizeof(l));//8

	//int i = 3;
	//char c = 3;
	//int n = i & c;
	//printf("%d\n", n);

	system("pause");
	return 0;
}