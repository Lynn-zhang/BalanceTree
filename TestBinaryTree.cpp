#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<assert.h>
#include<queue>
#include<stack>
using namespace std;

//定义二叉树节点
template<class T>
struct BinaryTreeNode
{
	T _data;
	BinaryTreeNode<T>* _left;
	BinaryTreeNode<T>* _right;


	BinaryTreeNode(int data = 0)
		:_data(data)
		, _left(NULL)
		, _right(NULL)
	{}
};

//************定义二叉树及二叉树的基本操作*********************//
template<class T>
class BinaryTree
{
	typedef BinaryTreeNode<T> Node;
public:
	BinaryTree();
	BinaryTree(const T* a, size_t size, const T& invalid);
	BinaryTree(const BinaryTree<T>& t);
	BinaryTree<T> operator=(BinaryTree<T> t);
	//BinaryTree<T> operator=(const BinaryTree<T> &t);
	~BinaryTree();

	//基本操作
	void PrevOrder();  //前序遍历
	void InOrder();      //中序遍历
	void PostOrder();  //后序遍历
	void LevelOrder();  //层序遍历

	// 非递归遍历 non-recursive
	void NonR_PrevOrder();  //前序遍历
	void NonR_InOrder();      //中序遍历
	void NonR_PostOrder();  //后序遍历
	void NonR_LevelOrder();  //层序遍历

	size_t Size();           //二叉树节点个数
	size_t Depth();       //二叉树的深度
	size_t LeafSize();   //叶子节点数

	Node* Find(const T key)
	{
		return _Find(_root, key);
	}
	Node* _Find(Node* root, const T key)
	{
		if (root == NULL)
			return NULL;
		if (root->_data == key)
			return root;
		Node*left = _Find(root->_left, key);
		if (left != NULL)
			return left;
		Node* right = _Find(root->_right, key);
		if (right != NULL)
			return right;
		return NULL;
	}
	void  FindLowestCommonAncestor(Node* node1, Node* node2);
	int _FindLCA(Node* root, Node* node1, Node* node2, Node*& ancestor);
	
protected:
	void  _CreatBinaryTree(Node *& root, const T*& a, size_t &size, const T& invalid); //建二叉树
	void _PrevOrder(Node *root);  //前序遍历
	void _InOrder(Node *root);      //中序遍历
	void _PostOrder(Node *root);  //后序遍历
	void _LevelOrder(Node *root);  //层序遍历
	size_t _Size(Node* root, size_t &count);
	size_t _Depth(Node* root);
	size_t _LeafSize(Node* root, size_t &count);
	Node* _Copy(Node* root);
	void Destory(Node*& root);


protected:
	Node* _root;
};
//*******************************************************************//

//定义无参构造函数
template<class T>
BinaryTree<T>::BinaryTree()
:_root(NULL)
{}

//定义有参数的构造函数
template<class T>
BinaryTree<T>::BinaryTree(const T*a, size_t size, const T& invalid)
{
	assert(a);
	_CreatBinaryTree(_root, a, size, invalid);
}

//定义拷贝构造函数
template<class T>
BinaryTree<T>::BinaryTree(const BinaryTree<T>& t)
{
	_root = _Copy(t._root);
}
template<class T>
BinaryTreeNode<T>* BinaryTree<T>::_Copy(Node* root)
{
	if (root == NULL)
	{
		return NULL;
	}
	Node* root_ = new Node(root->_data);
	root_->_left = _Copy(root->_left);
	root_->_right = _Copy(root->_right);
	return root_;
}

//定义赋值运算符重载
template<class T>
BinaryTree<T> BinaryTree<T>::operator=(BinaryTree<T> t)
{
	swap(_root, t._root);
	return *this;
}
//template<class T>
//BinaryTree<T> BinaryTree<T>::operator=(const BinaryTree<T>& t)
//{
//	if (this != &t)
//	{
//		if (_root != NULL)
//		{
//			this->Destory(_root);
//		}
//		_root=_Copy(t._root);
//	}
//	return *this;
//}

//析构
template<class T>
BinaryTree<T>::~BinaryTree()
{
	Destory(_root);
}
template<class T>
void BinaryTree<T>::Destory(Node*&root)
{
	if (root == NULL)
		return;

	if (root->_left == NULL&&root->_right == NULL)
	{
		delete root;
		root = NULL;
	}
	else
	{
		Destory(root->_left);
		Destory(root->_right);
		delete root;
		root = NULL;
	}
}

