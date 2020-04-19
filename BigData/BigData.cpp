/******************************************************************************************************
项目名称：大数据运算
技术运用：模板编程、指针、顺序表
项目描述：
		C++实现，解决了对于超过内存表示范围的大数据无法计算的问题
		用字符串表示整形的大数据，并实现各种运算，模拟整形数值的进位、借位，有效解决大数据的运算问题
		顺序表来存储字符串，实现基本的加、减、乘、除运算
******************************************************************************************************/
#include "BigData.h"
#include <assert.h>

BigData::BigData(INT64 data)
	: m_llValue(data)
	, m_strData("")
{
	INT64ToString();
}

BigData::BigData(const char *_pData)
{
	// "-12345789"  "1234567" "+" "12457aaa123" "000001234567"
	// "a23456789" 
	// atoi
	assert(NULL != _pData);

	char cSybom = _pData[0];
	char* pData = (char*)_pData;
	if ('+' == cSybom || '-' == cSybom)
	{
		pData++;
	}
	else if (*pData >= '0' && *pData <= '9')
	{
		cSybom = '+';
	}
	else           //缺省就直接返回
	{
		m_llValue = UN_INIT;
		return;
	}

 	// 去掉前置0
	while ('0' == *pData)
		pData++;

	// "12457aaa123"
	m_strData.resize(strlen(pData) + 1);    //string中size的大小不包括'\0'
	m_llValue = 0;
	m_strData[0] = cSybom;
	int iCount = 1;
	while (pData)
	{
		if (*pData >= '0' && *pData <= '9')
		{
			m_llValue = m_llValue * 10 + *pData - '0';
			m_strData[iCount++] = *pData++;
		}
		else
		{
			break;
		}
	}

	m_strData.resize(iCount);

	if ('-' == cSybom)
	{
		m_llValue = 0 - m_llValue;
	}
}

BigData BigData::operator+(BigData& bigData)
{
	// 8 + -2  10
	if (!IsINT64Owerflow() && !bigData.IsINT64Owerflow())
	{
		//如果两个数异号，一定不会溢出
		if (m_strData[0] != bigData.m_strData[0])
		{
			return BigData(m_llValue + bigData.m_llValue);
		}
		else
		{
			//3+4==>10-3>4
			//(-3)+(-4)==>-10-(-3)<(-4)
			if (('+' == m_strData[0] && MAX_INT64 - m_llValue >= bigData.m_llValue) ||
				('-') == m_strData[0] && MIN_INT64 - m_llValue <= bigData.m_llValue)
			{
				return BigData(m_llValue + bigData.m_llValue);
			}
		}
	}
	// 至少有一个溢出
	// 计算结果溢出
	string strRet;
	if (m_strData[0] == bigData.m_strData[0])
	{
		strRet = Add(m_strData, bigData.m_strData);
	}
	else
	{
		strRet = Sub(m_strData, bigData.m_strData);
	}

	return BigData(strRet.c_str());
}

BigData BigData::operator-(const BigData& bigData)
{
	if (!IsINT64Owerflow() && !bigData.IsINT64Owerflow())
	{
		//如果两个数同号，一定不会溢出
		if (m_strData[0] == bigData.m_strData[0])
		{
			return BigData(m_llValue - bigData.m_llValue);
		}
		else
		{
			//6-5=1 ==> 10+6 >= 5
			//-3-(-4)=1 => -10+(-3)<-4 
			if (('+' == m_strData[0] && MAX_INT64 + bigData.m_llValue >= m_llValue) ||
				('-' == m_strData[0] && MIN_INT64 + bigData.m_llValue <= m_llValue))
			{
				return BigData(m_llValue - bigData.m_llValue);
			}
		}
	}

	// 1、至少有一个操作数溢出
	// 2、相减的结果一定会溢出
	string strRet;
	if (m_strData[0] != bigData.m_strData[0])
	{
		strRet = Add(m_strData, bigData.m_strData);
	}
	else
	{
		strRet = Sub(m_strData, bigData.m_strData);
	}
	return BigData(strRet.c_str());
}

