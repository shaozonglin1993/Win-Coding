#pragma once

#include <iostream>
#include <assert.h>
#include <stack>
using namespace std;

void Print(int* a, size_t size)
{
	for (int i = 0; i < size; i++)
	{
		cout << a[i] << " ";
	}
}

//直接插入排序
void Insert_Sort(int* a, size_t size)
{
	assert(a);
	//第一个数肯定是有序的，从第二个开始遍历
	for (int i = 1; i < size; i++)
	{
		int j = 0;
		int tmp = a[i];
		//前i-1个数已经是有序的，所以当tmp<a[j]时，将a[j]向后移动一位
		for (j = i - 1; j >= 0 && tmp < a[j]; j--)
		{
			a[j + 1] = a[j];
		}
		a[j + 1] = tmp;
	}
}

//希尔排序
void Shell_Sort(int* a, size_t size)
{
	assert(a);

	int gap = size;
	while (gap > 1)
	{
		gap = (gap / 3) + 1;//gap = gap/2;
		for (int i = gap; i < size; i++)
		{
			int index = i;
			int tmp = a[index];
			int end = index - gap;

			while (end >= 0 && tmp < a[end])
			{
				a[end + gap] = a[end];
				end -= gap;
			}
			a[end + gap] = tmp;
		}
	}
}

//堆排

//升序
void AdjustDown(int* a, size_t size, int root)
{
	assert(a);

	int child = root * 2 + 1;
	while (child < size)
	{
		if (child + 1 < size && a[child + 1] > a[child])
		{
			child++;
		}

		if (a[child] > a[root])
		{
			swap(a[child], a[root]);
			root = child;
			child = root * 2 + 1;
		}
		else
		{
			break;
		}
	}
}

void AdjustUp(int* a, size_t size, int root)
{
	assert(a);

	int child = root * 2 + 1;
	while (child < size)
	{
		if (child + 1 < size && a[child + 1] < a[child])
		{
			child++;
		}

		if (a[child] < a[root])
		{
			swap(a[child], a[root]);
			root = child;
			child = root * 2 + 1;
		}
		else
		{
			break;
		}
	}
}

void Heap_Sort(int* a, size_t size)
{
	assert(a);
	
	//建堆
	for (int i = (size - 2) / 2; i >= 0; i--)
	{
		AdjustDown(a, size, i);
	}

	for (int j = size - 1; j > 0; j--)
	{
		swap(a[0], a[j]);
		AdjustDown(a, j, 0);
	}
}

void _Heap_Sort(int* a, size_t size)
{
	assert(a);

	for (int i = (size - 2) / 2; i >= 0; i--)
	{
		AdjustUp(a, size, i);
	}

	for (int j = size - 1; j > 0; j--)
	{
		swap(a[0], a[j]);
		AdjustUp(a, j, 0);
	}
}

//快速排序

//冒泡排序
void BubbleSort(int* a, size_t size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size - i - 1; j++)
		{
			if (a[j]>a[j + 1])
			{
				swap(a[j], a[j + 1]);
			}
		}
	}
}

//key左边的都小于key,key右边的都大于key
int Partition1(int *a, int left, int right)
{
	assert(a);

	int begin = left, end = right - 1, key = a[right];
	while (begin < end)
	{
		while (a[begin] <= key && begin < end)
		{
			begin++;
		}
		while (a[end] >= key && end > begin)
		{
			end--;
		}
		if (begin < end)
		{
			swap(a[begin], a[end]);
		}
	}
	if (a[begin] > a[right])
	{
		swap(a[begin], a[right]);
		return begin;
	}
	else
	{
		return right;
	}
}

void QuickSort1(int *a, int left, int right)
{
	assert(a);
	if (right > left)
	{
		int boundary = Partition1(a, left, right);
		QuickSort1(a, left, boundary - 1);
		QuickSort1(a, boundary + 1, right);
	}
}

//prev在cur 后面，向前指向小于key的，cur向前指向大于Key的，逐次进行交换


int Partition2(int *a, int left, int right)
{
	assert(a);
	int cur = left, prev = left - 1, key = a[right];
	while (cur < right)
	{
		if (a[cur] < key && (++prev) != cur)
		{
			swap(a[prev], a[cur]);
		}
		++cur;
	}
	swap(a[++prev], a[right]);
	return prev;
}
void QuickSort2(int *a, int left, int right)
{
	assert(a);
	if (right > left)
	{
		int boundary = Partition2(a, left, right);
		QuickSort2(a, left, boundary - 1);
		QuickSort2(a, boundary + 1, right);
	}
}