//建二叉树
template<class T>
void  BinaryTree<T>::_CreatBinaryTree(Node*& root, const T*& a, size_t& size, const T& invalid)
{
	if (size <1 || *a == invalid)
	{
		return;
	}
	root = new Node(*a);
	_CreatBinaryTree(root->_left, ++a, --size, invalid);
	if (size <1)
	{
		return;
	}
	_CreatBinaryTree(root->_right, ++a, --size, invalid);
}

//前序遍历
template<class T>
void  BinaryTree<T>::PrevOrder()
{
	cout << "前序：";
	_PrevOrder(_root);
	cout << endl;
}
template<class T>
void  BinaryTree<T>::_PrevOrder(Node *root)
{
	if (root)
	{
		cout << root->_data << " ";
		_PrevOrder(root->_left);
		_PrevOrder(root->_right);
	}
}
template<class T>
void BinaryTree<T>::NonR_PrevOrder()   // 非递归前序遍历
{
	if (_root == NULL)
	{
		return;
	}
	stack<Node*> sc;
	sc.push(_root);
	while (!sc.empty())
	{
		Node* ret = sc.top();
		cout << ret->_data << " ";
		sc.pop();
		if (ret->_right)
		{
			sc.push(ret->_right);
		}
		if (ret->_left)
		{
			sc.push(ret->_left);
		}
	}
	cout << endl;
}

//中序遍历
template<class T>
void BinaryTree<T>::InOrder()
{
	cout << "中序：";
	_InOrder(_root);
	cout << endl;
}
template<class T>
void BinaryTree<T>::_InOrder(Node *root)
{
	if (root)
	{
		_InOrder(root->_left);
		cout << root->_data << " ";
		_InOrder(root->_right);
	}

}
template<class T>
void BinaryTree<T>::NonR_InOrder()   // 非递归中序遍历
{
	if (_root == NULL)
	{
		return;
	}
	stack<Node*> sc;
	Node* cur = _root;
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
			cout << cur->_data << " ";
			sc.pop();
			cur = cur->_right;
		}
	}

	//// 不好，会漏掉节点没有左孩子但有右孩子的情况
	//sc.push(_root);
	//while (!sc.empty())
	//{
	//	Node* ret = sc.top();
	//	while (ret->_left != NULL)
	//	{
	//		sc.push(ret->_left);
	//		ret = sc.top();
	//	}
	//	cout << sc.top()->_data << " ";
	//	sc.pop();
	//	if (!sc.empty())
	//	{
	//		ret = sc.top();    //不加，会死循环（因为它不知道左孩子有没有被遍历过）
	//		cout << ret->_data << " ";
	//		sc.pop();
	//		if (ret->_right != NULL)
	//		{
	//			sc.push(ret->_right);
	//		}
	//	}
	//}

	cout << endl;
}

//后序遍历
template<class T>
void BinaryTree<T>::PostOrder()
{
	cout << "后序：";
	_PostOrder(_root);
	cout << endl;
}
template<class T>
void BinaryTree<T>::_PostOrder(Node *root)
{
	if (root)
	{
		_PostOrder(root->_left);
		_PostOrder(root->_right);
		cout << root->_data << " ";
	}
}
template<class T>
void BinaryTree<T>::NonR_PostOrder()   //非递归后序遍历
{
	if (_root == NULL)
	{
		return;
	}
	stack<Node*> sc;
	Node* cur = _root;
	Node* prev = NULL;
	while (!sc.empty() || cur)
	{
		while (cur)
		{
			sc.push(cur);
			cur = cur->_left;
		}
		if (prev == sc.top()->_right || sc.top()->_right == NULL)
		{
			cout << sc.top()->_data << " ";
			prev = sc.top();
			sc.pop();
		}
		else
		{
			cur = sc.top()->_right;
		}
	}
	cout << endl;
}

