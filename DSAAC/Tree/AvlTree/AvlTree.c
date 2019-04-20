#include "AvlTree.h"
#include<stdio.h>
#include<stdlib.h>

/*********************************
当我们需要平衡新的节点叫a，那么就会有四种情况
1：对a的左儿子的左子树进行一次插入；
2：对a的左儿子的右子树进行一次插入；
3：对a的右儿子的左子树进行一次插入；
4：对a的右儿子的右子树进行一次插入；
**********************************/
AvlTree MakeEmpty(AvlTree T)
{
	if(T != NULL)
	{
		MakeEmpty(T->Left);
		MakeEmpty(T->Right);
		free(T);
	}
	return NULL;
}

Position Find(AvlTree T, ElementType X)
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

Position FindMin(AvlTree T)
{
	if(NULL == T)
		return NULL;
	else if(NULL == T->Left)
		return T;
	else
	    return FindMin(T->Left);
}

Position FindMax(AvlTree T)
{
	if(NULL == T)
		return NULL;
	else if(NULL == T->Right)
		return T;
	else
		return FindMax(T->Right);
}

static int Height(AvlTree T)
{
	if(NULL == T)
		return -1;
	else
		return T->Height;
}

static int Max(int Left, int Right)
{
	return (Left > Right) ? Left : Right;
}

static AvlTree SingleRoateWithLeft(Position K2)
{
	Position K1;

	K1 = K2->Left;
	K2->Left = K1->Right;
	K1->Right = K2;
	K1->Height = Max(Height(K1->Left), Height(K1->Right)) + 1;
	K2->Height = Max(Height(K2->Left), Height(K2->Right)) + 1;

	return K1;
}
static Position SingleRoateWithRight(Position K2)
{
	Position K1;

	K1 = K2->Right;
	K2->Right = K1->Left;
	K1->Left = K2;
	K1->Height = Max(Height(K1->Left), Height(K1->Right)) + 1;
	K2->Height = Max(Height(K2->Left), Height(K2->Right)) + 1;

	return K1;
}

static Position DoubleRoateWithLeft(Position K3)
{
	K3->Left = SingleRoateWithRight(K3->Left);

	return SingleRoateWithLeft(K3);
}
static AvlTree DoubleRoateWithRight(Position K3)
{
	K3->Right = SingleRoateWithLeft(K3->Left);

	return SingleRoateWithRight(K3);
}

AvlTree Insert(AvlTree T, ElementType X)
{
	if(NULL == T)
	{
		T = (AvlTree)malloc(sizeof(struct AvlNode));
		if(NULL == T)
			printf("Allocation failure!");
		else
		{
			T->Element = X;
			T->Left = T->Right = NULL;
			T->Height = 0;
		}
	}
	else if(X < T->Element)
	{
		T->Left = Insert(T->Left, X);
		if(Height(T->Left) - Height(T->Right) == 2)
		{
			if(X < T->Left->Element)//处理情况1（数据结构与算法分析书的情况）
				T = SingleRoateWithLeft(T);
			else
				T = DoubleRoateWithLeft(T);//处理情况2
		}
	}
	else if(X > T->Element)
	{
		T->Right = Insert(T->Right, X);
		if(Height(T->Right) - Height(T->Left) == 2)
		{
			if(X > T->Right->Element)
				T = SingleRoateWithRight(T);//处理情况4
			else
				T = DoubleRoateWithRight(T);//处理情况3
		}
	}

	T->Height = Max(Height(T->Left), Height(T->Right)) + 1;
	return T;
}

AvlTree Delete(AvlTree T, ElementType X)
{
	if(NULL == T)
	{
		printf("Sorry can't Delete!");
		return NULL;
	}
	else if(X < T->Element)
	{
		T->Left = Delete(T->Left, X);
		/*当删除左边时相当于右边插入了，致使右边不平衡*/
		if(Height(T->Right) - Height(T->Left) == 2)
		{
			Position P = T->Right;
			if(Height(P->Right) > Height(P->Left))//处理情况3（数据结构与算法分析书的情况）
				T = SingleRoateWithRight(T);
			else
				T = DoubleRoateWithLeft(T);//处理情况4
		}
	}
	else if(X > T->Element)
	{
		T->Right = Delete(T->Right, X);
		/*当删除右边时相当于左边插入了，致使左边不平衡*/
		if(Height(T->Left) - Height(T->Right) == 2)
		{
			Position P = T->Left;
			if(Height(P->Left) > Height(P->Right))
				T = SingleRoateWithLeft(T);//处理情况1
			else
				T = DoubleRoateWithLeft(T);//处理情况2
		}
	}
	else if(T->Left && T->Right)
	{

		if(Height(T->Left) > Height(T->Right))
		{
		// 如果tree的左子树比右子树高；
        // 则(01)找出tree的左子树中的最大节点
        //   (02)将该最大节点的值赋值给tree。
        //   (03)删除该最大节点。
        // 这类似于用"tree的左子树中最大节点"做"tree"的替身；
        // 采用这种方式的好处是：删除"tree的左子树中最大节点"之后，AVL树仍然是平衡的。
			Position Max;
			Max = FindMax(T->Left);
			T->Element = Max->Element;
			T->Left = Delete(T->Left, Max->Element);//删除左子树上的最大元素，因为它已经上移
		}else
		{
		// 如果tree的右子树比左子树高；
        // 则(01)找出tree的右子树中的最小节点
        //   (02)将该最小节点的值赋值给tree。
        //   (03)删除该最小节点。
        // 这类似于用"tree的右子树中最小节点"做"tree"的替身；
        // 采用这种方式的好处是：删除"tree的右子树中最小节点"之后，AVL树仍然是平衡的。
			Position Min;
			Min = FindMin(T->Right);
			T->Element = Min->Element;
			T->Right = Delete(T->Right, Min->Element);//删除它的右子树上最小元素，因为它已经上移
		}
	}
	else
	{
		Position TmpCell = T;
		if(NULL == T->Left)
			T = T->Right;//让T的父节点连接它的右节点
        else if(NULL == T->Right)
			T = T->Left;//让T的父节点连接它的左节点
        /*else T have zero node , free it directly*/
        free(TmpCell);
    }
    if(T != NULL)
    {
    	T->Height = Max(Height(T->Left), Height(T->Right)) + 1;
    }

    return T;
}
