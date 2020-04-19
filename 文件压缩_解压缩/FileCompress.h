/**************************2016-8-22*******************************************
项目名称：文件压缩与解压缩
项目简介：利用Huffman编码实现
实现过程：
		利用最小堆来建立哈夫曼树；
		生成哈弗曼编码并存入结点；
		将字符总数、哈夫曼编码写入压缩文件；
		将哈夫曼树信息写入配置文件方便解压缩时建树；
		利用配置文件建树；
		利用压缩文件读字符；
		写入解压缩文件。
******************************************************************************/
#pragma once

#include "HuffmanTree.h"
#include <string>
#include <queue>
#include <algorithm>

#define _DEBUG_

typedef long  longType;

/******************************************************************************
struct CharInfo
*******************************************************************************/
struct CharInfo
{
	unsigned char _ch;
	longType _Count;
	string _code;

	CharInfo(longType Count = 0)
		:_Count(Count)
		, _ch(0)
	{}
/******************************************************************************
重载函数：
CharInfo operator+(const CharInfo& info)
bool operator < (const CharInfo& info) const
bool operator !=(const CharInfo& info) const
*******************************************************************************/
	CharInfo operator+(const CharInfo& info)
	{
		return CharInfo(_Count + info._Count);
	}
	bool operator < (const CharInfo& info) const
	{
		return _Count < info._Count;
	}
	bool operator !=(const CharInfo& info) const
	{
		return info._Count != _Count;
	}
};


ostream& operator<<(ostream& os, const CharInfo& info)
{
	os << info._ch << ":" << info._Count;

	return os;
}


