#include"cursor.h"
#include<stdio.h>

#define SpaceSize 20

struct Node CursorSpace[SpaceSize + 1];//定义一个全局CursorSpace空间

void InitializeCursorSpace()
{
	int Slot;
	for(Slot = 0; Slot < SpaceSize + 1; Slot++)
	{
		if(Slot != SpaceSize)
			CursorSpace[Slot].Next = Slot + 1;
		else
		   CursorSpace[Slot].Next = 0;
	}
}

static Position CursorAlloc()
{
	Position P;
	P = CursorSpace[0].Next;
	CursorSpace[0].Next = CursorSpace[P].Next;
	return P;
}

static void CursorFree(Position P)
{
	CursorSpace[P].Next = CursorSpace[0].Next;
	CursorSpace[0].Next = P;
}

List MakeEmpty(List L)
{
	if(L != 0)
		CursorSpace[L].Next = 0;
	return L;
}
int IsLast(Position P, List L)
{
	return CursorSpace[P].Next == 0;
}

int IsEmpty(List L)
{
	return CursorSpace[L].Next == 0;
}

Position FindPrevious(List L, ElementType X)
{
	Position P;
	P = L;
	while(CursorSpace[P].Next && CursorSpace[CursorSpace[P].Next].Element != X)
		P = CursorSpace[P].Next;
	return P;
}

Position Find(List L, ElementType X)
{
	Position P;
	P = CursorSpace[L].Next;
	while(P && CursorSpace[P].Element != X)
		P = CursorSpace[P].Next;
	return P;
}

void Delete(List L, ElementType X)
{
	Position Pre, Tmp;
	Pre = FindPrevious(L, X);
	if(Pre == 0)
		printf("Sorry! Can't find element");
	else
	{
		Tmp = CursorSpace[Pre].Next;
		CursorSpace[Pre].Next = CursorSpace[Tmp].Next;
		CursorFree(Tmp);
	}
}

void Insert(List L, ElementType X, Position P)
{
	Position NewCell;
	NewCell = CursorAlloc();
	if(NewCell == 0)
		printf("No space for allocation!!");
	else
	{
		CursorSpace[NewCell].Element = X;
		CursorSpace[NewCell].Next = CursorSpace[P].Next;
		CursorSpace[P].Next = NewCell;
	}
}

void InsertToTail(List L, ElementType X)
{
	Position Last;
	Last = L;
	/*遍历链表寻找最后一个结点*/
    while(CursorSpace[Last].Next != 0)
		Last = CursorSpace[Last].Next;
	Insert(L, X, Last);
}

void InsertToHead(List L, ElementType X)
{
	Insert(L, X, L);
}

void DeleteList(List L)
{
	Position P, Tmp;
	P = CursorSpace[L].Next;
	CursorSpace[L].Next = 0;
	while(P != 0)
	{
		Tmp = CursorSpace[P].Next;
		CursorFree(P);
		P = Tmp;
	}
}

void PrintList(List L)
{
	Position P;
	P = CursorSpace[L].Next;
	while(CursorSpace[P].Next != 0)
	{
		printf("%c-", CursorSpace[P].Element);
		P = CursorSpace[P].Next;
	}
	printf("%c\n", CursorSpace[P].Element);
}


