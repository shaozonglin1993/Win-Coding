#pragma once

#include <stdio.h>
#include <malloc.h>
#include <assert.h>

typedef int DataType;			//数据类型重命名

typedef struct _node			//定义节点结构体
{
	DataType data;			//数据
	struct _node* next;		//指向下一个节点的指针
}ListNode;

void InitList(ListNode** head)			//初始化head
{
	*head = NULL;
}

ListNode* CreatNode(DataType val)
{
	ListNode* tmp = (ListNode*)malloc(sizeof(ListNode));
	assert(tmp);
	tmp->data = val;
	tmp->next = NULL;
	return tmp;
}

void PushBack(ListNode** head, DataType x)
{
	assert(head);
	if (*head == NULL)			//空链表
	{
		*head = CreatNode(x);
	}
	else							//非空链表
	{
		ListNode* tail = *head;
		while (tail->next)
		{
			tail = tail->next;
		}
		tail->next = CreatNode(x);
	}
}


void ShowList(ListNode* head)
{
	assert(head);
	ListNode* cur = head;
	while (cur)
	{
		printf("%d ", cur->data);
		cur = cur->next;
	}
	printf("\n");
}

void PushHead(ListNode** head, DataType x)
{
	//if (NULL == *head)				//空链表
	//{
	//	*head = CreatNode(x);
	//}
	//else							//非空链表
	//{
	//	ListNode* tmp = CreatNode(x);
	//	tmp->next = *head;
	//	*head = tmp;
	//}

	ListNode* tmp = CreatNode(x);			//没有分情况，似乎没有什么问题
	tmp->next = *head;
	*head = tmp;
}


void PopBack(ListNode** head)
{
	if (NULL == *head)				//空链表
	{
		printf("list is empty!");
		return;
	}
	else if (NULL == (*head)->next)			//只有一个节点
	{
		free(*head);
		*head = NULL;
	}
	else										//多个节点
	{
		ListNode* tail = *head;
		ListNode* pre = *head;
		while (tail->next)
		{
			pre = tail;
			tail = tail->next;
		}
		pre->next = NULL;
		free(tail);
	}
}

void PopFront(ListNode** head)
{
	if (NULL == *head)		//空链表
	{
		printf("list is empty!");
		return;
	}
	else                     //非空链表
	{
		ListNode* tag = *head;
		*head = (*head)->next;
		free(tag);
	}
}

ListNode* Find(ListNode** head, DataType x)
{
	ListNode* cur = *head;
	while (cur)
	{
		if (cur->data == x)
		{
			return cur;
		}
		
		cur = cur->next;
	}
	return NULL;
}

void Insert(ListNode* pos, DataType x)			//在pos位置进行插入
{
	assert(pos);
	ListNode* new_node = CreatNode(x);
	ListNode* tmp = pos->next;
	new_node->data = pos->data;			//将x赋值给pos->data,将pos->data赋值给pos->data;交换顺序
	pos->data = x;
	pos->next = new_node;
	new_node->next = tmp;
}

void InsertFrontNode(ListNode* pos, DataType x)			//在pos位置的前面进行插入
{
	assert(pos);
	ListNode* tmp = CreatNode(x);
	tmp->next = pos->next;
	pos->next = tmp;
	tmp->data = pos->data;

	pos->data = x;
	
}


void Erase(ListNode** head, ListNode* pos)
{
	assert(pos);
	if (pos == *head)			//第一个节点
	{
		*head = (*head)->next;
		free(pos);
	}
	else
	{
		ListNode* cur = *head;
		while (cur)
		{
			if (cur->next == pos)
			{
				cur->next = pos->next;
				free(pos);
				break;
			}
			cur = cur->next;
		}
	}
}

void DelNonTailNode(ListNode* pos)					//删除非尾节点
{
	assert(pos && pos->next);
	
	ListNode* del = pos->next;			//将pos->next->data赋值给pos->data，把pos->next  free,在串起来
	ListNode* tmp = pos->next->next;
	pos->data = pos->next->data;
	pos->next = tmp;
	free(del);
}

void Remove(ListNode** head, DataType x)
{
	ListNode* remv = Find(head, x);
	if (remv)
	{
		Erase(head, remv);
	}
}

ListNode* Reverse(ListNode* head)
{
	ListNode* newHead = NULL;
	ListNode* cur = head;
	while (cur)
	{
		ListNode* tmp = cur;
		cur = cur->next;

		tmp->next = newHead;
		newHead = tmp;
	}
	return newHead;
}

void PrintTailtoHead(ListNode* head)		//递归实现从尾到头打印
{
	if (head)
	{
		PrintTailtoHead(head->next);
		printf("%d ", head->data);
	}
}

ListNode* FindMid(ListNode* head)			//找链表中间数据的位置并返回
{
	ListNode* slow = head;
	ListNode* fast = head;
	while (fast && fast->next)
	{
		slow = slow->next;
		fast = fast->next->next;
	}
	return slow;
}


