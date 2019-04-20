#include"searchtree.h"
#include<stdio.h>
#include<stdlib.h>

SearchTree MakeEmpty(SearchTree T)
{
	if(NULL != T)
	{
		MakeEmpty(T->Left);
		MakeEmpty(T->Right);
		free(T);
	}
	return NULL;
}

Position Find(SearchTree T, ElementType X)
{
	if(NULL == T)
		return NULL;
	if(X < T->Element)
		return Find(T->Left, X);
	else if(X > T->Element)
		return Find(T->Right, X);
	else
		return T;
}

Position FindMin(SearchTree T)
{
	if(NULL == T)
		return NULL;//用来处理空树情况
	else if(NULL == T->Left)
		return T;//找到最小结点
	else
		return FindMin(T->Left);
}

Position FindMax(SearchTree T)
{
	if(NULL == T)
		return NULL;
	else if(NULL == T->Right)
		return T;
	else
		return FindMax(T->Right);
}

SearchTree Insert(SearchTree T, ElementType X)
{
	if(NULL == T)
	{
		T = (SearchTree)malloc(sizeof(struct TreeNode));
		if(NULL == T)
		   printf("Allocate is fairure!");
		else
		{
			T->Element = X;
			T->Left = T->Right = NULL;
		}
	}
	else if(X < T->Element)//继续往左寻找地方插入，并更新左孩子节点
		T->Left = Insert(T->Left, X);
	else if(X > T->Element)//继续往右寻找地方插入，并更新右孩子节点
		T->Right = Insert(T->Right, X);
	/*else X is in the tree already wo will do nothing */

	return T;//Don't forget the step
}

SearchTree Delete(SearchTree T, ElementType X)
{
	Position TmpCell;

	if(NULL == T)
	{
		printf("Tree is empty! can't find!");
		return NULL;
	}
	else if(X < T->Element)
		T->Left = Delete(T->Left, X);
	else if(X > T->Element)
		T->Right = Delete(T->Right, X);
	else if(T->Left && T->Right)//have two children
	{
		TmpCell = FindMin(T->Right);//寻找右边最小的元素来替补当前节点
		T->Element = TmpCell->Element;
		T->Right = Delete(T->Right, T->Element);//删除右子树中最小的元素，因为已经存在
	}
	else//删除的节点有'零'个或一个子节点
	{
		TmpCell = T;
		if(NULL == T->Left)
			T = T->Right;
		else if(NULL == T->Right)
			T = T->Left;
		//else have zero node, free it directly
		free(TmpCell);
	}

	return T;
}

//下面是迭代写法
//Position Find(SearchTree T, ElementType X)
//{
//	while(NULL != T)
//	{
//		if(X < T->Element)
//		   T = T->Left;
//		else if(X > T->Element)
//		   T = T->Right;
//		else
//		   return T;
//	}
//	return NULL;
//}
//
//Position FindMin(SearchTree T)
//{
//	if(NULL != T)
//	{
//		while(T->Left)
//		{
//			T= T->Left;
//		}
//    }
//    return T;
//}
//
//Position FindMax(SearchTree T)
//{
//	if(NULL != T)
//   {
//		while(T->Right)
//        {
//			T = T->Right;
//		}
//	}
//	return T;
//}
//
//SearchTree Insert(SearchTree T, ElementType X)
//{
//    Position Pre, NewCell;
//	SearchTree Root;
//	Root = T;
//	while(T)
//    {
//    	Pre = T;//记录插入位置的父亲结点
//		if(X < T->Element)
//			T = T->Left;
//		else if(X > T->Element)
//			T = T->Right;
//		else//X存在，什么也不做
//			return Root;
//	}
//
//	NewCell = (SearchTree)malloc(sizeof(struct TreeNode));
//	if(NULL == NewCell)
//		printf("Allocation failure!");
//	else
//	{
//		NewCell->Element = X;
//		NewCell->Left = NewCell->Right = NULL;
//	}
//
//	if(NULL == Root)//空树情况
//		Root = NewCell;
//	else if(X < Pre->Element)
//		Pre->Left = NewCell;
//	else if(X > Pre->Element)
//		Pre->Right = NewCell;
//
//	return Root;
//}

