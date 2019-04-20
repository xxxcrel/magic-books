#include"heap.h"
#include<stdio.h>
#include<stdlib.h>
/*
堆——也叫优先队列
同时也是一个完全二叉树
具体实现用到数组更加方便
下面的所有操作都是以构造一个heap（min）为主
*/

#define MinHeapSize 10
#define MinData 1//保证小于堆中每一个元素

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
			H->Elements[0] = MinData;
		}
	}

	return H;
}


void MakeEmpty(PriorityQueue H)
{
	if(!IsEmpty(H))
		H->Size = 0;
}

void Destroy(PriorityQueue H)
{
	if(!IsEmpty(H))
	{
		free(H->Elements);
		free(H);
	}
}

void Insert(PriorityQueue H, ElementType X)
{
	int i;
	if(IsFull(H))
	{
		printf("Can't Insert, Heap is Full!!!");
		return;
	}
	//如果X小于父亲结点，将父亲结点往下
	for(i = ++H->Size; X < H->Elements[i / 2]; i /= 2)
		H->Elements[i] = H->Elements[i / 2];

	H->Elements[i] = X;
}

ElementType DeleteMin(PriorityQueue H)
{
	int i, Child;
	int MinElement, LastElement;

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
		if(Child != H->Size && H->Elements[Child + 1] < H->Elements[Child])
			Child++;
		/*percolate one level*/
		if(H->Elements[Child] < LastElement)//当前结点小于最后一个元素
		    H->Elements[i] = H->Elements[Child];//把较小的孩子结点上升到当前结点位置
		else
			break;
	}
	H->Elements[i] = LastElement;
	return MinElement;
}

ElementType FindMin(PriorityQueue H)
{
	if(!IsEmpty(H))
		return H->Elements[1];
	printf("Sorry! the Heap is Empty!!!");
	return 0;
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
		if(Child != H->Size && H->Elements[Child + 1] < H->Elements[Child])
			Child++;
        /*将取得的孩子结点上升到当前结点*/
		if(H->Elements[Child] < Tmp)
			H->Elements[P] = H->Elements[Child];
		else
			break;
	}
	H->Elements[P] = Tmp;
}
/*上滤操作*/
void PercolateUp(PriorityQueue H, Position P)
{
	ElementType Tmp;//需要上滤的结点

	for(Tmp = H->Elements[P]; Tmp < H->Elements[P / 2]; P /= 2)
		H->Elements[P] = H->Elements[P / 2];//将父亲结点下滤到当前结点
	H->Elements[P] = Tmp;
}
//减少关键字的值，位置P上的值减少De
void DecreaseKey(PriorityQueue H, Position P, ElementType De)
{
	if(IsEmpty(H))
		printf("Sorry! The heap is Empty!!");
	else
	{
		H->Elements[P] -= De;
		PercolateUp(H, P);
    }
}
//增加关键字的值，位置P上的值增加Ad
void IncreaseKey(PriorityQueue H, Position P, ElementType Ad)
{
	if(IsEmpty(H))
		printf("Sorry! The heap is empty!!");
	else
	{
		H->Elements[P] += Ad;
		PercolateDown(H, P);
	}
}

void Delete(PriorityQueue H, Position P)
{
	if(IsEmpty(H))
		printf("Sorry! The heap is empty!!");
	else
	{
		DecreaseKey(H, P, H->Elements[P]);
		PercolateUp(H, P);
		DeleteMin(H);
	}
}

void BuildHeap(PriorityQueue H)
{
	int i;
	for(i = H->Size / 2; i > 0; i--)
		PercolateDown(H, i);
}
