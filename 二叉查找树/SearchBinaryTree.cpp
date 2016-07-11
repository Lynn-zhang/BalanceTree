#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<stack>
using namespace std;

template<class K,class V>
struct BSTNode
{
	K _key;
	V _value;
	BSTNode<K, V>* _left;
	BSTNode<K, V>* _right;

	friend ostream& operator<<<K,V>(ostream&, BSTNode<K, V>*&);
	/*template<class K, class V>
	friend ostream& operator<<(ostream&, BSTNode<K,V>*&);*/
	
	BSTNode(const K& key,const V& value=1)
		:_key(key), _value(value), _left(NULL),_right(NULL)
	{}
};

template<class K, class V>
class BSTree
{
public:
	BSTree()
	:_root(NULL)
	{}
	//插入新节点（非递归）
	bool Insert(const K& key, const V& value);
	//插入新节点（递归）
	bool Insert_R(const K& key, const V& value)
	{
		return _Insert_R(_root, key, value);
	}
	//非递归查找
	BSTNode<K, V>* Find(const K& key);
	//递归查找
	BSTNode<K, V>* Find_R(const K& key)
	{
		return _Find_R(_root, key);
	}
	//非递归删除
	bool Remove(const K& key);
	//递归删除
	bool Remove_R(const K& key)
	{
		return _Remove_R(_root, key);
	}
	//打印
	void NonR_InOrderPrintTree();
	
protected:
	bool _Insert_R(BSTNode<K, V>*& root, const K& key, const V& value);
	BSTNode<K, V>* _Find_R(BSTNode<K, V>*& root, const K& key);
	bool _Remove_R(BSTNode<K, V>*& root, const K& key);
protected:
	BSTNode<K, V>* _root;
};

template<class K, class V>
bool BSTree<K, V>::Insert(const K& key, const V& value)
{
	if (_root == NULL)
	{
		_root = new BSTNode<K, V>(key);
		return true;
	}
	BSTNode<K, V>* cur = _root;
	BSTNode<K, V>* parent = _root;
	while (cur)
	{
		if (cur->_key < key)
		{
			parent = cur;
			cur = cur->_right;		
		}
		else if (cur->_key>key)
		{
				parent = cur;
				cur = cur->_left;
		}
		else
			return false;
	}
	if (key > parent->_key)
		parent->_right = new BSTNode<K, V>(key);
	else
		parent->_left = new BSTNode<K, V>(key);
	return true;
}
template<class K, class V>
bool BSTree<K, V>::_Insert_R(BSTNode<K, V>*& root, const K& key, const V& value)
{
	if (root == NULL)
	{
		root = new BSTNode<K, V>(key);
		return true;
	}
	else if (root->_key<key)
	{
		return _Insert_R(root->_right, key, value);
	}
	else if (root->_key>key)
	{
		return _Insert_R(root->_left, key, value);
	}
	else
	{
		return false;
	}
}
template<class K, class V>
BSTNode<K, V>* BSTree<K, V>::Find(const K& key)
{
	if (_root == NULL)
		return NULL;
	BSTNode<K, V>* cur = _root;
	while (cur)
	{
		if (cur->_key == key)
			return cur;
		else if (cur->_key > key)
			cur = cur->_left;
		else
			cur = cur->_right;
	}
	return NULL;
}
template<class K, class V>
BSTNode<K, V>*  BSTree<K, V>::_Find_R(BSTNode<K, V>*& root, const K& key)
{
	if (_root == NULL)
		return NULL;
	BSTNode<K, V>* cur = root;

	if (root->_key == key)
		return root;
	else if (root->_key > key)
		return _Find_R(root->_left, key);
	else
		return _Find_R(root->_right, key);
}
template<class K, class V>
bool BSTree<K, V>::Remove(const K& key)
{
	// 1.空树 根节点为空
	// 2.只有根节点
	// 3.该节点有子树
		// a.该节点无左子树 (或左右子树都没有)
		// b.该节点无右子树
		// c.该节点有左右子树
	if (_root == NULL)
		return false;
	if (_root->_left == NULL&&_root->_right == NULL)
	{
		if (_root->_key == key)
		{
			delete _root;
			_root = NULL;
			return true;
		}
		else
			return false;
	}
	BSTNode<K, V>* cur = _root;
	BSTNode<K, V>* parent =NULL;
	BSTNode<K, V>* del = NULL;
	while (cur)
	{
		if (cur->_key < key)
		{
			parent = cur;
			cur = cur->_right;
		}
		else if (cur->_key>key)
		{
			parent = cur;
			cur = cur->_left;
		}
		else
		{ // 找到该节点，根据情况删除
			del = cur;
			// 1.要删除的节点无左子树
			if (cur->_left == NULL)
			{
				// a.要删除的节点没有左子树，但有右子树
				if (cur->_right != NULL)
				{   //    \   <
					if (parent->_left == cur)parent->_left = cur->_right;
					else if (parent->_right == cur)parent->_right = cur->_right;
				}
				else
				{// b.要删除的节点既无做子树也无右子树
					if (parent->_left == cur)parent->_left = NULL;
					else if (parent->_right = cur)parent->_right = NULL;
				}
			}
			// 2.要删除的节点右子树为空，但有左子树
			else if (cur->_right == NULL)
			{ //        /   >
				if (parent->_left = cur)parent->_left = cur->_left;
				else if (parent->_right = cur)parent->_right = cur->_left;
			}
			// 3.要删除的节点既有左子树又有右子树
			else if (cur->_left && cur->_right)
			{
				BSTNode<K, V>* firstleft = cur->_right;
				// 找右子树中的最小节点,找到后和要删除的节点交换
				while (firstleft->_left)
				{
					parent = firstleft;
					firstleft = firstleft->_left;
				}
				del = firstleft;
				swap(cur->_key, firstleft->_key);
				swap(cur->_value, firstleft->_value);
				// 分两种情况处理
				
				// 1.要删除节点的右子树的左子树非空，最小节点经过循环寻找寻得
				if (parent->_left == firstleft)
				{
					parent->_left = firstleft->_right;
				}
				// 2.要删除节点的右子树无左孩子节点，即最小节点是要删除节点的右孩子
				else if ( cur->_right == firstleft)
				{
					cur->_right = firstleft->_right;
				}
			}
			delete del;
			return true;
		}		
	}
	return false;
}
template<class K, class V>
bool BSTree<K, V>::_Remove_R(BSTNode<K, V>*& root, const K& key)
{
	//未找到
	if (root == NULL)
		return false;
	//叶子节点
	if (root->_left == NULL&&root->_right == NULL)
	{
		if (root->_key == key)
		{
			delete root;
			root = NULL;
			return true;
		}
		else
			return false;		
	}
	//开始寻找
	if (root->_key > key)
	{
		return _Remove_R(root->_left, key);
	}
	else if (root->_key < key)
	{
		return _Remove_R(root->_right, key);
	}
	else
	{ //找到节点
		if (root->_left == NULL)
		{//左子树为空，将右子树连接到根节点
			root = root->_right;
		}
		else if (root->_right == NULL)
		{//右子树为空，将左子树链接到根节点
			root= root->_left ;
		}
		else
		{//左右子树都不为NULL
			BSTNode<K, V>* firstleft = root->_right;
			BSTNode<K, V>* parent = root;
			//从右子树中找最小节点firstleft，找到后将该节点属性与要删除节点属性交换
			while (firstleft->_left)
			{
				parent = firstleft;
				firstleft = firstleft->_left;
			}
			swap(firstleft->_key, root->_key);
			swap(firstleft->_value, root->_value);
			//分两种情况
			if (parent->_left == firstleft)
			{//firstleft为要删除节点的左子树中的节点
				parent->_left = firstleft->_right;
			}
			else if (root->_right == firstleft)
			{//最小节点为要删除节点右子树的根节点
				root->_right = firstleft->_right;
			}
			delete firstleft;
			return true;
		}
	}
}
template<class K, class V>
void BSTree<K, V>::NonR_InOrderPrintTree()
{
	if (_root == NULL)
		return;
	stack<BSTNode<K, V>*> sc;
	BSTNode<K, V>* cur = _root;
	while (cur || !sc.empty())
	{
		while (cur)
		{
			sc.push(cur);
			cur = cur->_left;
		}
		if (!sc.empty())
		{
			cur = sc.top();
			cout << cur->_key << " ";
			sc.pop();
			cur = cur->_right;
		}
	}
	cout << endl;
}
template<class K, class V>
ostream& operator<<(ostream& out, BSTNode<K,V>*& bst)
{
	if (bst)
	{
		out << "BSTNode->key: "<<bst->_key;
	}
	return out;
}

