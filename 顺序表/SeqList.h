#pragma once			//只编译一次

#include <memory.h>
#include<assert.h>
#include <stdio.h>

#define  MAX_SIZE 100
typedef int DataType;			 //数据类型重命名
typedef struct SeqList		 //定义结构体类型
{
	DataType array[MAX_SIZE];	 // 数据段
	size_t size;				 // 数据个数
}SeqList;


//初始化结构体变量

void InitSeqList(SeqList* pSeq)
{
	memset(pSeq->array, 0, sizeof(DataType)*MAX_SIZE);
	pSeq->size = 0;
}


//打印结构体变量

void PrintSeqList(SeqList* pSeq)			
{
	size_t i = 0;
	assert(pSeq);

	for (i = 0; i < pSeq->size; i++)
	{
		printf("%d ", pSeq->array[i]);
	}

	printf("\n");
}


//在结构体数组变量的最后面插入x

void PushBack(SeqList* pSeq, DataType x)		
{
	assert(pSeq);
	if (pSeq->size >= MAX_SIZE)			//判断顺序表是否已经满了
	{
		printf("list is full！\n");
		return;
	}
	pSeq->array[pSeq->size++] = x;	
}


//删除最后面一个有效元素

void PopBack(SeqList* pSeq)			
{
	assert(pSeq);		//指针判空
	if (pSeq->size == 0)	//顺序表判空
	{
		printf("list is empty!\n");
		return;
	}
	//pSeq->size--;					//pSeq->size - 1;直接size-1，删除未知的数据为重置
	pSeq->array[--pSeq->size] = 0;		//pSeq->size - 1 && pSeq->array[p->size-1]=0;数据重置
}


//在顺序表最前面插入一个x

void PushFront(SeqList* pSeq, DataType x)		
{
	assert(pSeq);
	int begin = pSeq->size - 1;		//数组下标为数据个数减1；
	if (pSeq->size >= MAX_SIZE)		//顺序表判断是否已经满了
	{
		printf("list is full!\n");
		return;
	}
	for (; begin >= 0; begin--)
	{
		pSeq->array[begin + 1] = pSeq->array[begin];		//所有数据向后移动一位，赋值x给p->array[0];
	}
	pSeq->array[0] = x;
	pSeq->size++;			//size+1；

}


//删除顺序表最首位元素

void PopFront(SeqList* pSeq)		
{
	assert(pSeq);		//指针判空
	int i = 1;
	if (pSeq->size <= 0)	//顺序表判空
	{
		printf("list is empty!\n");
		return;
	}
	for (i = 1; i < pSeq->size; i++)
	{
		pSeq->array[i - 1] = pSeq->array[i];			//所有元素前移一位
	}
	pSeq->size--;				//size-1
}


//在pos 位置 插入x

void Insert(SeqList* pSeq, size_t pos, DataType x)  
{
	assert(pSeq);	//指针判空
	size_t end = pSeq->size - 1;
	if (pSeq->size >= MAX_SIZE)		
	{
		printf("list is full!\n");		//顺序表判满
		return;
	}
	for (; end >= pos; end--)
	{
		pSeq->array[end + 1] = pSeq->array[end];		//pos位置及以后的元素全部后移一位，pos位置置为x
	}
	pSeq->array[pos] = x;		
	pSeq->size++;		//插入数据，size 加1
}


//寻找x的位置

int Find(SeqList* pSeq, DataType x)		
{
	assert(pSeq);		//指针判空
	if (pSeq->size <= 0)	//顺序表判空
	{
		printf("list is empty!\n");
		return -1;
	}
	rsize_t i = 0;
	for (i = 0; i < pSeq->size; i++)
	{
		if (pSeq->array[i] == x)
		{
			return i;		//返回数据x 的下表值
		}
	}
	return -1;		//未找到x返回 -1
}


// 删除pos位置的数据

