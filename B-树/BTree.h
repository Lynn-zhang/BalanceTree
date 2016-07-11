#pragma once

template<class K,int M=3>
struct BTreeNode
{
	K _key[M];	//关键字 (有效关键字个数为M-1)
	BTreeNode<K, M>* _sub[M + 1];	//链接子树的指针数组
	size_t _size;		//节点中关键字的个数
	BTreeNode<K, M>* _parent;	//指向父节点的指针

	BTreeNode()
		:_size(0)
		, _parent(NULL)
	{
		for (size_t i = 0; i < M + 1; i++)
		{
			_sub[i] = NULL;
		}
	}
};

template<class K,class V>
struct Pair
{
	K _first;
	V _second;
	
	Pair(const K &k = K(), const V& v = V())
		:_first(k)
		, _second(v)
	{}
};

template<class K,int M=3>
class BTree
{
public:
	BTree()
		:_root(NULL)
	{}
	//递归查找key
	Pair<BTreeNode<K, M>*, int> Find(const K& key)
	{
		BTreeNode<K, M>* parent=NULL;
		BTreeNode<K, M>* cur=_root;
		//遍历关键字数组_key[]，如果key比它小就 ++i 并继续往后遍历
		// 1.如果key=_key[i]则停止遍历，返回该结构体节点
		// 2.如果key比它大则停止遍历，此时的子树_sub[i]指向的关键字数组的所有数据都是介于_key[i-1]和_key[i]之间的数据，我们要找的key或许就在其中
		// 3.如果跳出循环则未找到该数据cur=NULL，返回cur的父节点；这时候若是插入key，就插入到parent指向的关键字数组中
		while (cur!=NULL)
		{
			size_t i = 0;
			while (i < cur->_size&&cur->_key[i] < key)
				++i;
			if (cur->_key[i] == key)
				return Pair<BTreeNode<K, M>*, int>(cur, i);	
			// key<_key[i] 则走向与key[i]下标相同的子树
			parent = cur;
			cur = cur->_sub[i];
		}
		return Pair<BTreeNode<K, M>*, int>(parent, -1);
	}
	//插入数据
	bool Insert(K& key)
	{
		// 1.B-树为空
		if (NULL == _root)
		{
			_root = new BTreeNode<K, M>;
			_root->_key[0] = key;
			++_root->_size;
			return true;
		}

		Pair<BTreeNode<K, M>*, int> ret = Find(key);
		// 2.该数据已经存在
		if (ret._second != -1)	
			return false;

		// 3.插入数据到关键字数组
		BTreeNode<K, M>* cur = ret._first;
		BTreeNode<K, M>* sub = NULL;
		while (1)
		{
			int i = 0;
			for ( i = cur->_size - 1; i >= 0; )
			{ // 把大数往后挪，对应子树也要进行挪动
				if (cur->_key[i] > key)
				{
					cur->_key[i + 1] = cur->_key[i];
					cur->_sub[i + 2] = cur->_sub[i + 1]; 
					i--;
				}
				else
				{
					break;
				}
			}
			cur->_key[i + 1] = key;
			cur->_sub[i + 2] = sub;
			if (sub!=NULL)
				cur->_sub[i+2]->_parent = cur;
			cur->_size++;

			//关键字数组未满，插入成功
			if (cur->_size < M)
				return true;

			//关键字数组已满，需要进行分裂
			int mid = M / 2;
			//分裂
			BTreeNode<K, M>* tmp = new BTreeNode<K, M>;
			int index = 0;
			size_t k;
			for ( k = mid + 1; k < cur->_size; k++)
			{
				tmp->_key[index] = cur->_key[k];
				if (cur->_sub[k] != NULL)
				{
					tmp->_sub[index] = cur->_sub[k];
					cur->_sub[k] = NULL;
					tmp->_sub[index]->_parent = tmp;
				}
				tmp->_size++;
				cur->_size--;
				index++;
			}
			if (cur->_sub[k] != NULL)
			{
				tmp->_sub[index] = cur->_sub[k];
				cur->_sub[k] = NULL;
				tmp->_sub[index]->_parent = tmp;
			}
			//父节点为空时的链接
			if (cur->_parent == NULL)
			{
				_root = new BTreeNode<K, M>;
				_root->_key[0] = cur->_key[mid];
				cur->_size--;
				_root->_sub[0] = cur;
				_root->_sub[1] = tmp;
				_root->_size++;
				
				//链接
				tmp->_parent = _root;
				cur->_parent = _root;
				return true;
			}
			//父节点不为空时的链接
			key = cur->_key[mid];
			cur->_size--;
			cur = cur->_parent;
			sub = tmp;
		}
	}

