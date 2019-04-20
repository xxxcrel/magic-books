/*栈———数组实现*/
#include"stack.h"
#include<stdio.h>
#include<stdlib.h>

#define EmptyStack -1/*默认空栈大小*/
#define MinStackSize 5

int IsEmpty(Stack S)
{
	return S->TopOfStack == EmptyStack;
}

int IsFull(Stack S)
{
	return S->Capacity == S->TopOfStack + 1;//考虑数组的计数方式
}

Stack CreatStack(int MaxStackSize)
{
	Stack S;

	if(MaxStackSize < MinStackSize)
	    printf("Stack is too small!");

	S = (Stack)malloc(sizeof(struct StackRecord));
	if(S == NULL)
	    printf("malloc failure!");
	else
	{
		S->Array = (StackElementType*)malloc(sizeof(StackElementType) * MaxStackSize);
		if(S->Array == NULL)
		    printf("malloc failure!");
		else
		{
			S->Capacity = MaxStackSize;
			MakeEmpty(S);
		}
	}
	return S;
}

void MakeEmpty(Stack S)
{
	S->TopOfStack = EmptyStack;
}

void DisposeStack(Stack S)
{
	if(S != NULL)//if S is NULL, that free(S) is meaningless
	{
		free(S->Array);
		free(S);
	}
}

void Push(Stack S, StackElementType X)
{
	if(IsFull(S))
	    printf("Stack is full!");
	else
		S->Array[++S->TopOfStack] = X;
}

void Pop(Stack S)
{
	if(IsEmpty(S))
	    printf("Stack is empty!");
	else
	    S->TopOfStack--;
}

StackElementType Top(Stack S)
{
	if(!IsEmpty(S))
		return S->Array[S->TopOfStack];
	printf("Stack is empty!");
	return 0;//return value used to avoid warning
}

StackElementType PopAndTop(Stack S)
{
	if(!IsEmpty(S))
		return S->Array[S->TopOfStack--];
    printf("Stack is empty!");
    return 0;
}
