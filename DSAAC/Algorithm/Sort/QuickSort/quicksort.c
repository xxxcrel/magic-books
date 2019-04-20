#include<stdio.h>

void QuickSort1(int a[], int left, int right)
{
	if(left >= right){
		return ;
	}
	int pivot = a[left];//设最左边的值为基准值 
	int i = left;
	int j = right;
	while(i != j){
		while(a[j] >= pivot && i < j)//从最右边开始往前， 找到小于基准的停下
			j--;
		a[i] = a[j]; 
		while(a[i] <= pivot && i < j)//从最左边开始往后， 找到大于基准的停下
			i++;
		a[j] = a[i];
	}
	a[i] = pivot;//当循环结束令当前的位置为基准值
	//继续递归将前半部分和后半部分求出 
	QuickSort1(a, left, i - 1);
	QuickSort1(a, i + 1, right); 
}
int main()
{
	int i; 
    int a[] = {3, 4, 2, 5, 6, 7, 9, 8, 1, 0,};
	int n = sizeof(a) / sizeof(int);
	QuickSort1(a, 0, n - 1);
	for(i = 0; i < 10; i++){
		printf("%d ", a[i]);
	}
	printf("\n");
	return 0;
} 
