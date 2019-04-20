#include<stdio.h>
/*
插入排序主要思想：
假设插入的是一段已经有序的序列；
*/
typedef int ElementType;

void InsertionSort(ElementType A[], int N);//简单插入排序
void BinaryInsertionSort(ElementType A[], int N);//二分插入排序

int main()
{
	int i;
	ElementType A[] = {5, 3, 4, 2, 1, 9, 7, 8, 0, 6, };
	ElementType B[] = {5, 3, 4, 2, 1, 9, 7, 8, 0, 6, };
	int N = sizeof(A) / sizeof(A[0]);
	int M = sizeof(B) / sizeof(B[0]);
	
	InsertionSort(A, N);
	printf("InsertionSort:\t\t");
	for(i = 0; i < N; i++)
		printf("%d ", A[i]);
	putchar('\n');
	
	BinaryInsertionSort(B, M);
	printf("BinaryInsertionSort:\t");
	for(i = 0; i < M; i++)
		printf("%d ", B[i]);
	return 0;
}
//M.A.W例程告诉你，好的代码都可以不用注释
void InsertionSort(ElementType A[], int N)
{
	int j, p;
	ElementType Tmp;
	for(p = 1; p < N; p++)
	{
		Tmp = A[p];
		for(j = p; j > 0 && A[j - 1] > Tmp; j--)
			A[j] = A[j - 1];
		A[j] = Tmp;
	}
}
/*二分插入以O(logN)寻找插入点*/
void BinaryInsertionSort(ElementType B[], int M)
{
	int j, p;
	ElementType Tmp;
	int Left, Center, Right;
	for(p = 1; p < M; p++)
	{
		Tmp = B[p];
		Left = 0;
		Right = p - 1;
		while(Left <= Right)
		{
			Center = (Left + Right) / 2;
			if(Tmp < B[Center])
				Right = Center - 1;
			else
				Left = Center + 1;
		}
		/*将 Left-->p-1 整体往后移一格*/
		for(j = p; j > Left; j--)
			B[j] = B[j - 1];
		B[Left] = Tmp;
	}
}
