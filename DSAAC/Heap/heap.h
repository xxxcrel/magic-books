#ifndef HEAP_H
#define HEAP_H

typedef int ElementType;

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
void MakeEmpty(PriorityQueue H);
void Destroy(PriorityQueue H);
void Insert(PriorityQueue H, ElementType X);
ElementType DeleteMin(PriorityQueue H);
ElementType FindMin(PriorityQueue H);

void BuildHeap(PriorityQueue H);
void DecreaseKey(PriorityQueue H, Position P, ElementType De);
void IncreaseKey(PriorityQueue H, Position P, ElementType Ad);
void Delete(PriorityQueue H, Position P);

void PecorlateDown(PriorityQueue H, Position P);
void PecorlateUp(PriorityQueue H, Position P);

#endif