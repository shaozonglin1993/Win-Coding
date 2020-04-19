
#include "SeqList.h"

int main()
{
	SeqList list;
	SeqList* p = &list;
	size_t i = 0;
	InitSeqList(&list);
	for (i = 0; i < 10; i++)
	{
		p->array[i] = i;
		p->size++;
	}
	/*p->array[10] = 3;
	p->array[11] = 10;
	p->size += 2;
	PrintSeqList(&list);*/
//	PushBack(&list, 10);
//	PopBack(&list);
//	PushFront(&list, 10);
//	PopFront(&list);
//	Insert(&list, 5, 10);
//	printf("%d\n", Find(&list, 9));
//	Erase(&list, 5);
//	Remove(&list, 2);
//	RemoveAll(&list, 3);
	BubbleSort(&list);
	PrintSeqList(&list);
//	printf("%d\n", BinarySearch(&list, 1));
	printf("%d\n", _BinarySearch_R(&list, 0, p->size, 10));
	PrintSeqList(&list);
	system("pause");
	return 0;
}