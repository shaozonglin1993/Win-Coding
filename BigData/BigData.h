/*************************************************************************************
大数据运算头文件---BigData.h
*************************************************************************************/
#pragma once

#include <string>
#include <iostream>
using namespace std;

#define UN_INIT 0xcccccccccccccccc
#define MAX_INT64 0x7fffffffffffffff
#define MIN_INT64 0x8000000000000000

typedef long long INT64;
/*************************************************************************************
class BigData
*************************************************************************************/
class BigData
{
public:
	BigData(INT64 datad = UN_INIT);
	BigData(const char *pData);

/*************************************************************************************
运算符重载函数
+	-	*	/	%
函数参数：BigData& bigData	BigData类型的引用
*************************************************************************************/
	BigData operator+(BigData& bigData);
	BigData operator-(const BigData& bigData);
	BigData operator*(const BigData& bigData);
	BigData operator/(const BigData& bigData);
	BigData operator%(const BigData& bigData);

/*************************************************************************************
友元函数运算符重载
*************************************************************************************/
	friend ostream& operator<<(ostream& _cout, const BigData& bigData);

private:
	string Add(string left, string right);
	string Sub(string left, string right);
	string Mul(string left, string right);
	string Div(string left, string right);

	void INT64ToString();

	bool IsINT64Owerflow()const;

	bool IsLeftStrBig(char *pLeft, size_t LSize, char *pRight, size_t RSize);

	char SubLoop(char *pLeft, size_t LSize, char *pRight, size_t RSize);

private:
	long long m_llValue;
	string m_strData;
};