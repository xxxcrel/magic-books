#include<stdio.h>

#define LeftChild(i) (2 * i + 1)//此处的原因看下滤操作的图解

typedef int ElementType;

void PercoDown(ElementType A[], int i, int N);
void HeapSort(ElementType A[], int N);
void Swap(ElementType *i, ElementType *j);

int main()
{
	int i;
	ElementType A[] = {2, 3, 1, 9, 5, 4, 0, 6, 8, 7,};
	int N = sizeof(A) / sizeof(A[0]);
	HeapSort(A, N);
	for(i = 0; i < N; i++)
		printf("%d ", A[i]);
	return 0;
}
/*
PercoDown例程图解
          0
      1       2
   3     4 5     6
 7   8 9
将这里的下滤和二叉堆中的下滤标号做比较可知
          1
      2       3
   4     5 6     7
 9   9  10
*/
void PercDown(ElementType A[], int i, int N)
{
	int Child;
	ElementType Tmp;
	for(Tmp = A[i]; LeftChild(i) < N; i = Child)
	{
		Child = LeftChild(i);
		/*取得孩子结点中较大的结点*/
		if(Child != N - 1 && A[Child + 1] > A[Child])
			Child++;
        /*将取得的结点上升到当前结点*/
		if(Tmp < A[Child])
			A[i] = A[Child];
		else
			break;
	}
	A[i] = Tmp;
}

void HeapSort(ElementType A[], int N)
{
	int i;
	for(i = N / 2; i >= 0; i--)
		PercDown(A, i, N);//此处构造一个heap（max）
	for(i = N - 1; i > 0; i--)
	{
		Swap(&A[0], &A[i]);
		PercDown(A, 0, i);
	}
}

void Swap(ElementType *i, ElementType *j)
{
	int Tmp = *i;
	*i = *j;
	*j = Tmp;
}
