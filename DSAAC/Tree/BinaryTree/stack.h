/*栈———数组实现申明*/
#ifndef STACKRECORD_H
#define STACKRECORD_H
#include "binarytree.h"

typedef BinTree StackElementType;

struct StackRecord;
typedef struct StackRecord *Stack;

struct StackRecord{
	int Capacity;//栈的大小
	int TopOfStack;//栈顶
	StackElementType *Array;
};

int IsEmpty(Stack S);
int IsFull(Stack S);
Stack CreatStack(int MaxStackSize);
void DisposeStack(Stack S);
void MakeEmpty(Stack S);
void Push(Stack S, StackElementType X);
void Pop(Stack S);
StackElementType Top(Stack S);
StackElementType PopAndTop(Stack S);

#endif