void Test()
{
	BSTree<int,int> bst;
	bst.Insert(5, 1);
	bst.Insert(3, 1);
	bst.Insert(4, 1);
	bst.Insert(1, 1);
	bst.Insert(7, 1);
	bst.Insert(8, 1);
	bst.Insert(2, 1);
	bst.Insert(6, 1);
	bst.Insert(0, 1);
    bst.Insert(9, 1);
	bst.NonR_InOrderPrintTree();

	bst.Remove_R(7);
	bst.NonR_InOrderPrintTree();
	bst.Remove_R(0);
	bst.NonR_InOrderPrintTree();
	bst.Remove_R(9);
	bst.NonR_InOrderPrintTree();
	bst.Remove_R(1);
	bst.NonR_InOrderPrintTree();
	bst.Remove_R(5);
	bst.NonR_InOrderPrintTree();
	bst.Remove_R(4);
	bst.NonR_InOrderPrintTree();
	bst.Remove_R(2);
	bst.NonR_InOrderPrintTree();
	bst.Remove_R(3);
	bst.NonR_InOrderPrintTree();
	bst.Remove_R(8);
	bst.NonR_InOrderPrintTree();
	bst.Remove_R(6);
	bst.NonR_InOrderPrintTree();

	//bst.Remove(7);
	//bst.NonR_InOrderPrintTree();
	//bst.Remove(0);
	//bst.NonR_InOrderPrintTree();
	//bst.Remove(9);
	//bst.NonR_InOrderPrintTree();
	//bst.Remove(1);
	//bst.NonR_InOrderPrintTree();
	//bst.Remove(5);
	//bst.NonR_InOrderPrintTree();
	//bst.Remove(4);
	//bst.NonR_InOrderPrintTree();
	//bst.Remove(2);
	//bst.NonR_InOrderPrintTree();
	//bst.Remove(3);
	//bst.NonR_InOrderPrintTree();
	//bst.Remove(8);
	//bst.NonR_InOrderPrintTree();
	//bst.Remove(6);
	//bst.NonR_InOrderPrintTree();
	/*BSTNode<int, int>* ret1 = bst.Find(7);
	cout << ret1 << endl;*/
	//BSTNode<int, int>* ret2 = bst.Find_R(7);
	//cout <<ret2<< endl;
	//bst.Insert_R(5,1);
	//bst.Insert_R(3,1);
	//bst.Insert_R(4,1);
	//bst.Insert_R(1,1);
	//bst.Insert_R(7,1);
	//bst.Insert_R(8,1);
	//bst.Insert_R(2, 1);
	//bst.Insert_R(6, 1);
	//bst.Insert_R(0, 1);
	//bst.Insert_R(9, 1);
}
int main()
{
	Test();
	system("pause");
	return 0;
}