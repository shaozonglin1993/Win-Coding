/**************************************************************************
建立Huffmantree
**************************************************************************/

#pragma once
#include"Heap.h"


/**************************************************************************
struct HuffmanTreeNode
**************************************************************************/
template<class T>
struct HuffmanTreeNode
{
	HuffmanTreeNode(const T& x)
	:_left(NULL)
	, _right(NULL)
	, _parent(NULL)
	, _weight(x)
	{}
	HuffmanTreeNode<T>* _left;
	HuffmanTreeNode<T>* _right;
	HuffmanTreeNode<T>* _parent;
	T _weight;
};

/**************************************************************************
class HuffmanTree
**************************************************************************/
template<class T>
class HuffmanTree
{
	typedef HuffmanTreeNode<T> Node;
public:
	HuffmanTree()
		:_root(NULL)
	{}
	~HuffmanTree()
	{
		Destroy(_root);
	}
	//删除HuffmanTree
	void Destroy(HuffmanTreeNode<T> *root)
	{
		if (root == NULL)
		{
			return;
		}
		Destroy(root->_left);	//递归调用
		Destroy(root->_right);
		delete root;
		root = NULL;
	}
	HuffmanTreeNode<T>* GetTreeRoot()
	{
		return _root;
	}
public:

/************************************************************************************
函数名称：CreateTree
函数参数：const T*a			const T*类型的数组
		size_t size			a的size
		const T& invalid		非法的值-->>这里是 '\0'
返回值类型：void
函数功能：生成HuffmanTree
************************************************************************************/
	void CreatTree(const T*a, size_t size, const T& invalid)
	{
		assert(a);

		struct Compare
		{
			bool operator()(HuffmanTreeNode<T>*& l, HuffmanTreeNode<T>*& r)
			{
				return l->_weight < r->_weight;
			}
		};

		Heap<Node*, Compare> minHeap;
		for (size_t i = 0; i < size; ++i)
		{
			if (a[i] != invalid)
			{
				Node* node = new Node(a[i]);
				minHeap.Push(node);
			}
		}

		if (minHeap.Empty())
		{
			return;
		}
		//Create HuffmanTree
		while (minHeap.Size() > 1)
		{
			//minHeap.Top()永远是最小的，根据huffmanTree的原理构建HuffmanTree
			Node* left = minHeap.Top();
			minHeap.Pop();
			Node* right = minHeap.Top();
			minHeap.Pop();

			Node*parent = new Node(left->_weight + right->_weight);
			parent->_left = left;
			parent->_right = right;
			left->_parent = parent;
			right->_parent = parent;

			minHeap.Push(parent);
		}
		_root = minHeap.Top();
	}

	//Tree层次遍历
	void LevelOrder()
	{
		queue<HuffmanTreeNode<T>* > q;
		if (_root)
		{
			q.push(_root);
		}
		while (!q.empty())
		{
			HuffmanTreeNode<T>* node = q.front();
			q.pop();
			cout << node->_weight << "	";

			if (node->_left)
			{
				q.push(node->_left);
			}

			if (node->_right)
			{
				q.push(node->_right);
			}
		}

		cout << endl;
	}

protected:
	HuffmanTreeNode<T>* _root;
};