//层序遍历
template<class T>
void BinaryTree<T>::LevelOrder()
{
	cout << "层序：";
	_LevelOrder(_root);
	cout << endl;
}
template<class T>
void BinaryTree<T>::_LevelOrder(Node *root)
{
	cout << "层序：";
	queue<Node*>qe;
	if (root)
	{
		qe.push(root);
	}
	while (!qe.empty())
	{
		Node* qu = qe.front();
		cout << qu->_data << " ";
		qe.pop();
		if (qu->_left)
		{
			qe.push(qu->_left);
		}
		if (qu->_right)
		{
			qe.push(qu->_right);
		}
	}
	/*while (!qe.empty())
	{
	if (root->_left)
	{
	qe.push(root->_left);
	}
	if (root->_right)
	{
	qe.push(root->_right);
	}
	cout << qe.front()->_data<< " ";
	qe.pop();
	if (!qe.empty())
	{
	root = qe.front();
	}
	}*/
}

//二叉树节点个数
template<class T>
size_t BinaryTree<T>::Size()
{
	size_t count = 0;
	return _Size(_root, count);
}
template<class T>
/*  //设置静态变量有可能会引发线程安全问题
size_t BinaryTree<T>::_Size(Node* root)
{
static int count = 0;
if (root)
{
_Size(root->_left);
_Size(root->_right);
count++;
}
return count;
}*/
size_t BinaryTree<T>::_Size(Node* root, size_t &count)
{
	if (root == NULL)
	{
		return 0;
	}
	else
	{
		_Size(root->_left, count);
		_Size(root->_right, count);
	}
	return ++count;
}

//二叉树的深度
template<class T>
size_t BinaryTree<T>::Depth()
{
	return _Depth(_root);
}
template<class T>
size_t BinaryTree<T>::_Depth(Node* root)
{
	if (root == NULL)
	{
		return 0;
	}
	size_t leftCount = _Depth(root->_left);
	size_t rightCount = _Depth(root->_right);
	if (leftCount >= rightCount)
	{
		return leftCount + 1;
	}
	else
	{
		return rightCount + 1;
	}
}

//叶子节点数
template<class T>
size_t BinaryTree<T>::LeafSize()
{
	size_t count = 0;
	return _LeafSize(_root, count);
}
template<class T>
size_t BinaryTree<T>::_LeafSize(Node* root, size_t &count)
{
	if (root == NULL)
	{
		return count;
	}
	if (root->_left == NULL&&root->_right == NULL)
	{
		return ++count;
	}
	_LeafSize(root->_left, count);
	_LeafSize(root->_right, count);
	return count;
}


//求二叉树中任意两个节点的最近公共祖先
template<class T>
void  BinaryTree<T>::FindLowestCommonAncestor(Node* node1, Node* node2)
{
	Node* ancestor = NULL;
	int ret = _FindLCA(_root, node1, node2, ancestor);
	cout << "The ancestor of " << node1->_data << " and " << node2->_data << " is ";
	if (ret == 2)
	{
		cout << ancestor->_data << endl;
	}
	else
	{
		cout << "	not exit !" << endl;
	}
}
template<class T>
int BinaryTree<T>::_FindLCA(Node* root, Node* node1, Node* node2, Node*& ancestor)
{
	if (root == NULL)
		return 0;
	if (root == node1 || root == node2)
		return 1;
	int left = _FindLCA(root->_left, node1, node2, ancestor);
	if (left == 2)return 2;
	int right = _FindLCA(root->_right, node1, node2, ancestor);
	if (right == 2)return 2;
	if (left + right == 2)
	{
		ancestor = root;
	}
	return left + right;
}

