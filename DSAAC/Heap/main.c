#include"heap.h"
#include"heap.c"
#include<stdio.h>
#include<math.h>

void PrintHeap(PriorityQueue H);

int main()
{
	int HeapSize;
	ElementType HElement, MinElement;
	PriorityQueue H;
	printf("Please enter the heap size:\n");
	scanf("%d", &HeapSize);
	printf("Please enter the element and end of -1:\n");
	H = Initialize(HeapSize);
	scanf("%d", &HElement);
	for(int i = 1; HElement != -1; i++)
	{
		H->Elements[i] = HElement;
		H->Size++;
		scanf("%d", &HElement);
	}
	BuildHeap(H);
	PrintHeap(H);
	MinElement = DeleteMin(H);
	printf("DeleteMin = %d\n", MinElement);
	MinElement = FindMin(H);
	printf("FindMin = %d\n", MinElement);
	printf("After DeleteMin:\n");
	PrintHeap(H);
	DecreaseKey(H, 3, 3);
	printf("After DecreaseKey(H, 3, 3):\n");
	PrintHeap(H);
	IncreaseKey(H, 4, 4);
	printf("After IncreaseKey(H, 4, 4):\n");
	PrintHeap(H);
	Destroy(H);
	return 0;
}
void OutSpace(int SpaceOnFront)
{
	for(int i = 0; i < pow(2, SpaceOnFront); i++)
		printf(" ");
	printf("\b");
}

void PrintHeap(PriorityQueue H)
{
	int LineStart, LineEnd, Depth = 0;
	for(int i = 1; i <= H->Size; i *= 2)
		Depth++;
	int SpaceOnFront = Depth - 1;
	int Interal = Depth;
	for(int Level = 0; Level < Depth; Level++)
	{
		OutSpace(SpaceOnFront);
		LineStart = pow(2, Level);
		LineEnd = LineStart * 2;
		for(int i = LineStart; i < LineEnd; i++)
		{
			if(i <= H->Size)
			{
				printf("%d", H->Elements[i]);
				OutSpace(Interal);
			}
		}
		printf("\n");
		SpaceOnFront--;
		Interal--;
	}
}