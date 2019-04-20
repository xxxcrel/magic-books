#include"queue.h"
#include<stdio.h>
#include<stdlib.h>

int IsEmpty(Queue Q)
{
	return Q->Front == NULL;//Q->Rear == NULL;
}

Queue CreatQueue()
{
	Queue Q;
	Q = (Queue)malloc(sizeof(struct PtrsToList));
	if(Q == NULL)
		printf("Malloc failure!");
	else
	{
		Q->Rear = Q->Front = NULL;
		MakeEmpty(Q);
	}
	return Q;
}

void MakeEmpty(Queue Q)
{
	if(Q == NULL)
		printf("Please creatqueue first!");
	else
	{
		while(!IsEmpty(Q))
			Dequeue(Q);
	}
}

void DiseposeQueue(Queue Q)
{
	PtrToNode P, Tmp;
	P = Q->Front;
	while(P != NULL)
	{
		Tmp = P->Next;
		free(P);
		P = Tmp;
	}
	Q->Front = Q->Rear = NULL;
	free(Q);
}

void Enqueue(Queue Q, ElementType X)
{
	PtrToNode TmpNode;
	TmpNode = (PtrToNode)malloc(sizeof(struct Node));
	if(TmpNode == NULL)
        printf("Malloc failure!");
	else
	{
		TmpNode->Element = X;
		TmpNode->Next = NULL;
		if(IsEmpty(Q))
		{
			Q->Front = TmpNode;
			Q->Rear = TmpNode;
		}
		else
		{
		    Q->Rear->Next = TmpNode;
		    Q->Rear = TmpNode;
		}
	}
}

void Dequeue(Queue Q)
{
	PtrToNode FrontNode;
	if(!IsEmpty(Q))
	{
		FrontNode = Q->Front;
		if(Q->Front == Q->Rear)
			Q->Front = Q->Rear = NULL;
	    else
			Q->Front = Q->Front->Next;
        free(FrontNode);
	}
}

ElementType Front(Queue Q)
{
	if(!IsEmpty)
		return Q->Front->Element;
	printf("Queue is empty!");
	return 0;
}

ElementType FrontAndDequeue(Queue Q)
{
	PtrToNode FrontCell;
	ElementType FrontElement;
	if(!IsEmpty(Q))
	{
		FrontCell = Q->Front;
		if(Q->Front == Q->Rear)
			Q->Front = Q->Rear = NULL;
		else
			Q->Front = Q->Front->Next;
		FrontElement = FrontCell->Element;
		free(FrontCell);
	}
	return FrontElement;
}
void PrintQueue(Queue Q)
{
	PtrToNode Pt;
	Pt = Q->Front;
	while(Pt->Next != NULL)
	{
		printf("%c-", Pt->Element);
		Pt = Pt->Next;
	}
	printf("%c\n", Pt->Element);
}