/******************************************************************************
template<class T>
class FileCompress
*******************************************************************************/
template<class T>
class FileCompress
{
public:
	//将字符编码写入_infos[]
	FileCompress()
	{
		for (size_t i = 0; i < 256; ++i)
		{
			_infos[i]._ch = i;
		}
	}
public:

/*******************************************************************************
函数名称：_GenerateHuffmanCode
函数参数：HuffmanTreeNode<CharInfo>* root	Huffmantree的根节点
返 回 值：void
函数功能：生成Huffman编码
*******************************************************************************/
	void _GenerateHuffmanCode(HuffmanTreeNode<CharInfo>* root)
	{
		if (root == NULL)
		{
			return;
		}
		//递归找叶子节点
		_GenerateHuffmanCode(root->_left);
		_GenerateHuffmanCode(root->_right);

		if (root->_left == NULL && root->_right == NULL)//是叶子才编码
		{
			HuffmanTreeNode<CharInfo>* cur = root;
			HuffmanTreeNode<CharInfo>* parent = cur->_parent;
			string &code = _infos[cur->_weight._ch]._code;
			while (parent)
			{
				if (parent->_left == cur)
				{
					code += '0';
				}
				else
				{
					code += '1';
				}
				cur = parent;
				parent = cur->_parent;
			}
			//从叶子到根部找的，所以要逆置. 
			reverse(code.begin(), code.end());
		}
	}
	
/*******************************************************************************
函数名称：GetHuffmanCode
函数参数：HuffmanTreeNode<CharInfo> *root	Huffmantree的根节点
返 回 值：void
函数功能：获取Huffman编码 
*******************************************************************************/
	void GetHuffmanCode(HuffmanTreeNode<CharInfo> *root)
	{
		queue<HuffmanTreeNode<CharInfo>* > q;
		if (root)
		{
			q.push(root);
		}

		while (!q.empty())
		{
			HuffmanTreeNode<CharInfo>* node = q.front();
			if (node->_left == NULL && node->_right == NULL)//是叶子才打印
			{
				//cout << node->_weight << " ";
			}
			if (node->_left)
			{
				q.push(node->_left);
			}
			if (node->_right)
			{
				q.push(node->_right);
			}
			q.pop();
		}

		cout << endl;
	}

/*******************************************************************************
函数名称：Compress
函数参数：const char*filename		char* 类型的文件名称
返 回 值：bool
函数功能：实现文件压缩
*******************************************************************************/
	bool Compress(const char*filename)
	{
		assert(filename);

		long long charCount = 0;
		//打开文件。统计字符出现的字数
		FILE* fOut = fopen(filename, "rb");
		assert(fOut);

		char ch = fgetc(fOut);
		while (ch != EOF)
		{
			_infos[(unsigned char)ch]._Count++;
			ch = fgetc(fOut);
			charCount++;
		}

		//构建哈夫曼树,生成对应的哈夫曼编码
		HuffmanTree<CharInfo> t;
		CharInfo invalid = CharInfo();
		t.CreatTree(_infos, 256, invalid);

		_GenerateHuffmanCode(t.GetTreeRoot());
#ifdef _DEBUG_
		GetHuffmanCode(t.GetTreeRoot());
#endif
		cout << endl;

		//创建压缩文件
		string CompressFile = filename;
		CompressFile += ".huffman";
		FILE *finCompress = fopen(CompressFile.c_str(), "wb");
		assert(finCompress);

		//将哈夫曼码写入压缩文件

		/*重定位流(数据流/文件)上的文件内部位置指针
		int fseek(FILE *stream, long offset, int fromwhere);函数设置文件指针stream的位置*/
		fseek(fOut, 0, SEEK_SET);
		ch = fgetc(fOut);
		char inch = 0;
		int index = 0;
		while (ch != EOF)	
		{
			string& code = _infos[(unsigned char)ch]._code;
#ifdef _DEBUG_
			//cout << code << "->";
#endif
			for (size_t i = 0; i < code.size(); ++i)
			{
				++index;
				inch <<= 1;
				if (code[i] == '1')
				{
					inch |= 1;
				}
				//一个字符一个字节
				if (index == 8)
				{
					fputc(inch, finCompress);
					index = 0;
					inch = 0;
				}
			}
			ch = fgetc(fOut);
		}
		if (index != 0)
		{
			inch <<= (8 - index);
			fputc(inch, finCompress);
		}
		//创建配置文件，保存树的信息
		string configFileName = filename;
		configFileName += ".config";
		FILE* fInConfig = fopen(configFileName.c_str(), "wb");
		assert(fInConfig);

		//写入字符总数,先写高位，再写低位
		char CountStr[100];
		itoa(charCount >> 32, CountStr, 10);
		fputs(CountStr, fInConfig);
		fputc('\n', fInConfig);

		itoa(charCount & 0xFFFFFFFF, CountStr, 10);
		fputs(CountStr, fInConfig);
		fputc('\n', fInConfig);

		string infoStr;
		for (int i = 0; i < 256; ++i)
		{
			if (_infos[i] != invalid)
			{
				infoStr += _infos[i]._ch;
				infoStr += ',';
				itoa(_infos[i]._Count, CountStr, 10);
				infoStr += CountStr;
				infoStr += '\n';
				fputs(infoStr.c_str(), fInConfig);

				infoStr.clear();
			}
		}

		fclose(finCompress);
		fclose(fOut);
		fclose(fInConfig);
		return true;
	}
	
/*******************************************************************************
函数名称：ReadLine
函数参数：FILE* fOut		文件指针
		 string& line	
返 回 值：bool
函数功能：读一行
*******************************************************************************/
	bool ReadLine(FILE* fOut, string& line)
	{
		char ch = fgetc(fOut);
		if (ch == EOF)
		{
			return false;
		}
		while (ch != EOF && ch != '\n')
		{
			line += ch;
			ch = fgetc(fOut);
		}
		return true;
	}

/*******************************************************************************
函数名称：UnCompress
函数参数：const char*filename	char* 类型的文件名称
返 回 值：bool
函数功能：实现文件解压缩
*******************************************************************************/
	bool UnCompress(const char*filename)
	{
		assert(filename);
		//打开配置文件,建树
		string configFileName = filename;
		configFileName += ".config";
		FILE* fOutConfig = fopen(configFileName.c_str(), "rb");
		assert(fOutConfig);

		//读文件总字符数，先读高位，再读低位
		string line;
		string CountStr;
		ReadLine(fOutConfig, line);
		CountStr += line;
		line.clear();
		ReadLine(fOutConfig, line);
		CountStr += line;
		long long Count = atoi(CountStr.c_str());
		line.clear();

		//开始读配置文件正文
		char ch = 0;
		while (ReadLine(fOutConfig, line))
		{
			if (!line.empty())
			{
				ch = line[0];
				_infos[(unsigned char)(ch)]._Count = atoi(line.substr(2).c_str());
				line.clear();
			}
			else//空行为换行符
			{
				line = '\n';
			}
		}
		//读好了_infos,开始建树

		HuffmanTree<CharInfo> t;
 		CharInfo invalid(0);
		t.CreatTree(_infos, 256, invalid);

		//建好了树，根据压缩文件里的编码开始解压缩
		string uncompressFileName = filename;
		uncompressFileName += ".Uncompress";
		FILE* fOut = fopen(uncompressFileName.c_str(), "wb");

		string compressFileName = filename;
		compressFileName += ".huffman";
		FILE* fIn = fopen(compressFileName.c_str(), "rb");

		ch = fgetc(fIn);
		int pos = 8;
		HuffmanTreeNode<CharInfo>* root = t.GetTreeRoot();
		HuffmanTreeNode<CharInfo>* cur = root;
		while (1)
		{
			if (cur->_left == NULL && cur->_right == NULL)
			{
				fputc(cur->_weight._ch, fOut);
				cur = root;
				if (--Count == 0)
					break;
			}
			--pos;
			if (ch & (1 << pos))
				cur = cur->_right;
			else
				cur = cur->_left;
			if (pos == 0)
			{
				ch = fgetc(fIn);
				pos = 8;
			}
		}

		fclose(fOutConfig);
		fclose(fOut);
		fclose(fIn);
		return true;
	}
protected:
	CharInfo _infos[256];
};