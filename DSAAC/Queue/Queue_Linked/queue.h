#ifndef QUEUE_H
#define QUEUE_H

typedef char ElementType;

struct Node;//队列节点的结构体
typedef struct Node *PtrToNode;

struct PtrsToList;//指向队列节点的结构体
typedef struct PtrsToList *Queue;

struct Node{
	ElementType Element;
	PtrToNode Next;
};

struct PtrsToList{
	PtrToNode Rear;
	PtrToNode Front;
};

int IsEmpty(Queue Q);
Queue CreatQueue();
void MakeEmpty(Queue Q);
void Enqueue(Queue Q, ElementType X);
void Dequeue(Queue Q);
ElementType Front(Queue Q);
ElementType FrontAndDequeue(Queue Q);
void PrintQueue(Queue Q);

#endif
