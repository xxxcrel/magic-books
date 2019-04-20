#include<stdio.h>

void InsertionSort(int a[], int n)
{
	int i, p;
	int Tmp;
	/*需经过n - 1躺插入排序*/
	for(p = 1; p < n; p++)
	{
		Tmp = a[p];
		for(i = p; i > 0 && Tmp < a[i - 1]; i--)
			a[i] = a[i - 1];
		a[i] = Tmp;
    }
}
int main()
{
	int i; 
	int a[] = {3, 4, 2, 5, 6, 7, 9, 8, 1, 0,};
	int n = sizeof(a) / sizeof(int);
	InsertionSort(a, n);
	for(i = 0; i < 10; i++){
		printf("%d ", a[i]);
	}
	printf("\n");
	return 0;
}