void Erase(SeqList* pSeq, size_t pos)		
{
	assert(pSeq);				//指针判空
	if (pos >= pSeq->size)		//pos值error
	{
		printf("pos is error!\n");
		return;
	}
	rsize_t i = pos;				//pos值OK
	for (; i < pSeq->size-1; i++)
	{
		pSeq->array[i] = pSeq->array[i + 1];		//pos位置pos位置以后的全部数据前移一位
	}
	pSeq->array[i + 1] = 0;		//最后一位重置为0
	pSeq->size--;				//size-1
}


// 删除找到的第一个x

void Remove(SeqList* pSeq, DataType x)		
{
	assert(pSeq);		//指针判空
	size_t i = 0;
	for (; i < pSeq->size; i++)
	{
		if (pSeq->array[i] == x)
		{
			size_t ret = Find(pSeq, x);		//调用Find函数找到X的位置
			Erase(pSeq, ret);					//调用Erase函数删除该数据元素
		}
	}									//pSeq->size不用减1，Erase已经处理了
}


//删除所有的x
//思路：定义两个相同值下标（preIndex和aftIndex），当找到X后aftIndex加1 ，preIndex不变记录X的位置，当
//下标aftIndex值为X，该元素赋值到preIndex位置

void RemoveAll(SeqList* pSeq, DataType x)		
{
	assert(pSeq);		//指针判空
	int count = 0;
	int preIndex = 0;		
	int aftIndex = 0;
	while (preIndex < pSeq->size)
	{
		if (pSeq->array[aftIndex] != x)		//寻找顺序表中的X
		{
			pSeq->array[preIndex] = pSeq->array[aftIndex];	
			preIndex++;
		}
		else
		{
			count++;
		}
		aftIndex++;
	}
	pSeq->size -= count;			//size-删除的X的个数
}


//冒泡排序：它重复地走访过要排序的数列，一次比较两个元素，如果他们的顺序错误就把他们交
//换过来。走访数列的工作是重复地进行直到没有再需要交换，也就是说该数列已经排序完成

void BubbleSort(SeqList* pSeq)			
{
	int begin = 1;
	int end = pSeq->size;
	assert(pSeq);

	for (; end > 0; --end)
	{
		int exchange = 0;
		for (begin = 1; begin < end; begin++)				//该for循环第一个条件必须填写
		{
			if (pSeq->array[begin - 1] > pSeq->array[begin])
			{
				DataType tmp = pSeq->array[begin - 1];
				pSeq->array[begin - 1] = pSeq->array[begin];
				pSeq->array[begin] = tmp;
				exchange = 1;
			}
		}

		if (exchange == 0)
		{
			return;
		}
	}
}


//选择排序
//选择排序（Selection sort）是一种简单直观的排序算法。它的工作原理是每一次从待排序的数据元素中选出最小（或最大）的一个元素，存放在
//序列的起始位置，直到全部待排序的数据元素排完。 选择排序是不稳定的排序方法（比如序列[5， 5， 3]第一次就将第一个[5]与[3]交换，导致
//第一个5挪动到第二个5后面）。

void SeclectSort(SeqList* pSeq)			
{

}


//非递归实现二分法查找

int BinarySearch(SeqList* pSeq, DataType x)			
{
	int left = 0;
	int right = pSeq->size;						//pSeq->array[pSeq->size] 不是数组的元素，是数组后面的元素
	assert(pSeq);

	while (left < right)
	{
		int mid = left + (right - left) / 2;
		if (pSeq->array[mid] < x)
		{
			left = mid + 1;
		}
		else if (pSeq->array[mid] > x)
		{
			right = mid;
		}
		else
		{
			return mid;
		}
	}

	return -1;
}


//递归实现二分法查找

int _BinarySearch_R(SeqList* pSeq, int left, int right, DataType x)  
{
	assert(pSeq);
	int mid = 0;
	if (left < right)
	{
		mid = left + (right - left) / 2;

		if (pSeq->array[mid] < x)
		{
			return _BinarySearch_R(pSeq, mid + 1 , right, x);			
		}
		else if (pSeq->array[mid] > x)
		{
			return _BinarySearch_R(pSeq, left, mid, x);
		}
		else
		{
			return mid;
		}
	}
	return -1;
}


