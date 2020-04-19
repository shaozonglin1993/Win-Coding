#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>

//初始化一个数组

void init(char arr[5][5])
{
	int i = 0, j = 0;
	for (i = 0; i < 5; i++)
	{
		for (j = 0; j < 5; j++)
		{
			arr[i][j] = ' ';
		}
	}
}

//打印棋盘

void print_cheseboard(char arr[][5])
{
	int i = 0;
	for (i = 0; i < 5; i++)
	{
		printf("| %c | %c | %c | %c | %c |\n", arr[i][0], arr[i][1], arr[i][2], arr[i][3], arr[i][4]);
		if (i != 4)
			printf("|---|---|---|---|---|\n");
	}
}

//玩家下棋

void player_move(char arr[][5])
{
	int x = 0;
	int y = 0;
	printf("请输入坐标>>>  \n");
	scanf("%d%d", &x, &y);
	x -= 1;
	y -= 1;
	if (arr[x][y] == ' ')
		arr[x][y] = 'X';
	else
	{
		printf("输入有误，请重新输入：\n");
		player_move(arr);
	}
}

//电脑下棋

void computer_move(char arr[][5])
{
	int i = 0, j = 0;
	for (i = 0; i < 5; i++)
	{
		for (j = 0; j < 5; j++)
		{
			if (arr[i][j] == ' ')
				break;
		}
		if (arr[i][j] == ' ')
			break;
	}
	if (i*j == 25)
		exit(0);
	else
		arr[i][j] = '0';
}

//战况判断

char check(char arr[][5])
{
	int i = 0;
 	for (i = 0; i < 5; i++)
	{
		if (arr[i][0] == arr[i][1] && arr[i][1] == arr[i][2] && arr[i][2] == arr[i][3] && arr[i][3] == arr[i][4])
		{
			if (arr[i][0] != ' ')
				return arr[i][0];
		}
	}
	for (i = 0; i < 5; i++)
	{
		if (arr[0][i] == arr[1][i] && arr[1][i] == arr[2][i] && arr[2][i] == arr[3][i] && arr[3][i] == arr[4][i])
		{
			if (arr[0][i] != ' ')
				return arr[0][i];
		}
	}
	if (arr[0][0] == arr[1][1] && arr[1][1] == arr[2][2] && arr[2][2] == arr[3][3] && arr[3][3] == arr[4][4])
	{
		if (arr[0][0] != ' ')
			return arr[0][0];
	}
	if (arr[0][4] == arr[1][3] && arr[1][3] == arr[2][2] && arr[2][2] == arr[3][1] && arr[3][1] == arr[4][0])
	{
		if (arr[0][4] != ' ')
			return arr[0][4];
	}
	return  ' ';
}

//主函数
int main()
{
	char done=' ';
	char arr[5][5];
	init(arr); 
	do
	{
		print_cheseboard(arr);
		player_move(arr);
		done = check(arr);
		if (done != ' ')
		{
			break;
		}
		 computer_move(arr);
		done = check(arr);
	} while (done == ' ');
	if (done == 'X')
		printf("玩家胜！！！\n");
	else
		printf("电脑胜！！！\n");
	print_cheseboard(arr);
	system("pause");
	return 0;
}