BigData BigData::operator*(const BigData& bigData)
{
	if (0 == m_llValue || 0 == bigData.m_llValue)
	{
		return BigData(INT64(0));
	}

	if (!IsINT64Owerflow() && !bigData.IsINT64Owerflow())
	{
		if (m_strData[0] == bigData.m_strData[0])
		{
			if (('+' == m_strData[0] && MAX_INT64 / m_llValue >= bigData.m_llValue) ||
				('-' == m_strData[0] && MAX_INT64 / m_llValue <= bigData.m_llValue))
			{
				return BigData(m_llValue*bigData.m_llValue);
			}
		}
		else
		{
			if (('+' == m_strData[0] && MIN_INT64 / m_llValue <= bigData.m_llValue) ||
				('-' == m_strData[0] && MIN_INT64 / m_llValue >= bigData.m_llValue))
			{
				return BigData(m_llValue*bigData.m_llValue);
			}
		}
	}

	return BigData(Mul(m_strData, bigData.m_strData).c_str());
}

BigData BigData::operator/(const BigData& bigData)
{
	if (0 == bigData.m_llValue)
	{
		assert("除数不能为0！");
		return BigData(INT64(0));
	}

	if (!IsINT64Owerflow() && !bigData.IsINT64Owerflow())
	{
		return BigData(m_llValue / bigData.m_llValue);
	}

	return BigData(Div(m_strData, bigData.m_strData).c_str());
}

string BigData::Add(string left, string right)
{
	int LSize = left.size();
	int RSize = right.size();
	if (LSize < RSize)
	{
		swap(left, right);
		swap(LSize, RSize);
	}

	string strRet;
	strRet.resize(LSize + 1);
	strRet[0] = left[0];
	char cStep = 0;

	//left = "+9999999"  size = 9 
	// right="1"   "+10000000" 
	for (int index = 1; index < LSize; ++index)
	{
		//先加上进位
		char cRet = left[LSize - index] - '0' + cStep;

		if (index < RSize)
		{
			cRet += (right[RSize - index] - '0');
		}

		strRet[LSize + 1 - index] = (cRet % 10 + '0');
		cStep = cRet / 10;
	}

	strRet[1] = (cStep + '0');

	return strRet;
}

std::string BigData::Sub(std::string left, std::string right)
{
	// 1、左操作数 > 右操作数
	// 2、确定符号位
	int LSize = left.size();
	int RSize = right.size();
	char cSymbol = left[0];
	if (LSize < RSize || (LSize == RSize && left < right))
	{
		swap(left, right);
		swap(LSize, RSize);
		if ('+' == cSymbol)
		{
			cSymbol = '-';
		}
		else
		{
			cSymbol = '+';
		}
	}

	string strRet;
	strRet.resize(LSize);
	strRet[0] = cSymbol;

	// 逐位相减
	// 1、取left每一位，从后往前取
	// 2、在right没有超出  取right每一位 从后往前取
	// 3、直接相减
	// 4、 保存结果
	for (int index = 1; index < LSize; ++index)
	{
		char cRet = left[LSize - index] - '0';
		if (index < RSize)
		{
			cRet -= right[RSize - index] - '0';
		}

		if (cRet < 0)
		{
			left[LSize - index - 1] -= 1;
			cRet += 10;
		}

		strRet[LSize - index] = cRet + '0';
	}

	return strRet;
}

std::string BigData::Mul(std::string left, std::string right)
{
	//左操作数<右操作数
	int LSize = left.size();
	int RSize = right.size();
	if (LSize > RSize)
	{
		std::swap(left, right);
		std::swap(LSize, RSize);
	}

	char cSymbol = '+';
	if (left[0] != right[0])
	{
		cSymbol = '-';
	}

	string strRet;
	//strRet.resize(LSize + RSize - 1);
	strRet.assign(LSize + RSize - 1, '0');
	strRet[0] = cSymbol;
	int DataLen = strRet.size();
	int Offset = 0;   //偏移

	for (int index = 1; index < LSize; ++index)
	{
		char cLeft = left[LSize - index] - '0';
		char cStep = 0;
		if (0 == cLeft)
		{
			Offset++;
			continue;
		}

		for (int RIdx = 1; RIdx < RSize; ++RIdx)
		{
			char cRet = cLeft*(right[RSize - RIdx] - '0');
			cRet += cStep;
			cRet += (strRet[DataLen - Offset - RIdx] - '0');
			strRet[DataLen - Offset - RIdx] = cRet % 10 + '0';
			cStep = cRet / 10;
		}

		strRet[DataLen - Offset - RSize] += cStep;
		Offset++;
	}

	return strRet;
}

