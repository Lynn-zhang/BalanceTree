#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include"BTree.h"
using namespace std;

void Test()
{
	int a[] = { 53, 75, 139, 49, 145, 36, 101 };
	BTree<int> bt;
	for (int i = 0; i < sizeof(a) / sizeof(a[0]); i++)
	{
		bt.Insert(a[i]);
	}
	bt.InOrder();
}
int main()
{
	Test();
	system("pause");
	return 0;
}