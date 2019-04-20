#include"heap.h"
#include<stdio.h>
#include<stdlib.h>

#define MinHeapSize 10
#define MinData -1//保证小于堆中每一个元素

int IsFull(PriorityQueue H)
{
	return H->Size == H->Capacity;
}

int IsEmpty(PriorityQueue H)
{
	return H->Size == 0;
}

PriorityQueue Initialize(int MaxHeapSize)
{
	PriorityQueue H;

	if(MaxHeapSize < MinHeapSize)
	{
		printf("HeapSize is too small !!!");
		return NULL;
	}

	H = (PriorityQueue)malloc(sizeof(struct HeapStruct));
	if(NULL == H)
		printf("Allocation failure!!!");
	else
	{
		H->Elements = (ElementType*)malloc(sizeof(ElementType) * (MaxHeapSize + 1));//加1用来添加一个哑元信息
		if(NULL == H->Elements)
			printf("Allocation failure !!!");
		else
		{
			H->Capacity = MaxHeapSize;
			H->Size = 0;
			H->Elements[0] = NULL;
		}
	}

	return H;
}

ElementType DeleteMin(PriorityQueue H)
{
	int i, Child;
	ElementType MinElement, LastElement;

	if(IsEmpty(H))
	{
		printf("Heap is empty!!! can't delete!!");
		return H->Elements[0];
	}

	MinElement = H->Elements[1];
	LastElement = H->Elements[H->Size--];
    /*i 是当前需要下滤的结点*/
	for(i = 1; i * 2 <= H->Size; i = Child)
	{
		Child = i * 2;
		//取得较小的孩子结点
		if(Child != H->Size && H->Elements[Child + 1]->weight < H->Elements[Child]->weight)
			Child++;
		/*percolate one level*/
		if(H->Elements[Child]->weight < LastElement->weight)//当前结点小于最后一个元素
		    H->Elements[i] = H->Elements[Child];//把较小的孩子结点上升到当前结点位置
		else
			break;
	}
	H->Elements[i] = LastElement;
	return MinElement;
}

/*下滤操作*/
void PercolateDown(PriorityQueue H, Position P)
{
	int Child;
    ElementType Tmp;//需要下滤的结点

	for(Tmp = H->Elements[P]; P * 2 <= H->Size; P = Child)
	{

		Child = P * 2;
		/*取得孩子结点中较小的结点*/
		if(Child != H->Size && H->Elements[Child + 1]->weight < H->Elements[Child]->weight)
			Child++;
        /*将取得的孩子结点上升到当前结点*/
		if(H->Elements[Child]->weight < Tmp->weight)
			H->Elements[P] = H->Elements[Child];
		else
			break;
	}
	H->Elements[P] = Tmp;
}

void BuildHeap(PriorityQueue H)
{
	int i;
	for(i = H->Size / 2; i > 0; i--)
		PercolateDown(H, i);
}
