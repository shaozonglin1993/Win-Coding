#include "notes.h"

int main()
{
	FILE *fin, *fout;
	char p[100];

	printf("请输入要转换的文件路径：\n");
	scanf("%s", &p);
	
	if ((fin = fopen(p, "r")) == NULL)
	{
		printf("无法打开原文件：\n");
		exit(0);
	}

	if ((fout = fopen("C:\\Users\\john\\Desktop\\output.txt", "w")) == NULL)
	{
		printf("无法创建新文件：\n");
		exit(0);
	}

	covert(fin, fout);

	fclose(fin);
	fclose(fout);

	system("pause");
	return(0);
}