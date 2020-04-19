/*********************项目：注释转换**2016-8-21***********************************
项目简介：将C++风格注释转换成传统C风格注释的程序（//--> /*）
作    者：邵宗林
*********************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*********************************************************************************
定义枚举类型，注册所有的状态；用来确定注释转换的方向
分别包括：	nostate, cstate, cppstate, endstate
*********************************************************************************/
typedef enum
{
	nostate,
	cstate,
	cppstate,
	endstate
}STATEENUM;

/*********************************************************************************
定义状态机结构体 state_machine，注册状态机的文件指针和状态机的当前状态
*********************************************************************************/
typedef struct state_machine
{
	FILE *inputfile;
	FILE *outputfile;
	STATEENUM state;
}STATE_MACHINE;

STATE_MACHINE go_state = { 0 };

/*********************************************************************************
全局函数省明
void eventpro(char ch);
void eventproatno(char ch);
void eventproatc(char ch);
void eventproatcpp(char ch);
int	covert(FILE *fin, FILE *fout);
*********************************************************************************/
void eventpro(char ch);
void eventproatno(char ch);
void eventproatc(char ch);
void eventproatcpp(char ch);
void covert(FILE *fin, FILE *fout);

/*********************************************************************************
函数名称：covert
函数参数：两个文件指针
          FILE *fin  所要打开的源文件文件指针
          FILE *fout 重定向目标文件的文件指针
函数功能：状态转换
函数返回值：void
*********************************************************************************/
void covert(FILE *fin, FILE *fout)
{
	if (fin == NULL || fout == NULL)
	{
		printf("Error: Argument Invalid!\n");
		return -1;
	}
	char ch;
	go_state.inputfile = fin;
	go_state.outputfile = fout;
	go_state.state = nostate;

	while (go_state.state != endstate)
	{
		ch = fgetc(go_state.inputfile);
		eventpro(ch);
	}
}
/*********************************************************************************
函数名称：eventro
函数参数：char ch 从原文件读取到的字符
函数功能：状态处理函数，判断字符，确定需要调用的状态函数
函数返回值：void
*********************************************************************************/
void eventpro(char ch)
{
	switch (go_state.state)
	{
	case nostate:
		eventproatno(ch);
		break;
	case cstate:
		eventproatc(ch);
		break;
	case cppstate:
		eventproatcpp(ch);
		break;
	case endstate:
		printf("运行结束\n");
		break;
	default:
		break;
	}
}

/*********************************************************************************
函数名称：eventproatno
函数参数：char ch 从原文件读取到的字符
函数功能：无状态函数，判断ch，来确定状态机状态
函数返回值：void
*********************************************************************************/
void eventproatno(char ch)
{
	char nextch;
	switch (ch)
	{
	case '/':
		nextch = fgetc(go_state.inputfile);
		if (nextch == '/')
		{
			fputc(ch, go_state.outputfile);
			fputc('*', go_state.outputfile);
			go_state.state = cppstate;
			break;
		}

		else if (nextch == '*')
		{
			fputc(ch, go_state.outputfile);
			fputc(nextch, go_state.outputfile);
			go_state.state = cstate;

		}
		else
		{
			fputc(ch, go_state.outputfile);
			fputc(nextch, go_state.outputfile);
		}
		break;
	case EOF:
		go_state.state = endstate;
		break;
	default:
		fputc(ch, go_state.outputfile);
		break;

	}
}

/*********************************************************************************
函数名称：eventproatcpp
函数参数：char ch 从原文件读取到的字符
函数功能：cpp状态处理函数,将C++注释转换成C语言注释，补全C语言的右半部分
函数返回值：void
*********************************************************************************/
void eventproatcpp(char ch)
{
	char nextch;
	switch (ch)
	{
	case'*':
		nextch = fgetc(go_state.inputfile);
		if (nextch == '/')
		{
			fputc(' ', go_state.outputfile);
			fputc(' ', go_state.outputfile);
		}
		else
		{
			fputc(ch, go_state.outputfile);
			fputc(nextch, go_state.outputfile);
		}
		break;
	case'/':
		nextch = fgetc(go_state.inputfile);
		if (nextch == '/' || nextch == '*')
		{
			fputc(' ', go_state.outputfile);
			fputc(' ', go_state.outputfile);
		}
		else
		{
			fputc(ch, go_state.outputfile);
			fputc(nextch, go_state.outputfile);
		}
		break;
	case'\n':
	{
				fputc('*', go_state.outputfile);
				fputc('/', go_state.outputfile);
				fputc('\n', go_state.outputfile);
				go_state.state = nostate;
	}
		break;

	case EOF:
	{
				fputc('*', go_state.outputfile);
				fputc('/', go_state.outputfile);
				go_state.state = endstate;
	}
		break;
	default:
		fputc(ch, go_state.outputfile);
		break;
	}
}

/*********************************************************************************
函数名称：eventproatc
函数参数：char ch 从原文件读取到的字符
函数功能：C状态处理函数，补全C语言注释
函数返回值：void
*********************************************************************************/
void eventproatc(char ch)
{
	char nextch;
	switch (ch)
	{
	case '*':
		nextch = fgetc(go_state.inputfile);
		if (nextch == '/')
		{
			fputc('*', go_state.outputfile);
			fputc('/', go_state.outputfile);
			go_state.state = nostate;
		}
		else
		{
			fputc(ch, go_state.outputfile);
			fputc(nextch, go_state.outputfile);
		}
		break;
	case EOF:
	{
				go_state.state = endstate;
	}
		break;
	case'/':
		nextch = fgetc(go_state.inputfile);
		if (nextch == '/')
		{
			fputc(' ', go_state.outputfile);
			fputc(' ', go_state.outputfile);
		}
		else if (nextch == '*')
		{
			fputc(' ', go_state.outputfile);
			fputc(' ', go_state.outputfile);
		}
		else
		{
			fputc(ch, go_state.outputfile);
			fputc(nextch, go_state.outputfile);
			//	/**XXXXX**/
			//	/*XXXXX*/
			//第一行结束状态没有置空，会导致下一次出现问题；第二行会变成 空格空格XXXXX*/
			go_state.state = nostate;  
		}
		break;
	default:
		fputc(ch, go_state.outputfile);
		break;
	}
}