#ifndef HEAP_H
#define HEAP_H

#include "mgraph.h"

typedef Edge ElementType;

struct HeapStruct;
typedef struct HeapStruct *PriorityQueue;
typedef int Position;

struct HeapStruct
{
	int Capacity;
	int Size;
	ElementType *Elements;
};

int IsFull(PriorityQueue H);
int IsEmpty(PriorityQueue H);
PriorityQueue Initialize(int MaxHeapSize);
ElementType DeleteMin(PriorityQueue H);

void PecorlateDown(PriorityQueue H, Position P);
void PecorlateUp(PriorityQueue H, Position P);

void BuildHeap(PriorityQueue H);

#endif