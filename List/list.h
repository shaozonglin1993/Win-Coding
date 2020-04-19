#pragma once
#include"Iterator.h"

template<class T>
struct _ListNode
{
	_ListNode<T>* _prev;
	_ListNode<T>* _next;
	T _data;

	_ListNode()
		:_prev(NULL)
		, _next(NULL)
	{}

	_ListNode(const T& x)
		:_data(x)
		, _next(NULL)
		, _prev(NULL)
	{}
};


template<class T, class Ref, class Ptr>
struct _ListIterator
{
	typedef _ListNode<T> Node;
	typedef Node* LinkType;
	typedef _ListIterator<T, Ref, Ptr> Self;

	typedef T ValueType;
	typedef Ref Reference;
	typedef Ptr Pointer;
	typedef BidirectionalIteratorTag IteratorCategory;
	typedef ptrdiff_t DifferenceType;

	LinkType _node;





protected:
	LinkType _head;
};