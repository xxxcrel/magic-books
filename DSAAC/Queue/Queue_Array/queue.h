#ifndef QUEUERECORD_H
#define QUEUERECORD_H

typedef char ElementType;
struct QueueRecord;
typedef struct QueueRecord *Queue;

struct QueueRecord{
	int capacity;//the fixed size of queue
	int size;//the dynamic size of queue
	int front;
	int rear;
	ElementType *Array;
};

int IsEmpty(Queue Q);
int IsFull(Queue Q);
Queue CreatQueue(int MaxQueueSize);
void MakeEmpty(Queue Q);
void DisposeQueue(Queue Q);
static int Succ(Queue Q, int Value);//循环队列的判断函数
void Enqueue(Queue Q, ElementType X);
void Dequeue(Queue Q);
ElementType Front(Queue Q);
ElementType FrontAndDequeue(Queue Q);

#endif
