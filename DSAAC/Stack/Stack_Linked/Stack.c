/*栈———链表实现*/
#include"Stack.h"
#include<stdio.h>
#include<stdlib.h>

Stack CreatStack()
{
	Stack S;
	S = (Stack)malloc(sizeof(struct Node));
	if(S == NULL)
	{
	    printf("sorry! malloc is failed!");
	    return NULL;
	}
    else
	{
		S->Next = NULL;
		MakeEmpty(S);//confirm the stack is emptystack
	}
	return S;
}

int IsEmpty(Stack S)
{
	return S->Next == NULL;
}

void MakeEmpty(Stack S)
{
    if(S == NULL)
        printf("Please creatstack first!");
	while(!IsEmpty(S))
		Pop(S);
}

void DiseposeStack(Stack S)
{
	PtrToNode P, Tmp;
	P = S->Next;
	S->Next = NULL;
	while(P != NULL)
	{
		Tmp = P->Next;
		free(P);
		P = Tmp;
	}
}
//头插法入栈
void Push(Stack S, ElementType x)
{
	PtrToNode TmpCell;

	TmpCell = (Stack)malloc(sizeof(struct Node));
	if(TmpCell == NULL)
	    printf("Sorry! malloc is failed!");
	else
	{
		TmpCell->Element = x;
		TmpCell->Next = S->Next;
		S->Next = TmpCell;
	}
}

void Pop(Stack S)
{
	PtrToNode FirstCell;

	if(IsEmpty(S))
	    printf("Sorry the stack is empty!");
	else
	{
	    FirstCell = S->Next;
	    S->Next = FirstCell->Next;
        //S->Next = S->Next->Next;//这样最安全
	    free(FirstCell);
	}
}

ElementType Top(Stack S)
{
	if(!IsEmpty(S))
	    return S->Next->Element;
	printf("Sorry! the stack is empty");
	return 0;
}

ElementType PopAndTop(Stack S)
{
	PtrToNode FirstCell;
	ElementType FirstElement;

    if(IsEmpty(S))
	{
	    printf("Sorry the stack is empty!");
		return 0;
	}
	else
	{
			FirstCell = S->Next;
			FirstElement = S->Next->Element;
			S->Next = S->Next->Next;
			free(FirstCell);
			return FirstElement;
	}
}
