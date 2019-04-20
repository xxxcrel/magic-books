/*循环队列——主要细节在MakeEmpty那里*/
#include"queue.h"
#include<stdio.h>
#include<stdlib.h>

#define MinQueueSize (5)

int IsEmpty(Queue Q)
{
	return Q->size == 0;
}

int IsFull(Queue Q)
{
	return Q->capacity == Q->size;
}

Queue CreatQueue(int MaxQueueSize)
{
	Queue Q;

	if(MaxQueueSize < MinQueueSize)
		printf("Queue Size is too small!");

	Q = (Queue)malloc(sizeof(struct QueueRecord));
	if(Q == NULL)
	    printf("Aalloc failure!");
	else
	{
		Q->Array = (ElementType*)malloc(sizeof(ElementType) * MaxQueueSize);
		if(Q->Array == NULL)
		    printf("Aalloc failure!");
		else
		{
			Q->capacity = MaxQueueSize;
			MakeEmpty(Q);
		}
	}
	return Q;
}

void MakeEmpty(Queue Q)
{
	Q->size = 0;
	Q->rear = 0;//when enquen a element to queue , rear + 1 make rear == front ,
	Q->front = 1;
}

void DisposeQueue(Queue Q)
{
	if(!IsEmpty(Q))
	{
		free(Q->Array);
		free(Q);
	}
}

//判断是否到队列尾部的函数 static 用来表示只再本程序内
static int Succ(Queue Q, int Value)
{
	if(++Value == Q->capacity)
	    Value = 0;
	return Value;
}

void Enqueue(Queue Q, ElementType X)
{
	if(IsFull(Q))
	    printf("Queue is full!, can't enqueue!\n");
	else
	{
		Q->rear = Succ(Q, Q->rear);//这里的精妙之处我已无法用英语注释 仔细体会！！！
		Q->Array[Q->rear] = X;
		Q->size++;
	}
}

void Dequeue(Queue Q)
{
	if(IsEmpty(Q))
	    printf("Queue is empty!, can't dequeue!\n");
	else
	{
	    Q->front = Succ(Q, Q->front);
	    Q->size--;
	}
}

ElementType Front(Queue Q)
{
	if(!IsEmpty(Q))
	    return Q->Array[Q->front];
	printf("Sorry the queue is empty! can't find the front element!\n");
	return 0;//return value used to avoid warning!
}

ElementType FrontAndDequeue(Queue Q)
{
	ElementType FrontElement;
	if(!IsEmpty(Q))
	{
		FrontElement = Q->Array[Q->front];
		Q->size--;
		Q->front = Succ(Q, Q->front);
	    return FrontElement;
	}
	else
	{
		printf("Sorry the queue is empty! can't find the front element!\n");
		return 0;
	}
}
