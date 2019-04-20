/*栈———数组实现申明*/
#ifndef STACKRECORD_H
#define STACKRECORD_H

typedef char ElementType;

struct StackRecord;
typedef struct StackRecord *Stack;

struct StackRecord{
	int Capacity;//栈的大小
	int TopOfStack;//栈顶
	ElementType *Array;
};

int IsEmpty(Stack S);
int IsFull(Stack S);
Stack CreatStack(int MaxStackSize);
void DisposeStack(Stack S);
void MakeEmpty(Stack S);
void Push(Stack S, ElementType X);
void Pop(Stack S);
ElementType Top(Stack S);
ElementType PopAndTop(Stack S);

#endif
