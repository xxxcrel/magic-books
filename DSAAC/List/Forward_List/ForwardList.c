#include"list.h"
#include<stdio.h>
#include<stdlib.h>

List MakeEmpty(List L)
{
	if(NULL != L)
	{
		L->Next = NULL;
	}
	return L;
}

int IsLast(Position P, List L)//L is unused
{
	return P->Next == NULL;
}

int IsEmpty(List L)
{
	return L->Next == NULL;
}

Position FindPrevious(List L, ElementType x)
{
	Position P;
	P = L;
	while(P->Next && P->Next->Element != x)
	    P = P->Next;
	return P;
}

Position Find(List L, ElementType x)
{
    Position P;
	P = L->Next;
	while(P && P->Element != x)
	    P = P->Next;
	return P;
}

 void Delete(List L, ElementType x)
{
    Position Pre, Tmpcell;

	Pre = FindPrevious(L, x);//we need find the previous of deleted element
	if(!IsLast(Pre, L))
	{
		Tmpcell = Pre->Next;
		Pre->Next = Tmpcell->Next;
		free(Tmpcell);
	}
}

//we insert the element after the position p
void Insert(List L, ElementType x, Position P)
{
    Position TmpCell;
	TmpCell = (List)malloc(sizeof(struct Node));
	if(TmpCell == NULL)
	    printf("No space for allocation!!");
	else
	{
		TmpCell->Element = x;
		TmpCell->Next = P->Next;
		P->Next = TmpCell;
	}
}
//插入链表尾部(尾插法)
void InsertToTail(List L, ElementType x)
{
	Position Last;
	Last = L;
	/*遍历链表找到最后一个结点*/
	while(NULL != Last->Next)
		Last = Last->Next;
	Insert(L, x, Last);
}
//插入链表头部(头插法)
void InsertToHead(List L, ElementType x)
{
	Insert(L, x, L);
}

void PrintList(List L)
{
	PtrToNode Tmp;
	Tmp = L->Next;
	while(Tmp->Next)
	{
	    printf("%c-", Tmp->Element);
	    Tmp = Tmp->Next;
	}
	printf("%c\n", Tmp->Element);
}

void DeleteList(List L)
{
	Position Tmp, P;
	P = L->Next;
	L->Next = NULL;
	while(P != NULL)
	{
		Tmp = P->Next;
		free(P);
		P = Tmp;
	}
	free(L);
}

void Reverse(List L)
{
	Position CurrentPos, NextPos, PreviousPos;

	CurrentPos = L->Next;//当前单链表的第一个节点
	PreviousPos = NULL;//指向新链表的第一个节点，假设开始为空
	while(CurrentPos != NULL)
	{
		NextPos = CurrentPos->Next;//取得当前节点的下一个节点位置
		CurrentPos->Next = PreviousPos;//当前节点连接成新的链表
		PreviousPos = CurrentPos;
		CurrentPos = NextPos;//遍历到下一个节点
	}
	L->Next = PreviousPos;//哑元节点连接新链表的头节点
}
//与上述思想差不多，主要在返回上
/*Asumming(假如）is no header and L is not empty*/
//List Reverse(List L)
//{
//	Position CurrentPos, NextPos, PreviousPos;
//
//	CurrentPos = L;
//	PreviousPos = NULL;
//	while(CurrentPos != NULL)
//	{
//		NextPos = CurrentPos->Next;
//		CurrentPos->Next = PreviousPos;
//		PreviousPos = CurrentPos;
//		CurrentPos = NextPos;
//	}
//	return PreviousPos;
//}
//下面是复杂记忆写法
//void Reverse(List L)//含有头节点
//{
//	Position Tmp, P;
//	Tmp = L->Next;
//	L->Next = NULL;
//	while(Tmp != NULL)
//	{
//		P = Tmp->Next;
//		Tmp->Next = L->Next;
//		L->Next = Tmp;
//		Tmp = P;
//	}
//}
//List Reverse(List L)//不含头节点
//{
//	PtrToNode Tmp, P;
//	P = L;
//	L = NULL;
//	while(P != NULL){
//	    Tmp = P->Next;
//	    P->Next = L;
//	    L = P;
//	    P = Tmp;
//	}
//	return L;
//}
