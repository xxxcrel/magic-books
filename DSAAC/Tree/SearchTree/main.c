#include "SearchTree.h"
#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

SearchTree CreatTree();
void PreOrderTraversal(SearchTree ST);
void InOrderTraversal(SearchTree ST);

int main(int argc, char *argv[]) {
	SearchTree ST;
	ST = CreatTree();
	//DisplayTree(ST);
	Position MinSubTree;
	MinSubTree = FindMin(ST);
	printf("该树最小节点是：%c\n", MinSubTree->Element);

	Position MaxSubTree;
	MaxSubTree = FindMax(ST);
	printf("该树最大节点是：%c\n", MaxSubTree->Element);

	ElementType In;
	printf("请输入你要插入的值：");
	scanf("%c", &In);
	getchar();
	ST = Insert(ST, In);
	printf("前序遍历如下：\n");
	PreOrderTraversal(ST);
	printf("\n");
	printf("中序遍历如下：\n");
	InOrderTraversal(ST);
	printf("\n");

	ElementType De;
	printf("请输入你要删除的值: ");
	scanf("%c", &De);
	getchar();
	ST = Delete(ST, De);
	printf("前序遍历如下：\n");
	PreOrderTraversal(ST);
	printf("\n");
	printf("中序遍历如下：\n");
	InOrderTraversal(ST);
	printf("\n");
	return 0;
}
//先序递归创建二叉树
//SearchTree CreatTree()
//{
//	ElementType ch;
//	SearchTree ST;
//	scanf("%d", &ch);
//	if(ch == 0){
//	    ST = NULL;
//	}else{
//		ST = (SearchTree)malloc(sizeof(struct TreeNode));
//		if(!ST){
//			printf("Out of space!!!");
//			return NULL;
//		}
//		ST->Element = ch;
//		ST->Left = CreatTree();
//		ST->Right = CreatTree();
//	}
//	return ST;
//}
//插入法创建一颗排序树
SearchTree CreatTree()
{
	ElementType Elem;
	SearchTree ST;
	ST = NULL;
	printf("请输入搜索树类似：54637#\n");
	Elem = getchar();
	while(Elem != '#')
	{
		ST = Insert(ST, Elem);
		Elem = getchar();
	}
	getchar();
	return ST;
}
void PreOrderTraversal(SearchTree ST)
{
	if(ST)
	{
		printf("%c ", ST->Element);
		PreOrderTraversal(ST->Left);
		PreOrderTraversal(ST->Right);
	}
}
void InOrderTraversal(SearchTree ST)
{
	if(ST)
	{
		InOrderTraversal(ST->Left);
		printf("%c ", ST->Element);
		InOrderTraversal(ST->Right);
	}
}