	void InOrder()
	{
		_InOrder(_root);
	}
	protected:
		void _InOrder(BTreeNode<K, M>* root)
		{
			if (root == NULL)
				return;
			size_t i = 0;
			for (; i < root->_size; i++)
			{
				_InOrder(root->_sub[i]);
				cout << root->_key[i]<<" ";
			}
				_InOrder(root->_sub[i]);
		}

protected:
	BTreeNode<K, M>* _root;
};



//#include<iostream>  
//using namespace std;
//
//template<class K, int M = 3>
//struct BTreeNode
//{
//	K _keys[M];
//	BTreeNode<K, M>* _subs[M + 1];
//	size_t _size;
//	BTreeNode<K, M>* _parent;
//
//	BTreeNode()
//		:_size(0)
//		, _parent(NULL)
//	{
//		for (size_t i = 0; i < M + 1; ++i)
//		{
//			_subs[i] = NULL;
//		}
//	}
//};
//
//template<class K, class V>
//struct Pair
//{
//	K _first;
//	V _second;
//
//	Pair(const K& k = K(), const V& v = V())
//		:_first(k)
//		, _second(v)
//	{}
//};
//
//template<class K, int M = 3>
//class BTree
//{
//	typedef BTreeNode<K, M> Node;
//public:
//	BTree()
//		:_root(NULL)
//	{}
//
//	Pair<Node*, int> Find(const K& key)
//	{
//		Node* parent = NULL;
//		Node* cur = _root;
//		while (cur)
//		{
//			int i = 0;
//			while (i < cur->_size && cur->_keys[i] < key)
//			{
//				++i;
//			}
//			if (cur->_keys[i] == key)
//			{
//				return  Pair<Node*, int>(cur, i);
//			}
//			parent = cur;
//			cur = cur->_subs[i];
//		}
//		return Pair<Node*, int>(parent, -1);
//	}
//
//	bool Insert(const K& key)
//	{
//		if (_root == NULL)
//		{
//			_root = new Node;
//			_root->_keys[0] = key;
//			++_root->_size;
//			return true;
//		}
//
//		Pair<Node*, int> ret = Find(key);
//		if (ret._second != -1)
//		{
//			return false;
//		}
//		K k = key;
//		Node *cur = ret._first;
//		Node *sub = NULL;
//		while (1)
//		{
//			_InsertKey(cur, k, sub);
//			if (cur->_size < M)
//			{
//				return true;
//			}
//
//			int boundary = M / 2;
//			Node *tmp = new Node;
//			size_t index = 0;
//			size_t size = cur->_size;
//
//			for (int i = boundary + 1; i < size; ++i)
//			{
//				tmp->_keys[index++] = cur->_keys[i];
//				tmp->_size++;
//				cur->_size--;
//			}
//
//			index = 0;
//			for (int i = boundary + 1; i <= size; ++i)
//			{
//				tmp->_subs[index] = cur->_subs[i];
//				if (tmp->_subs[index])
//				{
//					tmp->_subs[index]->_parent = tmp;
//				}
//				++index;
//			}
//
//			k = cur->_keys[boundary];
//			cur->_size--;
//
//			if (cur->_parent == NULL)
//			{
//				_root = new Node;
//				_root->_keys[0] = k;
//				_root->_subs[0] = cur;
//				_root->_subs[1] = tmp;
//				_root->_size = 1;
//
//				tmp->_parent = _root;
//				cur->_parent = _root;
//
//				return true;
//			}
//
//			cur = cur->_parent;
//			sub = tmp;
//
//		}
//	}
//
//	void InOrder()
//	{
//		_InOrder(_root);
//		cout << endl;
//	}
//
//protected:
//
//	void _InsertKey(Node* cur, const K& k, Node* sub)
//	{
//		int i = cur->_size - 1;
//		while (i >= 0)
//		{
//			if (cur->_keys[i] > k)
//			{
//				cur->_keys[i + 1] = cur->_keys[i];
//				cur->_subs[i + 2] = cur->_subs[i + 1];
//				--i;
//			}
//			else
//			{
//				break;
//			}
//		}
//		cur->_keys[i + 1] = k;
//		cur->_subs[i + 2] = sub;
//		if (sub != NULL)
//		{
//			sub->_parent = cur;
//		}
//		cur->_size++;
//	}
//
//	void _InOrder(Node* root)
//	{
//		if (root == NULL)
//		{
//			return;
//		}
//		for (size_t i = 0; i < root->_size; ++i)
//		{
//			_InOrder(root->_subs[i]);
//			cout << root->_keys[i] << " ";
//		}
//		_InOrder(root->_subs[root->_size]);
//	}
//
//private:
//	Node* _root;
//};
//
