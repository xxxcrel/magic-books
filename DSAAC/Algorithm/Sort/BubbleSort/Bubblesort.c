#include<stdio.h>

void Swap(int *i, int *j);
void BubbleSort(int a[], int n);

int main()
{
	int i; 
	int a[] = {3, 4, 2, 5, 6, 7, 9, 8, 1, 0,};
	int n = sizeof(a) / sizeof(int);
	BubbleSort(a, n);
	for(i = 0; i < 10; i++)
		printf("%d ", a[i]);
	printf("\n");
	return 0;
}

void Swap(int *i, int *j)
{
	int temp = *i;
	*i = *j;
	*j = temp;
}

void BubbleSort(int a[], int n)
{
    int i, j;
	for(i = 0; i < n - 1; i++)//执行n - 1次，最后第一个不用交换
	{
	    for(j = 0; j < n - 1 - i; j++)//此循环将最大的交换到最后面
	    {
		    if(a[j] > a[j+1])
			{
		    	Swap(&a[j], &a[j + 1]);
		    }
		}
	}
}
