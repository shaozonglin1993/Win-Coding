
#pragma once 
#include <iostream>
#include <assert.h>
using namespace std;

enum Type
{
	HEAD,
	VALUE,
	SUB,
};

struct GeneralListNode
{
	Type _type;
	GeneralListNode* _next;

	union{
		char _value;
		GeneralListNode* _subLink;
	};

	GeneralListNode(Type type = VALUE, char value = 0)
		:_type(type)
		,_next(NULL)
	{
		if (_type == VALUE)
		{
			_value = value;
		}
		else if (_type = SUB)
		{
			_subLink = NULL;
		}
	}
};

class GeneralList
{
public:
	GeneralList()
		:_head(NULL)
	{}

	GeneralList(char* s)
		:_head(NULL)
	{
		_head = _CreateGeneralList(s);
	}

	~GeneralList()
	{
		_Destroy(_head);
	}

	GeneralList(const GeneralList& g)
	{
		_head = _Copy(g._head);
	}

	GeneralList& operator=(GeneralList g)
	{
		swap(_head, g._head);
		return *this;
	}

	size_t Size()
	{
		return _Size(_head);
	}

	void Print()
	{
		_Print(_head);
		cout << endl;
	}

	size_t Depth()
	{
		return _Depth(_head);
	}

protected:

	GeneralListNode* _Copy(GeneralListNode* head)
	{
		assert(head);
		GeneralListNode* cur = head->_next;

		GeneralListNode* newhead = new GeneralListNode(HEAD);
		GeneralListNode* newCur = newhead;

		while (cur)
		{
			if (cur->_type == VALUE)
			{
				newCur->_next = new GeneralListNode(VALUE, cur->_value);
				newCur = newCur->_next;
			}
			else if (cur->_type == SUB)
			{
				newCur->_next = new GeneralListNode(SUB);
				newCur = newCur->_next;
				newCur->_subLink = _Copy(cur->_subLink);
			}
			cur = cur->_next;
		}

		return newhead;
	}

	void _Destroy(GeneralListNode* head)
	{
		GeneralListNode* cur = head;
		while (cur)
		{
			GeneralListNode* del = cur;
			cur = cur->_next;

			if (del->_type == SUB)
			{
				_Destroy(del->_subLink);
			}
			
			delete del;
		}
	}

	void _Print(GeneralListNode* head)
	{
		GeneralListNode* cur = head;
		while (cur)
		{
			if (cur->_type == HEAD)
			{
				cout << "(";
			}
			else if (cur->_type == VALUE)
			{
				cout << cur->_value;
				if (cur->_next)
				{
					cout << ",";
				}
			}
			else
			{
				_Print(cur->_subLink);
				if (cur->_next)
				{
					cout << ",";
				}
			}
			cur = cur->_next;
		}

		cout << ")";
	}

	size_t _Depth(GeneralListNode* head)
	{
		size_t depth = 1;
		GeneralListNode* cur = head;

		while (cur)
		{
			if (cur->_type == SUB)
			{
				size_t subDepth = _Depth(cur->_subLink);
				if (subDepth + 1 > depth)
				{
					depth = subDepth + 1;
				}
			}
			cur = cur->_next;
		}
		return depth;
	}

	size_t _Size(GeneralListNode* head)
	{
		GeneralListNode* cur = head;
		size_t size = 0;
		while (cur)
		{
			if (cur->_type == VALUE)
			{
				++size;
			}
			else if (cur->_type == SUB)
			{
				size += _Size(cur->_subLink);
			}

			cur = cur->_next;
		}

		return size;
	}

	bool IsValue(char ch)
	{
		if ((ch >= '0' && ch <= '9') || (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
		{
			return true;
		}
		return false;
	}

	GeneralListNode* _CreateGeneralList(char*& s)
	{
		assert(*s == '(');
		GeneralListNode* head = new GeneralListNode(HEAD);
		++s;
		GeneralListNode* cur = head;

		while (*s)
		{
			if (*s == '(')
			{
				GeneralListNode* subNode = new GeneralListNode(SUB);
				cur->_next = subNode;
				cur = cur->_next;

				subNode->_subLink = _CreateGeneralList(s);
			}
			else if (*s == ')')
			{
				++s;
				break;
			}
			else if (IsValue(*s))
			{
				GeneralListNode* valueNode = new GeneralListNode(VALUE, *s);
				cur->_next = valueNode;
				cur = cur->_next;
				++s;
			}
			else
			{
				++s;
			}
		}
		return head;
	}

protected:
	GeneralListNode* _head;
};

void Test1()
{
	GeneralList g1("()");
	GeneralList g2("(a,b)");
	GeneralList g3("(a,b,(c,d))");
	GeneralList g4("(a,b,(c,d),(e,(f),h))");
	GeneralList g5;
	g5 = g4;
	g4.Print();
	cout << "Depth:" << g4.Depth() << endl;
	cout << "Size:" << g4.Size() << endl;

	g5.Print();
}