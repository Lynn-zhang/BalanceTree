#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
using namespace std;
#include"RBTree.h"

void TestRBTree()
{
	int array[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15, 20, 100,0,1,2,5};
	RBTree<int, int> tree;
	for (int i = 0; i < sizeof(array) / sizeof(array[0]); i++)
	{
		tree.Insert(array[i], i);
	}

	tree.InOrder();
	bool ret=tree.Check();
	if (ret == true)
		cout << "RBTree is in Balanced !" << endl;
	else
		cout << "RBTree not in a state of balance !" << endl;

}

int main()
{
	TestRBTree();
	system("pause");
	return 0;
}