//测试
void Test1()
{
	int a1[11] = { 1, 2, 3, '#', '#', 4, '#', '#', 5, 6, '#' };
	int a2[10] = { 1, 2, 3, '#', '#', 4, '#', '#', 5, 6 };
	int a3[15] = { 1, 2, '#', 3, '#', '#', 4, 5, '#', 6, '#', 7, '#', '#', 8 };

	BinaryTree<int>t1(a1, 11, '#');
	BinaryTree<int>t2(a2, 10, '#');
	BinaryTree<int>t3(a3, 15, '#');
	BinaryTree<int>t4(t2);
	t4.PrevOrder();
	//t1.~BinaryTree();
	t4 = t3;
	t4.PrevOrder();
	/*t1.PrevOrder();
	t1.InOrder();
	t1.PostOrder();
	t1.LevelOrder();
	cout << "Size -> "<<t1.Size() << endl;
	cout << "Depth -> "<<t1.Depth() << endl;
	cout << "LeafSize -> " << t1.LeafSize() << endl;
	cout << endl;
	t3.PrevOrder();
	t3.InOrder();
	cout << "Size -> " << t3.Size() << endl;
	cout << "Depth -> " << t3.Depth() << endl;
	cout << "LeafSize -> " << t3.LeafSize() << endl;*/
}
void Test2()
{
	int a1[10] = { 1, 2, 3, '#', '#', 4, '#', '#', 5, 6 };
	int a2[15] = { 1, 2, '#', 3, '#', '#', 4, 5, '#', 6, '#', 7, '#', '#', 8 };
	BinaryTree<int>t1(a1, 10, '#');
	BinaryTree<int>t2(a2, 15, '#');
	/*t1.PrevOrder();
	t1.NonR_PrevOrder();
	t2.PrevOrder();
	t2.NonR_PrevOrder();*/
	/*t1.InOrder();
	t1.NonR_InOrder();
	t2.InOrder();
	t2.NonR_InOrder();*/
	t1.PostOrder();
	t1.NonR_PostOrder();
	t2.PostOrder();
	t2.NonR_PostOrder();
}
//void Test3()
//{
//	int a1[] = { 1, 2, 3, '#', 8, '#', '#', 4, '#', '#', 5, 6, '#', '#', 7 };
//	//	int a2[] = { 1, 2, 4, 8, '#', '#', '#', 5, '#', '#', 3, 6, '#', '#', 7 };
//	int a3[] = { 1, 2, 3, 8, '#', '#', '#', 4, '#', '#', 5, 6, '#', '#', 7 };
//	//int a3[] = { 1, 2, 3, 8, '#', 9, '#', 4, '#', '#', 5, 6, '#', '#', 7 };
//	//int a3[] = { 1, 2, 3, '#', '#', 4,5, '#', '#' , 6, '#','#' };
//	//int a3[] = {0, 1,  3, 7, '#','#', 8, '#','#', 4, '#', '#', 2,5, '#', '#' };
//	//int a3[] = { NULL};
//	//int a3[] = {1 };
//	BinaryTree<int>t1(a1, (sizeof(a1) / sizeof(a1[0])), '#');
//	//	BinaryTree<int>t2(a2, 15, '#');	
//	BinaryTree<int>t3(a3, (sizeof(a3) / sizeof(a3[0])), '#');
//
//	t1.InOrder();
//	//	t2.InOrder();
//	t3.InOrder();
//	if (t1.IsCompleteTree() == true)
//		cout << "This BinaryTree is Complete Tree !" << endl;
//	else
//		cout << "This BinaryTree isn't Complete Tree !" << endl;
//
//	//if (t2.IsCompleteTree() == true)
//	//	cout << "This BinaryTree is Complete Tree !" << endl;
//	//else
//	//	cout << "This BinaryTree isn't Complete Tree !" << endl;
//
//	if (t3.IsCompleteTree() == true)
//		cout << "This BinaryTree is Complete Tree !" << endl;
//	else
//		cout << "This BinaryTree isn't Complete Tree !" << endl;
//}
//void Test4()
//{
//	int a1[10] = { 1, 2, 3, '#', '#', 4, '#', '#', 5, 6 };
//	int a2[15] = { 1, 2, '#', 3, '#', '#', 4, 5, '#', 6, '#', 7, '#', '#', 8 };
//	BinaryTree<int>t1(a1, 10, '#');
//	BinaryTree<int>t2(a2, 15, '#');
//	BinaryTreeNode<int>* node1 = t1.Find(3);
//	BinaryTreeNode<int>* node2 = t1.Find(4);
//	//t1.FindLowestCommonAncestor(node1, node2);
//
//}
void Test4()
{
	int a1[11] = { 1, 2, 3, '#', '#', 4, '#', '#', 5, 6, '#' };
	BinaryTree<int>t1(a1, 11, '#');
	BinaryTreeNode<int>* a=t1.Find(4);
	BinaryTreeNode<int>* b = t1.Find(6);
	t1.FindLowestCommonAncestor(a,b);
}
int main()
{
	//Test1();
	//Test2();
	//Test3();
	Test4();
	system("pause");
	return 0;
}