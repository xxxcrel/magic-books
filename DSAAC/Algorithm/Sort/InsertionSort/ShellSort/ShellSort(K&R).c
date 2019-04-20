#include<stdio.h>

typedef char ElementType;

void ShellSort(ElementType A[], int N);
void Swap(ElementType *x, ElementType *y);

int main()
{
	int i;
	ElementType A[] = {5, 3, 4, 2, 1, 9, 7, 8, 0, 6, };
	int N = sizeof(A) / sizeof(A[0]);
	ShellSort(A, N);
	printf("ShellSort:\t");
	for(i = 0; i < N; i++)
        printf("%d ", A[i]);
	return 0;
}

void Swap(ElementType *x, ElementType *y)
{
	int Temp = *x;
	*x = *y;
	*y = Temp;
}

void ShellSort(ElementType A[], int N)
{
	int Gap, i, j;
	for(Gap = N / 2; Gap > 0; Gap /= 2)
		for(i = Gap; i < N; i++)
            for(j = i - Gap; j >= 0 && A[j] > A[j + Gap]; j -= Gap)
				Swap(&A[j], &A[j + Gap]);
}
