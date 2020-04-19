#include"BigData.h"
#include<stdlib.h>

int main()
{
	BigData d1("22222222222222222222222222222222222222222");
	BigData d2("11111111111111111111111111111111111111111");

	cout << d1 + d2 << endl;
	cout << d1 - d2 << endl;
	cout << d1*d2 << endl;
	cout << d1 / d2 << endl;
	system("pause");
	return 0;
}