std::string BigData::Div(std::string left, std::string right)
{
	char cSymbol = '+';
	if (left[0] != right[0])
	{
		cSymbol = '-';
	}

	int LSize = left.size();
	int RSize = right.size();
	if (LSize < RSize ||
		(LSize == RSize && strcmp(left.c_str() + 1, right.c_str() + 1) < 0))
	{
		return "0";
	}
	else
	{
		if ("+1" == right || "-1" == right)
		{
			left[0] = cSymbol;
			return left;
		}
	}

	string strRet;
	strRet.append(1, cSymbol);
	char *pLeft = (char*)(left.c_str() + 1);
	char *pRight = (char*)(right.c_str() + 1);
	int DataLen = 1;  //当前被除的位数
	LSize -= 1;   //-1是因为里面包括了符号位
	// "2422222222"  33
	for (int Idx = 0; Idx < LSize;)
	{
		if ('0' == *pLeft)
		{
			strRet.append(1, '0');
			pLeft++;
			Idx++;

			continue;
		}

		if (!IsLeftStrBig(pLeft, DataLen, pRight, RSize - 1))
		{
			strRet.append(1, '0');
			DataLen++;
			if (Idx + DataLen > LSize)
			{
				break;
			}
			continue;
		}
		else
		{
			// 循环相减
			strRet.append(1, SubLoop(pLeft, DataLen, pRight, RSize - 1));

			// pLeft
			while ('0' == *pLeft && DataLen > 0)
			{
				pLeft++;
				Idx++;
				DataLen--;
			}

			DataLen++;
			if (Idx + DataLen > LSize)
			{
				break;
			}
		}
	}

	return strRet;
}

bool BigData::IsLeftStrBig(char *pLeft, size_t LSize, char *pRight, size_t RSize)
{
	assert(NULL != pLeft && NULL != pRight);
	if (LSize > RSize ||
		LSize == RSize && strncmp(pLeft, pRight, LSize) >= 0)
	{
		return true;
	}

	return false;
}

char BigData::SubLoop(char *pLeft, size_t LSize, char *pRight, size_t RSize)
{
	assert(NULL != pLeft && NULL != pRight);

	char cRet = '0';
	while (true)
	{
		if (!IsLeftStrBig(pLeft, LSize, pRight, RSize))
		{
			break;
		}

		// 做-=
		int LDataIdx = LSize - 1;
		int RDataIdx = RSize - 1;
		while (RDataIdx >= 0 && LDataIdx >= 0)
		{
			if (pLeft[LDataIdx] < pRight[RDataIdx])
			{
				pLeft[LDataIdx - 1] -= 1;
				pLeft[LDataIdx] += 10;
			}

			pLeft[LDataIdx] = pLeft[LDataIdx] - pRight[RDataIdx] + '0';
			LDataIdx--;
			RDataIdx--;
		}

		// "990000000000000000000000000099"
		while ('0' == *pLeft && LSize > 0)
		{
			pLeft++;
			LSize--;
		}

		cRet++;
	}

	return cRet;
}

void BigData::INT64ToString()
{
	//12345
	char cSymbol = '+';
	INT64 temp = m_llValue;
	if (temp < 0)
	{
		cSymbol = '-';
		temp = 0 - temp;
	}


	m_strData.append(1, cSymbol);
	int iCount = 1;
	// 54321
	while (temp)
	{
		m_strData.append(1, temp % 10 + '0');
		temp /= 10;
	}

	char *pLeft = (char*)(m_strData.c_str() + 1);
	char *pRight = (char*)(m_strData.c_str() + m_strData.size() - 1);
	while (pLeft < pRight)
	{
		char ctemp = *pLeft;
		*pLeft++ = *pRight;
		*pRight-- = ctemp;
	}

	// 1 符号位
	// 2 m_strData = 54321
}

bool BigData::IsINT64Owerflow()const
{
	string strTemp;
	if ('+' == m_strData[0])
	{
		strTemp = "+9223372036854775807";
	}
	else
	{
		strTemp = "-9223372036854775808";
	}

	if (m_strData.size() > strTemp.size())
	{
		return true;
	}
	else if (m_strData.size() == strTemp.size() && m_strData > strTemp)
	{
		return true;
	}

	return false;
}

ostream& operator<<(std::ostream& _cout, const BigData& bigData)
{
	if (!bigData.IsINT64Owerflow()) // 没有溢出
	{
		_cout << bigData.m_llValue;
	}
	else
	{
		char* pData = (char*)bigData.m_strData.c_str();
		if (pData[0] == '+')
		{
			pData++;
		}
		_cout << pData;
	}
	return _cout;
}