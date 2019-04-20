#include<stdio.h>
#include<stdlib.h>

typedef int ElementType;

void MergeSort(ElementType A[], int N);
void Msort(ElementType A[], ElementType Tmp[], int Left, int Right);
void Merge(ElementType A[], ElementType Tmp[], int LStart, int Center, int REnd);

int main()
{
	int i;
    ElementType A[] = {3, 4, 2, 5, 6, 7, 9, 8, 1, 0,};
	int N = sizeof(A) / sizeof(A[0]);
	MergeSort(A, N);
	for(i = 0; i < 10; i++)
		printf("%d ", A[i]);
	printf("\n");
	return 0;
}

void MergeSort(ElementType A[], int N)
{
	ElementType *TmpArray;
	TmpArray = (ElementType*)malloc(sizeof(ElementType) * N);
	if(NULL == TmpArray)
		printf("No space for Tmp Array!!!");
	else
	{
		Msort(A, TmpArray, 0, N - 1);
		free(TmpArray);
	}
}

void Msort(ElementType A[], ElementType TmpArray[], int Left, int Right)
{
	int Center;
	
	if(Left < Right)
	{
		Center = (Left + Right) / 2;
		Msort(A, TmpArray, Left, Center);
		Msort(A, TmpArray, Center + 1, Right);
		Merge(A, TmpArray, Left, Center, Right);
	}
}

void Merge(ElementType A[], ElementType TmpArray[], int LeftStart, int Center, int RightEnd)
{
	int i;
	int TmpStart = LeftStart;
	int LeftEnd = Center;
	int RightStart = Center + 1;
	int NumElements = RightEnd - LeftStart + 1;
	while(LeftStart <= LeftEnd && RightStart <= RightEnd)
	{
		if(A[LeftStart] <= A[RightStart])
			TmpArray[TmpStart++] = A[LeftStart++];
		else
			TmpArray[TmpStart++] = A[RightStart++];
	}
	while(LeftStart <= LeftEnd)
		TmpArray[TmpStart++] = A[LeftStart++];
	while(RightStart <= RightEnd)
		TmpArray[TmpStart++] = A[RightStart++];
	//TmpStart -= 1;
	//printf("RightEnd = %d, TmpStart = %d\n", RightEnd, TmpStart);//验证TmpStart和REnd是否相等
	//for(i = 0; i < NumElements; i++)
	//	A[RightEnd--] = TmpArray[TmpStart--];
	for(i = 0; i < NumElements; i++, RightEnd--)
		A[RightEnd] = TmpArray[RightEnd];
}
