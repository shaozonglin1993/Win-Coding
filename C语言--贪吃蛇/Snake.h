#define MAX_R 20		//宏定义地图的列数
#define MAX_C 10		//宏定义地图的行数

//定义结构体,节点
typedef struct ListNode
{
	char ch;
	struct ListNode* next;
}ListNode;

ListNode* head = NULL;

//初始化一个数组
void Init(ListNode arr[][MAX_R])
{
	int i = 0, j = 0;
	for (i = 0; i < MAX_C; i++)
	{
		for (j = 0; j < MAX_C; j++)
		{
			arr[i][j].ch = ".";
		}
	}
}


//打印贪吃蛇地图
void PrintMap(ListNode arr[][MAX_R])
{
	printf("map\n");
	int i = 0, j = 0;
	for (i = 0; i < MAX_C; i++)
	{
		for (j = 0; j < MAX_R; j++)
		{
			if (arr[i][j].ch == '1')			//1  蛇头
			{
				arr[i][j].ch = '@';
				printf("%c", arr[i][j].ch);
			}
			else if (arr[i][j].ch == '2')		//2  食物
			{
				arr[i][j].ch = '*';
				printf("%c", arr[i][j].ch);
			}
			else if (arr[i][j].ch == '3')		//3  蛇身
			{
				arr[i][j].ch = '*';
				printf("%c", arr[i][j].ch);
			}
			else
			{
				arr[i][j].ch = '.';
				printf("%c", arr[i][j].ch);
			}
		}
		printf("\n");
	}
	printf("\n");
}


//食物随机产生函数
void Creat_Food(ListNode arr[][MAX_R])
{
	srand(time(0));
	int i = 0, j = 0;
	i = (rand() % MAX_C);
	j = (rand() % MAX_R);
	arr[i][j].ch = '2';

}

//键盘输入字符方向
void Button(ListNode arr[][MAX_R],size_t head,size_t tail)
{
	arr[head][tail].ch = '1';		//蛇头初始化位置
	char key;
	if (_kbhit() != 0) //检查当前是否有键盘输入，若有则返回一个非0值，否则返回0  
	{
		while (_kbhit() != 0)  //可能存在多个按键,要全部取完,以最后一个为主  
		{
			key = getchar(); //将按键从控制台中取出并保存到key中  
		}
		switch (key)
		{
		case 56:
			head--;
			break;
			//8-上  
		case 50:
			head++;
			break;
			//2-下  
		case 52:
			
			break;
			//4-左  
		case 54:
			break;
			//6-右
		}
	}
}
//贪吃蛇运动函数
//void SnakeMove(ListNode arr[][MAX_R])
//{
//	char ch;
//	int i = 5, j = 5;
//	//arr[i][j].ch = '1';		//蛇头初始化位置
//	//arr[i][j].next = &arr[i + 1][j];
//	//arr[i + 1][j].ch = '3';
//	printf("请输入：");
//	scanf("%c", &ch);
//	switch (ch)
//	{
//	case'8':
//		if (arr[i - 1][j].ch == '2')
//		{
//			arr[i - 1][j].ch = '1';
//			arr[i - 1][j].next = &arr[i][j];
//			arr[i][j].ch = '3';
//		}
//		else
//		{
//			arr[i + 1][j].ch = '1';
//			arr[i + 1][j].next = &arr[i][j];
//			arr[i - 1][j].ch = '0';
//		}
//	}
//}

	//system("cls");	//刷新
	//Sleep(1000);

	//fflush(stdout);