//挖坑补位法
//设置一个key，此处key设置为最后面，则最后面位置是一个坑，
//begin向后找比key大的，放进先前的坑，end向前找比key小的，放入刚才的坑，一直重复
int Partition3(int* a, size_t left, size_t right)
{
	assert(a);

	int begin = left, end = right, key = a[end];
	while (begin < end)
	{
		//向前找比key大的
		while (begin < end && a[begin] <= key)
		{
			begin++;
		}
		if (begin < end)
		{
			a[end] = a[begin];
		}
		//从后向前找比key小的
		while (end > begin && a[end] >= key)
		{
			end--;
		}
		if (end > begin)
		{
			a[begin] = a[end];
		}
	}
	a[begin] = key;
	return begin;
}
void QuickSort3(int *a, int left, int right)
{
	assert(a);

	if (right > left)
	{
		int boundary = Partition3(a, left, right);
		QuickSort3(a, left, boundary - 1);
		QuickSort3(a, boundary + 1, right);
	}
}

//三数取中法
int GetMidIndex(int* a, size_t left, size_t right)
{
	int mid = left + (right - 1)/2;

	if (a[left] < a[right])
	{
		if (a[mid] < a[left])
			return left;
		else if (a[mid] < a[right])
			return mid;
		else
			return right;
	}
	else
	{
		if (a[mid] < a[right])
			return right; 
		if (a[mid] < a[left])
			return left;
		else
			return mid;
	}
}


//非递归方法

void QuickSort4(int* a, size_t left, size_t right)
{
	assert(a);

	stack<int> s;
	if (left < right)
	{
		int boundary = GetMidIndex(a, left, right);

		if (left < boundary - 1)
		{
			s.push(left);
			s.push(boundary - 1);
		}
		if (boundary + 1 < right)
		{
			s.push(boundary + 1);
			s.push(right);
		}
		while (!s.empty())
		{
			int end = s.top();
			s.pop();
			int begin = s.top();
			s.pop();
			boundary = Partition2(a, begin, end);

			if (begin < boundary - 1)
			{
				//左边界在下，右边界在上。
				s.push(begin);
				s.push(boundary - 1);
			}
			if (boundary + 1 < end)
			{
				s.push(boundary + 1);
				s.push(end);
			}
		}
	}
}

//选择排序

void SelectSort(int* a, size_t size)
{
	assert(a);

	for (int i = 0; i < size; i++)
	{
		int min = i;
		for (int j = i + 1; j < size; j++)
		{
			if (a[j] < a[min])
			{
				min = j;
			}
		}
		if (a[i] != a[min])
		{
			int tmp = a[i];
			a[i] = a[min];
			a[min] = tmp;
		}
	}
}

//归并排序

void MergeSection(int* a, int* tmp, size_t left, size_t mid, size_t right)
{
	assert(a);

	size_t i = left, j = mid + 1;
	size_t m = mid, n = right;
	int index = left;

	while (i <= m && j <= n)
	{
		if (a[i] <= a[j])
		{
			tmp[index++] = a[i++];
		}
		else
		{
			tmp[index++] = a[j++];
		}
	}
	while (i <= m)
	{
		tmp[index++] = a[i++];
	}
	while (j <= n)
	{
		tmp[index++] = a[j++];
	}
}

void _MergeSort(int* a, int* tmp, size_t left, size_t right)
{
	assert(a && tmp);

	if (left < right)
	{
		int mid = left + (right - left) / 2;
		_MergeSort(a, tmp, left, mid);
		_MergeSort(a, tmp, mid + 1, right);

		MergeSection(a, tmp, left, mid, right);

		memcpy(a + left, tmp + left, (right - left + 1)*sizeof(int));
	}
}

bool MergeSort(int* a, size_t size)
{
	assert(a);

	int* tmp = new int[size];
	if (tmp == NULL)
		return false;

	_MergeSort(a, tmp, 0, size - 1);
	delete[] tmp;

	return true;
}

//非比较排序

//计数排序

void CountSort(int* a, size_t size)
{
	assert(a);

	int max = a[0];
	int min = a[0];

	for (int i = 1; i < size; i++)
	{
		if (a[i] > max)
			max = a[i];			//数列最大值
		if (a[i] < min)
			min = a[i];			//数列最小值
	}
	int range = max - min + 1;
	int* CountArray = new int[range];			//开辟range个数的数组
	
	memset(CountArray, 0, sizeof(int)*range);

	for (size_t i = 0; i < size; i++)
	{
		CountArray[a[i] - min]++;			//a[i]-min 表示从下标为0开始
	}

	size_t index = 0;
	for (size_t i = 0; i < range; i++)
	{
		while(CountArray[i]--)
		{
			a[index++] = i + min;			//对每一个位置进行填数
		}
	}
	delete[] CountArray;					//一定要delete
	CountArray = NULL;
}

//基数排序
//LSD-- Least Significant Digit first
//MSD-- Most Significant Digit first