DataType Find_TheLast_Knode(ListNode* head, int k)							//查找倒数第K个节点，遍历一次
{
	assert(head);
	ListNode* pre = head;						//定义两个指针，分别指向前面和后面
	ListNode* aft = head;
	int i = 1;
	while (aft)
	{
		if (i <= k)
		{
			aft = aft->next;
			i++;
		}
		else
		{
			aft = aft->next;
			pre = pre->next;
		}
	}									//指针aft和pre保持距离为(k-1)，则遍历完成之后，pre即为倒数第K个节点
	if ( i > k && k != 0)				//不存在倒数第0个节点
	{
		return pre->data;
	}
	else
		return -1;
}

void swap(DataType* n, DataType* m)		//交换两个数
{
	DataType tmp = *n;
	*n = *m;
	*m = tmp;

}

void BubbleSort(ListNode** head)				//链表的冒泡排序
{
	assert(head);
	//一个节点
	if (NULL == (*head)->next)
	{
		return;
	}
	else
	{
		while (1)
		{
			ListNode* cur = (*head)->next;
			ListNode* p = *head;
			int exchange = 0;	//进行判断是否发生交换
			while (cur)
			{
				if (p->data > cur->data)
				{
					swap(&(p->data), &(cur->data));
					exchange = 1;
				}
				cur = cur->next;
				p   = p->next;
			}
			if (exchange == 0)  //一趟循环结束未发生交换则return，跳出死循环						
			{
				return;
			}
		}
	}
}

ListNode* Merge_List(ListNode* l1, ListNode* l2)
{
	if (NULL == l1 || NULL == l2)
	{
		return l1 == NULL ? l2 : l1;
	}
	ListNode* newhead = CreatNode(0);
	ListNode* l = newhead;
	ListNode* cur1 = l1;
	ListNode* cur2 = l2;
	while (cur1 && cur2)
	{
		if (cur1->data > cur2->data)
		{
			l->next = cur2;
			l = l->next;
			cur2 = cur2->next;
		}
		else
		{
			l->next = cur1;
			l = l->next;
			cur1 = cur1->next;
		}
	}
	l->next= (cur1 == NULL ? cur2 : cur1);
	ListNode* tmp = newhead;
	newhead = newhead->next;
	free(tmp);
	tmp = NULL;
	return newhead;

}

ListNode* Joseph_Cycle(ListNode* head,int k)
{
	if (NULL == head)
	{
		printf("list is empty!\n");
		return NULL;
	}
	
	ListNode* cur = head;
	while (cur->next != NULL)
	{
		cur = cur->next;
	}
	ListNode* tmp = NULL;
	cur->next = head;
	cur = head;
	int count = k;
	while (1)
	{
		count = k;
		if (cur->next != cur)
		{
			while (--count)
			{
				cur = cur->next;
			}
			tmp = cur->next;
			cur->data = cur->next->data;
			cur->next = cur->next->next;
			free(tmp);
		}
		else
		{
			cur->next = NULL;
			return cur;
		}
	}
}

ListNode* CreatCycle(ListNode* phead,int k)		//为单链表创造一个环
{
	if (NULL == phead)			//phead为空
	{
		printf("list is empty!\n");
		return NULL;
	}
	ListNode* pos = Find(&phead, k);
	if (pos == NULL)
	{
		printf("k is error!\n");
	}

	ListNode* pos1 = pos;
	ListNode* tail = phead;
	while (tail->next)			//找到list的尾节点
	{
		tail = tail->next;
	}
	tail->next = pos1;			//list的尾节点*next指向pos 
	tail = phead;				//cur 指向头结点
	return tail;
}

int IsLoop(ListNode* phead)			//判断链表是否有环，有环返回1；否则返回-1；
{
	if (NULL == phead)
	{
		printf("list is empty!\n");
		return -1;
	}
	ListNode* slow = phead;	//快指针 
	ListNode* fast = phead;	//慢指针
	while (fast && fast->next)	
	{
		fast = fast->next->next;	//fast = 2*slow
		slow = slow->next;
		if (&slow->data == &fast->data)
		{
			return 1;
		}
	}
	return -1;
}

ListNode* MeetNode(ListNode* phead)		//返回快慢指针在环中相遇的节点,同时也可以判断是否存在环
{
	if (NULL == phead)
	{
		printf("list is empty!\n");
		return -1;
	}
	ListNode* slow = phead;	//快指针 
	ListNode* fast = phead;	//慢指针
	while (fast && fast->next)
	{
		fast = fast->next->next;	//fast = 2*slow
		slow = slow->next;
		if (&slow->data == &fast->data)			//if(slow == fast);
		{
			return slow;
		}
	}
	return NULL;
}

int GetLength(ListNode* phead)		//求单链表的节点个数
{
	int count = 0;
	ListNode* cur = phead;
	if (NULL == phead)		//空表
	{
		return count;
	}
	else				//非空表	
	{
		while (cur)
		{
			cur = cur->next;
			count++;
		}
		return count;
	}
}

ListNode* GetEnterNode(ListNode* phead)		//求有环单链表的环的入口节点
{
	ListNode* meet = MeetNode(phead);	//判断list是否存在环

	if (NULL == meet)				    //没有环的情况
	{
		printf("there is no cycle in the list!\n");	
		return NULL;
	}
	else								//有环的情况
	{
		ListNode* tar = meet;
		ListNode* cur = phead;
		while (tar != cur)			//2*（L + X）=L + X + nC   L = nC - X
		{
			cur = cur->next;
			tar = tar->next;
		}
		return cur;			//返回环入口节点
	}
}










