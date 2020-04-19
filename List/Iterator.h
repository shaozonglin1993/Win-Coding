#pragma once

//
// 迭代器的型别
//
struct InputIteratorTag {};
struct OutputIteratorTag {};
struct ForwardIteratorTag : public InputIteratorTag {};
struct BidirectionalIteratorTag : public ForwardIteratorTag {};
struct RandomAccessIteratorTag : public BidirectionalIteratorTag {};

template <class Category, class T, class Distance = ptrdiff_t,
class Pointer = T*, class Reference = T&>
struct Iterator
{
	typedef Category   IteratorCategory;      // 迭代器类型
	typedef T          ValueType;            // 迭代器所指对象类型
	typedef Distance   DifferenceType;        // 两个迭代器之间的距离
	typedef Pointer    Pointer;               // 迭代器所指对象类型的指针
	typedef Reference Reference;             // 迭代器所指对象类型的引用
};


//
// Traits 就像一台“特性萃取机”，榨取各个迭代器的特性（对应的型别）
//
template <class Iterator>
struct IteratorTraits
{
	typedef typename Iterator::IteratorCategory IteratorCategory;
	typedef typename Iterator::ValueType        ValueType;
	typedef typename Iterator::DifferenceType   DifferenceType;
	typedef typename Iterator::Pointer           Pointer;
	typedef typename Iterator::Reference         Reference;
};

//
// 偏特化原生指针类型
//
template <class T>
struct IteratorTraits< T*>
{
	typedef RandomAccessIteratorTag IteratorCategory;
	typedef T                           ValueType;
	typedef ptrdiff_t                   DifferenceType;
	typedef T *                         Pointer;
	typedef T &                         Reference;
};

//
// 偏特化const原生指针类型
//
template <class T>
struct IteratorTraits< const T *>
{
	typedef RandomAccessIteratorTag IteratorCategory;
	typedef T                           ValueType;
	typedef ptrdiff_t                   DifferenceType;
	typedef const T*                   Pointer;
	typedef const T&                   Reference;
};

template <class InputIterator>
inline size_t _Distance(InputIterator first, InputIterator last, ForwardIteratorTag)
{
	size_t distance = 0;
	while (first != last)
	{
		++distance;
		++first;
	}

	return distance;
}

template <class InputIterator>
inline size_t _Distance(InputIterator first, InputIterator last, BidirectionalIteratorTag)
{
	size_t distance = 0;
	while (first != last)
	{
		++distance;
		++first;
	}

	return distance;
}

template <class InputIterator>
inline size_t _Distance(InputIterator first, InputIterator last, RandomAccessIteratorTag)
{
	return last - first;
}

template <class InputIterator>
inline size_t Distance(InputIterator first, InputIterator last)
{
	return _Distance(first, last, IteratorTraits<InputIterator>::IteratorCategory());
}

template <class InputIterator>
inline void _Advance(InputIterator& i, int n, RandomAccessIteratorTag) {
	i += n;
}

template <class InputIterator>
inline void _Advance(InputIterator& i, size_t n, ForwardIteratorTag) {
	for (size_t i = 0; i < n; ++i)
	{
		++i;
	}
}

template <class InputIterator>
inline void _Advance(InputIterator& i, int n, BidirectionalIteratorTag) {
	if (n > 0)
	{
	}
	else
	{
	}
}



template <class InputIterator>
inline void Advance(InputIterator& i, size_t n) {
	_Advance(i, n, IteratorTraits<InputIterator>::IteratorCategory());
}


template <class Iterator>
class ReverseIterator
{
protected:
	Iterator _current;
public:
	typedef typename IteratorTraits<Iterator>::IteratorCategory
		IteratorCategory;
	typedef typename IteratorTraits<Iterator>::ValueType
		ValueType;
	typedef typename IteratorTraits<Iterator>::DifferenceType
		DifferenceType;
	typedef typename IteratorTraits<Iterator>::Pointer
		Pointer;
	typedef typename IteratorTraits<Iterator>::Reference
		Reference;

	typedef Iterator IteratorType;
	typedef ReverseIterator<Iterator> Self;

public:
	ReverseIterator() {}
	explicit ReverseIterator(IteratorType x) : _current(x) {}

	// ?
	Reference operator*() const {
		Iterator tmp = _current;
		return *--tmp;
	}

	Pointer operator->() const { return &(operator*()); }

	Self& operator++() {
		--_current;
		return *this;
	}
	Self operator++(int) {
		Self tmp = *this;
		--_current;
		return tmp;
	}
	Self& operator--() {
		++_current;
		return *this;
	}
	Self operator--(int) {
		Self tmp = *this;
		++_current;
		return tmp;
	}

	bool operator != (Self& s)
	{
		return _current != s._current;
	}

	bool operator == (Self& s)
	{
		return _current == s._current;
	}

};