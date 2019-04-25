#include"binarytree.h"
#include"stack.h"
#include"queue.h"
#include<stdio.h>
#include<stdlib.h>

#define MaxSize 50//栈和队列的大小

//先序递归创建二叉树
BinTree CreateTree()
{
    TreeElementType ch;
	BinTree BT;
    ch = getchar();
	if(ch == '0')
	    BT = NULL;
	else
	{
		BT = (BinTree)malloc(sizeof(struct TreeNode));
		if(NULL == BT)
		{
			printf("Out of space!!!");
			return NULL;
		}
		BT->Element = ch;
		BT->Left = CreateTree();
		BT->Right = CreateTree();
	}
	return BT;
}

void PreOrderTraversal(BinTree BT)
{
	if(BT)
	{
		printf("%c ", BT->Element);
		PreOrderTraversal(BT->Left);
		PreOrderTraversal(BT->Right);
	}
}

void InOrderTraversal(BinTree BT)
{
	if(BT)
	{
		InOrderTraversal(BT->Left);
		printf("%c ", BT->Element);
		InOrderTraversal(BT->Right);
	}
}

void PostOrderTraversal(BinTree BT)
{
	if(BT)
	{
		PostOrderTraversal(BT->Left);
		PostOrderTraversal(BT->Right);
		printf("%c ", BT->Element);
	}
}


/*-------------------下面是非递归写法------------------------*/
//先序非递归创建二叉树
BinTree IterationCreateTree()
{
	int Flag[MaxSize] = {0};
	Stack S;
	S = CreatStack(MaxSize);
	TreeElementType ch;
	BinTree Root;
	PtrToNode NewCell, T;
	printf("请输入简单二叉树的元素类似：222003004500600：\n");
	do{
		ch = getchar();
		if(ch == '0')
	    	NewCell = NULL;
		else
		{
			NewCell = (BinTree)malloc(sizeof(struct TreeNode));
			if(NULL == NewCell)
			{
				printf("Alloc is fairure!!");
				return NULL;
			}
			else
			{
				NewCell->Element = ch;
				NewCell->Left = NewCell->Right = NULL;
			}
		}
		//根节点入栈
		if(IsEmpty(S) && NewCell)
		{
			Push(S, NewCell);
			Root = NewCell;//第一个进栈的为根节点
			Flag[S->TopOfStack] = 0;
        }
        //如果当前(栈顶)节点已经连接左节点，现在连接右节点
		else if(Flag[S->TopOfStack] == 1)
		{
			T = PopAndTop(S);
			T->Right = NewCell;
			if(NewCell)
			{
				Push(S, NewCell);
				Flag[S->TopOfStack] = 0;//元素进栈后都要置为0，清除隐患
			}
		}
		//该左孩子节点入栈，并连接父亲节点
		else
		{
			Flag[S->TopOfStack] = 1;//父亲结点标记为1，表示已经连接左结点
			//下面是连接左结点的代码
			T = Top(S);
			T->Left = NewCell;
			if(NewCell)
			{
				Push(S, NewCell);
				Flag[S->TopOfStack] = 0;//元素进栈后都要置为0，清除隐患
			}
		}
	}while(!IsEmpty(S));

	return Root;
}
//先序
void IterationPreOrderTraversal(BinTree BT)
{
	Stack S;
	S = CreatStack(MaxSize);
	BinTree T = BT;
	while(T || !IsEmpty(S))
	{
		while(T)
		{
			Push(S, T);
			//注意printf的顺序，因为他是在访问左孩子节点时就已经处理了！
			printf("%c ", T->Element);
			T = T->Left;
		}
		if(T == NULL)
		{
			T = PopAndTop(S);
			T = T->Right;
		}
	}
}
//中序
void IterationInOrderTraversal(BinTree BT)
{
	Stack S;
	S = CreatStack(MaxSize);
	BinTree T = BT;
	while(T || !IsEmpty(S))
	{
		while(T)
		{
			Push(S, T);
			T = T->Left;
		}
		if(T == NULL)
		{
			T = PopAndTop(S);
			//printf在访问右孩子之前就处理的当前元素
			printf("%c ", T->Element);
			T = T->Right;
		}
	}
}
//后序
//void IterationPostOrderTraversal(BinTree BT)
//{
//	int Flag[MaxSize];
//	Stack S;
//	S = CreatStack(MaxSize);
//	BinTree T = BT;
//	while(T || !IsEmpty(S))
//	{
//		while(T)
//		{
//			Push(S, T);
//			Flag[S->TopOfStack] = 0;//未处理的标记为0
//			T = T->Left;
//		}
//		while(Flag[S->TopOfStack] == 1)
//		{
//			T = PopAndTop(S);
//			printf("%c ", T->Element);
//			T = NULL;//该节点被处理后，父亲节点的右孩子置空
//		}
//		if(!IsEmpty(S))
//		{
//			T = Top(S);
//			T = T->Right;
//          Flag[S->TopOfStack] = 1;
//		}
//	}
//}
//第二种版本
void IterationPostOrderTraversal(BinTree BT)
{
	int Flag[MaxSize] = {0};
	Stack S;
	S = CreatStack(MaxSize);
	BinTree T = BT;
	while(T || !IsEmpty(S))
	{
		/*将左结点全部入栈*/
		if(T)
		{
			Push(S, T);
			Flag[S->TopOfStack] = 0;//未处理的标记为0
			T = T->Left;
		}
		/*如果已经访问了该结点的右孩子，将它出队并打印*/
		else if(Flag[S->TopOfStack] == 1)
		{
			T = PopAndTop(S);
			printf("%c ", T->Element);
			T = NULL;//该节点被处理后置空，否则会被识别入栈
		}
		/*如果左孩子为空，则访问它的右孩子*/
		else
		{
			T = Top(S);
			T = T->Right;
			Flag[S->TopOfStack] = 1;//访问了右孩子，标记为1
		}
	}
}
//层次
void LevelTraversal(BinTree BT)
{
	Queue Q;
	Q = CreatQueue(MaxSize);
	BinTree T = BT;
	Enqueue(Q, T);
	while(!QIsEmpty(Q))
	{
		T = FrontAndDequeue(Q);
		printf("%c ", T->Element);
		if(T->Left)
			Enqueue(Q, T->Left);
		if(T->Right)
			Enqueue(Q, T->Right);
	}
}

int SumNode(BinTree BT)
{
	if(NULL == BT)
		return 0;
	else if(BT->Left == NULL && BT->Right == NULL)
		return 1;
	else
		return SumNode(BT->Left) + SumNode(BT->Right) + 1;//加1等于是每次返回 加一个根结点
}

int SumLeafNode(BinTree BT)
{
	if(NULL == BT)
		return 0;
	else if(BT->Left == NULL && BT->Right == NULL)
		return 1;
	else
		return SumLeafNode(BT->Left) + SumLeafNode(BT->Right);
}

int Depth(BinTree BT)//输出的是整个二叉树的深度
{
	int DepthOfLeft = 0;
	int DepthOfRight = 0;
	if(NULL == BT)
		return 0;
	else
	{
		DepthOfLeft = Depth(BT->Left);
		DepthOfRight = Depth(BT->Right);
		return (DepthOfLeft > DepthOfRight) ? DepthOfLeft + 1 : DepthOfRight + 1;
	}
}