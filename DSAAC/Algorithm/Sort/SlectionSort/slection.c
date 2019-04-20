#include<stdio.h>

void Swap(int *i, int *j)
{
	int temp = *i;
	*i = *j;
	*j = temp;
}
void SlectionSort(int a[], int n)
{
    int i, j;
	for(i = 0; i < n - 1; i++)
	{
		int min = i; 
	    for(j = i + 1; j < n; j++)
		{
		    if(a[j] < a[min])
		    	min = j;
		}
		if(min != i)
			Swap(&a[i], &a[min]);
	}
}
int main()
{
	int i; 
	int a[] = {3, 4, 2, 5, 6, 7, 9, 8, 1, 0,};
	int n = sizeof(a) / sizeof(int);
	SlectionSort(a, n);
	for(i = 0; i < 10; i++)
		printf("%d ", a[i]);
	printf("\n");
	return 0;
}
