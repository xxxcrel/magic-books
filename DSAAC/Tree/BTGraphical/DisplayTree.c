#include "displaytree.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
//这里放一组深度为5的满二叉树元素组：
// phdba00c00fe00g00lji00k00nm00o00xtrq00s00vu00w00bzy00a00dc00e00
static int count = 0;

void DisplayTree(Tree T)
{
	int allNodes = AllNodes(T);
	int depth = TotalDepth(T);
	Flag A = (Flag)malloc(sizeof(struct FlagNode) * allNodes);
	if (NULL == A)
		return;
	MarkTreeNode(T, A, 1);
	//PrintFlag(A, allNodes);
	printf("The binary tree is look like:\n");
	Display(A, allNodes, depth);
}

//给树结点做标记，按理论完全二叉树的序号标记
void MarkTreeNode(Tree T, Flag Array, int No)
{
	if (NULL != T)
	{
		Array[count].SerialNumber = No;
		Array[count++].Element = T->Element;
		MarkTreeNode(T->Left, Array, No * 2);
		MarkTreeNode(T->Right, Array, No * 2 + 1);
	}
}

void Display(Flag Array, int ArraySize, int depth)
{
	int lineStart, lineEnd;
	int spaceInFront = depth - 1;
	int interval = depth;//节点之间的间隔指数
	for (int level = 0; level < depth; level++)
	{
		/*    level:0    ___1                    */
		/*    level:1    _2___3                 */
		/*    level:2    4_5_6_7               */
		lineStart = pow(2, level);
		lineEnd = lineStart * 2;
		OutSpace(spaceInFront); //输出每行前面的空格
		for (int start = lineStart; start < lineEnd; start++)
		{
			/*eg:从4，5，6，7按顺序检测该标志是否存在，存在输出节点，不存在则输出"0"*/
			int exist = 0;
			for (int i = 0; i < ArraySize; i++)
			{
				if (start == Array[i].SerialNumber)
				{
					printf("%c", Array[i].Element);
					exist = 1;
				}
			}
			if (exist == 0)
				printf(" ");
			OutSpace(interval); //输出一个节点后的空格
		}
		printf("\n");
		spaceInFront--;
		interval--;
		OutSpace(spaceInFront);
		//下面输出树枝
		for (int parent = lineStart; parent < lineEnd; parent++)
		{
			int exist = 0;
			for (int i = 0; i < ArraySize; i++)
			{
				if (parent == Array[i].SerialNumber)
				{
					int haveLeft = 0, haveRight = 0; //记录当前节点是否有左右孩子 0 为无
					int leftChild = parent * 2;
					int rightChild = parent * 2 + 1;
					for (int last = i; last < ArraySize; last++)
					{
						if (Array[last].SerialNumber == leftChild)
							haveLeft = 1;
						if (Array[last].SerialNumber == rightChild)
							haveRight = 1;
					}
					OutBranch(haveLeft, haveRight, interval);
					OutSpace(interval);
					exist = 1;
				}
			}
			if (!exist)
			{
				OutBranch(0, 0, interval);
				OutSpace(interval);
			}
		}
		printf("\n");

	}
}

/*可变长树枝"┌─────┴─────┐"*/
void OutBranch(int haveLeft, int haveRight, int interval)
{
	if (haveLeft)
	{
		printf("┌");
		for (int i = 0; i < pow(2, interval) / 2 - 1; i++)
			printf("─");
		if (haveRight)
		{
			/*"┌─────┴─────┐"*/
			printf("┴");
			for (int i = 0; i < pow(2, interval) / 2 - 1; i++)
				printf("─");
			printf("┐");
		}
		else
		{
			/*"┌─────┘        "*/
			printf("┘");
			for (int i = 0; i < pow(2, interval) / 2 - 1; i++)
				printf(" ");
			printf(" ");
		}
	}
	else
	{
		printf(" ");
			for (int i = 0; i < pow(2, interval) / 2 - 1; i++)
				printf(" ");
		if(haveRight)
		{
			/*"      └──────┐"*/
			printf("└");
			for (int i = 0; i < pow(2, interval) / 2 - 1; i++)
				printf("─");
			printf("┐");
		}
		else
		{
			/*"              "*/
			printf(" ");
			for (int i = 0; i < pow(2, interval) / 2 - 1; i++)
				printf(" ");
			printf(" ");
		}
	}
}

void OutSpace(int n)
{
	for (int i = 0; i < pow(2, n); i++)
		printf(" ");
	printf("\b");
}
//辅助debug函数
void PrintFlag(Flag Array, int ArraySize)
{
	for (int i = 0; i < ArraySize; i++)
		printf("%c-->%d\n", Array[i].Element, Array[i].SerialNumber);
}
int TotalDepth(Tree T) //输出的是整个二叉树的深度
{
	int DepthOfLeft = 0;
	int DepthOfRight = 0;
	if (NULL == T)
		return 0;
	else
	{
		DepthOfLeft = TotalDepth(T->Left);
		DepthOfRight = TotalDepth(T->Right);
		return (DepthOfLeft > DepthOfRight) ? DepthOfLeft + 1 : DepthOfRight + 1;
	}
}
int AllNodes(Tree T)
{
	if (NULL == T)
		return 0;
	else if (T->Left == NULL && T->Right == NULL)
		return 1;
	else
		return AllNodes(T->Left) + AllNodes(T->Right) + 1; //加1等于是每次返回 加一个根结点
}
