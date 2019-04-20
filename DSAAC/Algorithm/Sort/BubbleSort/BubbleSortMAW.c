#include<stdio.h>

typedef int ElementType;

void BubbleSort(ElementType A[], int N);
void Swap(ElementType *i, ElementType *j);

int main()
{
	int i, N;
	ElementType A[] = {3, 4, 2, 1, 6, 9, 0, 5, 7, 8,};
	N = sizeof(A) / sizeof(ElementType);
	BubbleSort(A, N);
	for(i = 0; i < N; i++)
		printf("%d ", A[i]);
	return 0;
}

void Swap(ElementType *i, ElementType *j)
{
	int Tmp = *i;
	*i = *j;
	*j = Tmp;
}

void BubbleSort(ElementType A[], int N)
{
	int i, p;
	for(p = N - 1; p >= 0; p--)
	{
		/*假如某一趟中没有发生交换，则说明已经有序，从而节省了时间*/
		int Flag = 0;
		for(i = 0; i < p; i++)
		{
			if(A[i] > A[i + 1])
			{
				Swap(&A[i], &A[i + 1]);
				Flag = 1;
			}
		}
		if(Flag == 0)
			break;
    }
}
