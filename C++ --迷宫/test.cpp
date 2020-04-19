#include <iostream>
#include <stack>
#include <stdlib.h>
#include <assert.h>
using namespace std;

void GetMazeMap(int* a, int row, int col)
{
	FILE* fOut = fopen("MazeMap.txt", "r");
	assert(fOut);
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col;)
		{
			char ch = fgetc(fOut);
			if (ch == '0' || ch == '1')
			{
				a[i*col + j] = ch - '0';
				++j;
			}
		}
	}
	fclose(fOut);
}

void PrintMaze(int* a, int row, int col)
{
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < col; j++)
		{
			cout << a[i*col + j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}


struct Pos
{
	int row;
	int col;
};


bool CheckIsAcess(int* a, int rowSize, int colSize, Pos cur)
{
	if (cur.row < rowSize && cur.col < colSize && a[cur.row * colSize + cur.col] == 0)
	{
		return true;
	}
	return false;
}


stack<Pos> GetMazePath(int* a, int rowSize, int colSize, Pos entry)
{
	stack<Pos> paths;
	Pos cur = entry;
	paths.push(entry);
	while (!paths.empty())
	{
		Pos cur = paths.top();
		Pos next = cur;

		if (next.row == rowSize - 1)
		{
			return paths;
		}

		//left
		next = cur;
		next.col--;
		if (CheckIsAcess(a, 10, 10, next))
		{
			a[next.row * colSize + next.col] = 2;
			paths.push(next);
			continue;
		}

		//right
		next = cur;
		next.col++;
		if (CheckIsAcess(a, 10, 10, next))
		{
			a[next.row * colSize + next.col] = 2;
			cur = next;
			paths.push(next);
			continue;
		}

		//up 
		next.row--;
		if (CheckIsAcess(a, 10, 10, next))
		{
			a[next.row * colSize + next.col] = 2;
			paths.push(next);
			continue;
		}

		//down
		next = cur;
		next.row++;
		if (CheckIsAcess(a, 10, 10, next))
		{
			a[next.row * colSize + next.col] = 2;
			paths.push(next);
			continue;
		}
		Pos top = paths.top();
		a[top.row * colSize + top.col] = 3;
		paths.pop();
	}
	cout << "ц╩сп" << endl;
}


void TestMaze()
{
	int a[10][10] = {};
	GetMazeMap((int*)a, 10, 10);
	PrintMaze((int*)a, 10, 10);

	Pos entry = { 2, 0 };
	GetMazePath((int*)a, 10, 10, entry);
	PrintMaze((int*)a, 10, 10);
}

int main()
{
	TestMaze();
	system("pause");
	return 0;
}