int GetMaxDigit(int* a, size_t size)
{
	assert(a);

	int digit = 1, max = 10;

	for (size_t i = 0; i < size; i++)
	{
		while (a[i] > max)
		{
			digit++;
			max *= 10;
		}
	}
	return digit;
}

void DigitSort(int* a, size_t size)
{
	assert(a);

	int maxDigit = GetMaxDigit(a, size);
	int* bucket  = new int[size];
	int count[10];
	int start[10];
	int digit = 1;
	int curDigit = 10;
	while (digit++ <= maxDigit)
	{
		memset(count, 0, sizeof(int)* 10);
		memset(start, 0, sizeof(int)* 10);
		//0-9号桶各有？个数
		for (size_t i = 0; i < size; i++)
		{
			int num = (a[i] / curDigit) % 10;
			count[num]++;
		}
		//计算个位数为[0-9]的数在桶里起始位置
		start[0] = 0;

		for (size_t i = 1; i < 10; i++)
		{
			start[i] = start[i - 1] + count[i - 1];
		}

		for (size_t i = 0; i < size; i++)
		{
			int num = (a[i] / curDigit) % 10;
			bucket[start[num]++] = a[i];
		}

		memcpy(a, bucket, sizeof(int)* 10);
		curDigit *= 10;
	}
	delete[] bucket;
	bucket = NULL;
}



//Test
void TestInsertSort()
{
	int a[5] = { 1, 3, 2, 4, 0 };
	Print(a, 5);
	cout << endl;
	Insert_Sort(a, 5);
	Print(a, 5);
	cout << endl;

}

void TestShell_Sort()
{
	int a[10] = { 49, 38, 65, 97, 76, 13, 27, 49, 55, 4 };
	Print(a, 10);
	cout << endl;

	Shell_Sort(a, 10);
	Print(a, 10);
	cout << endl;
}

void TestHeap_Sort()
{
	int a[10] = { 49, 38, 65, 97, 76, 13, 27, 49, 55, 4 };
	Print(a, 10);
	cout << endl;

	Heap_Sort(a, 10);
	Print(a, 10);
	cout << endl;
}

void Test_Heap_Sort()
{
	int a[10] = { 49, 38, 65, 97, 76, 13, 27, 49, 55, 4 };
	Print(a, 10);
	cout << endl;

	_Heap_Sort(a, 10);
	Print(a, 10);
	cout << endl;
}

void TestQuickSort1()
{
	//int a[10] = { 49, 38, 65, 97, 76, 13, 10, 12, 11, 100};
	int a[10] = { 0, 2, 4, 8, 6, 1, 5, 9, 7, 3 };
	Print(a, 10);
	cout << endl;

	QuickSort1(a, 0, 9);
	Print(a, 10);
	cout << endl;
}

void TestQuickSort2()
{
	int a[10] = { 49, 38, 3, 49, 55, 4 ,97, 7, 13, 27 };
	Print(a, 10);
	cout << endl;

	QuickSort2(a, 0, 9);
	Print(a, 10);
	cout << endl;
}

void TestQuickSort3()
{
	int a[10] = { 49, 38, 65, 97, 76, 13, 27, 49, 55, 4 };
	Print(a, 10);
	cout << endl;

	QuickSort3(a, 0, 9);
	Print(a, 10);
	cout << endl;
}

void TestQuickSort4()
{
	int a[10] = { 49, 38, 65, 97, 76, 13, 27, 49, 55, 4 };
	Print(a, 10);
	cout << endl;

	QuickSort3(a, 0, 9);
	Print(a, 10);
	cout << endl;
}

void TestSelectSort()
{
	int a[10] = { 49, 38, 65, 97, 76, 13, 27, 49, 55, 4 };
	Print(a, 10);
	cout << endl;

	SelectSort(a, 10);
	Print(a, 10);
	cout << endl;
}

void TestMergeSort()
{
	int a[10] = { 49, 38, 65, 97, 76, 13, 27, 49, 55, 4 };
	cout << "初始序列" << " :";
	Print(a, 10);
	cout << endl;

	MergeSort(a, 10);
	cout << "新 序 列" << " :";
	Print(a, 10);
	cout << endl;
}

void TestCountSort()
{
	int a[10] = { 49, 13, 65, 97, 4, 13, 27, 13, 55, 4 };
	Print(a, 10);
	cout << endl;

	CountSort(a, 10);
	Print(a, 10);
	cout << endl;
}

void TestBubbleSort()
{
	int a[10] = { 1, 3, 5, 7, 9, 0, 2, 6, 8, 4 };
	Print(a, 10);
	cout << endl;

	BubbleSort(a, 10);
	Print(a, 10);
	cout << endl;
}


void TestDigitSort()
{
	int a[10] = { 49, 38, 65, 97, 76, 13, 27, 49, 55, 4 };
	Print(a, 10);
	cout << endl;

	DigitSort(a, 10);
	Print(a, 10);
	cout << endl;
}

