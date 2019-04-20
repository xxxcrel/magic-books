#ifndef QUEUERECORD_H
#define QUEUERECORD_H
#include"binarytree.h"

typedef BinTree QueueElementType;
struct QueueRecord;
typedef struct QueueRecord *Queue;

struct QueueRecord{
	int capacity;//the fixed size of queue
	int size;//the dynamic size of queue
	int front;
	int rear;
	QueueElementType *Array;
};

int QIsEmpty(Queue Q);
int QIsFull(Queue Q);
Queue CreatQueue(int MaxQueueSize);
void QMakeEmpty(Queue Q);
void DisposeQueue(Queue Q);
static int Succ(Queue Q, int Value);//循环队列的判断函数
void Enqueue(Queue Q, QueueElementType X);
void Dequeue(Queue Q);
QueueElementType Front(Queue Q);
QueueElementType FrontAndDequeue(Queue Q);

#endif
