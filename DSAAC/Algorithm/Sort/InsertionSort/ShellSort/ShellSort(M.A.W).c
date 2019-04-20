#include<stdio.h>

typedef int ElementType;

void ShellSort(ElementType A[], int N);

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

void ShellSort(ElementType A[], int N)
{
	int j, p;
	int Increment;
	ElementType Tmp;
	for(Increment = N / 2; Increment > 0; Increment /= 2)
	{
		/*
		shell排序主要以增量相同的数字为一组进行排序
		假设有20个数字，数组下标分别为 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19；
		那么 第一次取得增量后，将以 {0 5 10 15}{1 6 11 16}{2 7 12 17}{3 8 13 18}{4 9 14 19}
		分成5组进行简单插入排序
		其他增量类似，具体细节看下列代码
		*/
		for(p = Increment; p < N; p++)
		{
			Tmp = A[p];
			for(j = p; j >= Increment && Tmp < A[j - Increment]; j -= Increment)
				A[j] = A[j - Increment];
			/*从代码的美观最好设计成下列代码，但上列代码考虑到与简单插入的比较
			for(j = p; j >= Increment; j -= Increment)
			{
				if(Tmp < A[j - Increment])
					A[j] = A[j - Increment];
				else
					break;
			}
			*/
			A[j] = Tmp;
		}
	}
}
