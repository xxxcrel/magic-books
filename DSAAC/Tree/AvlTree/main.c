#include"AvlTree.h"
#include<stdio.h>
#include<stdlib.h>
#include"AvlTreeOperate.c"
AvlTree CreatTree();
void PreOrderTraversal(AvlTree AT);
void InOrderTraversal(AvlTree AT);

int main()
{
	AvlTree AT;
	AT = CreatTree();

	ElementType In;
	printf("请输入你要插入的值：");
	scanf("%c", &In);
	getchar();
	AT = Insert(AT, In);
	printf("前序遍历如下：\n");
	PreOrderTraversal(AT);
	printf("\n");
	printf("中序遍历如下：\n");
	InOrderTraversal(AT);
	printf("\n");

	ElementType De;
	printf("请输入你要删除的值: ");
	scanf("%c", &De);
	getchar();
	AT = Delete(AT, De);
	printf("前序遍历如下：\n");
	PreOrderTraversal(AT);
	printf("\n");
	printf("中序遍历如下：\n");
	InOrderTraversal(AT);
	printf("\n");

	return 0;

}

AvlTree CreatTree()
{
	AvlTree AT;
	AT = NULL;
	ElementType X;
	X = getchar();
	while(X != '#')
	{
		AT = Insert(AT, X);
		X = getchar();
	}
	getchar();
	return AT;
}

void PreOrderTraversal(AvlTree AT)
{
	if(AT)
	{
		printf("%c ", AT->Element);
		PreOrderTraversal(AT->Left);
		PreOrderTraversal(AT->Right);
	}
}
void InOrderTraversal(AvlTree AT)
{
	if(AT)
	{
		InOrderTraversal(AT->Left);
		printf("%c ", AT->Element);
		InOrderTraversal(AT->Right);
	}
}
