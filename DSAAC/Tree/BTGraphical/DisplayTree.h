#ifndef _PRINTTREE_H
#define _PRINTTREE_H

//#include "searchtree.h"
//按需选择自己需要打印的各种类型树；
//但只支持类似下面树结点的申明形式：
//struct TreeNode
//{
//	TreeElementType Element;
//	struct TreeNode *Left;
//	struct TreeNode *Right;
//};

typedef SearchTree Tree; //打印其他树类型，请修改此处树类型指针

struct FlagNode
{
	ElementType Element;
	int SerialNumber;
};
typedef struct FlagNode *Flag;

void DisplayTree(Tree T);
void MarkTreeNode(Tree T, Flag Array, int f);
void PrintFlag(Flag Array, int ArraySize);
void Display(Flag Array, int ArraySize, int DepthOfTree);
void OutSpace(int n);
void OutBranch(int haveLeft, int haveRight, int level);
int AllNodes(Tree T);
int TotalDepth(Tree T);

#endif