#include <stdio.h>
using namespace std;
#include <stdlib.h>
#include "offer.h"

int main()
{
	int data[10] = { 1, 2, 3, 4, 4, 4, 4, 5, 6, 7 };
	int count = GetNumberOfK(data, 10, 4);
	printf("%d\n", count);

	system("pause");
	return 0;
}