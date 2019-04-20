#include<stdio.h>

#define Cutoff 3//快排的截止范围

typedef int ElementType;

ElementType Median3(ElementType A[], int Left, int Right);
void QuickSort(ElementType A[], int N);
void Qsort(ElementType A[], int Left, int Right);
void InsertionSort(ElementType A[], int N);
void Swap(ElementType *i, ElementType *j);

int main()
{
	int i;
    ElementType A[] = {3, 4, 2, 5, 6, 7, 9, 8, 1, 0,};
	int N = sizeof(A) / sizeof(A[0]);
	QuickSort(A, N);
	for(i = 0; i < 10; i++)
		printf("%d ", A[i]);
	printf("\n");
	return 0;
}

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

void Swap(ElementType *x, ElementType *y)
{
	ElementType Tmp = *x;
	*x = *y;
	*y = Tmp;
}
//Qsort的驱动程序
void QuickSort(ElementType A[], int N)
{
	Qsort(A, 0, N - 1);
}

ElementType Median3(ElementType A[], int Left, int Right)
{
	int Center = (Left + Right) / 2;
	
	if(A[Left] > A[Center])
		Swap(&A[Left], &A[Center]);
	if(A[Left] > A[Right])
		Swap(&A[Left], &A[Right]);
	if(A[Center] > A[Right])
		Swap(&A[Center], &A[Right]);
		
	Swap(&A[Center], &A[Right - 1]);
	return A[Right - 1];
}
//很精彩的快排例程
void Qsort(ElementType A[], int Left, int Right)
{
	int i, j;
	ElementType Pivot;

	if(Left + Cutoff <= Right)
	{
		/*Pivot放在Right - 1的位置上*/
		Pivot = Median3(A, Left, Right);
		/*i初始化为Left + 1，j初始化为Right - 2*/
		i = Left; j = Right - 1;
		for(; ;)
		{
			while(A[++i] < Pivot){}
			while(A[--j] > Pivot){}
			if(i < j)
				Swap(&A[i], &A[j]);
			else
				break;
		}
		Swap(&A[i], &A[Right - 1]);
		Qsort(A, Left, i - 1);
		Qsort(A, i + 1, Right);
	}
	/*小于截止范围的序列采用简单插入排序更好*/
	else
		InsertionSort(A + Left, Right - Left + 1);
}
