#include<stdio.h>

void Swap(int *i, int *j)
{
	int temp = *i;
	*i = *j;
	*j = temp;
}
void CocktailSort(int a[], int n)
{
	int i, j;
	int left = 0;
	int right = n - 1;
	while(left < right){
		//将最大元素放在最右边
		for(i = left; i < right; i++)
		{
			if(a[i] > a[i+1])
				Swap(&a[i], &a[i + 1]);
	    }
	    right--;
	    //将最小元素放在最左边
	    for(j = right; j > left; j--)
		{
	    	if(a[j] < a[j - 1])
	    		Swap(&a[j], &a[j - 1]);
	    }
	    left++;
	}
}
int main()
{
    int i;
	int a[] = {3, 4, 2, 5, 6, 7, 9, 8, 1, 0,};
	int n = sizeof(a) / sizeof(int);
	CocktailSort(a, n);
	for(i = 0; i < 10; i++){
		printf("%d ", a[i]);
	}
	printf("\n");
	return 0;
}
