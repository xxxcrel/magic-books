/*循环队列——主要细节在MakeEmpty那里*/
#include"queue.h"
#include<stdio.h>
#include<stdlib.h>

#define MinQueueSize (5)

int QIsEmpty(Queue Q)
{
	return Q->size == 0;
}

int QIsFull(Queue Q)
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
		Q->Array = (QueueElementType*)malloc(sizeof(QueueElementType) * MaxQueueSize);
		if(Q->Array == NULL)
		    printf("Aalloc failure!");
		else
		{
			Q->capacity = MaxQueueSize;
			QMakeEmpty(Q);
		}
	}
	return Q;
}

void QMakeEmpty(Queue Q)
{
	Q->size = 0;
	Q->rear = 0;//when enquen a element to queue , rear + 1 make rear == front ,
	Q->front = 1;
}

void DisposeQueue(Queue Q)
{
	if(!QIsEmpty(Q))
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

void Enqueue(Queue Q, QueueElementType X)
{
	if(QIsFull(Q))
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
	if(QIsEmpty(Q))
	    printf("Queue is empty!, can't dequeue!\n");
	else
	{
	    Q->front = Succ(Q, Q->front);
	    Q->size--;
	}
}

QueueElementType Front(Queue Q)
{
	if(!QIsEmpty(Q))
	    return Q->Array[Q->front];
	printf("Sorry the queue is empty! can't find the front element!\n");
	return 0;//return value used to avoid warning!
}

QueueElementType FrontAndDequeue(Queue Q)
{
	QueueElementType FrontElement;
	if(!QIsEmpty(Q))
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
