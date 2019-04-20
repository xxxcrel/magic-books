#include<stdio.h>
#include<stdlib.h>

void merge(int a[], int left, int mid, int right)
{
	int index = 0;//暂借的数组的起始下标 
    int start1 = left;//前一个小分组的起始下标 
    int end1 = mid;//前一个小分组的末下标 
	int start2 = mid + 1;//后一个小分组的起始下标
	int end2 = right;//后一个小分组的末下标
	int len = right - left + 1;
    int *temp = (int*)malloc(sizeof(int) * len);
	while(start1 <= end1 && start2 <= end2){
	    if(a[start1] <= a[start2])
		    temp[index++] = a[start1++];
		else
		    temp[index++] = a[start2++];
	}
	//将小分组剩下的元素放入temp里 
	while(start1 <= end1){
		temp[index++] = a[start1++];
	}
	while(start2 <= end2){
		temp[index++] = a[start2++];
	}
	//下面将temp里的数复制到a里面
	int k;
	for(k = 0; k < len; k++){
	    a[left++] = temp[k];
	}
	free(temp);
}
//void MergeSort(int a[], int n)//非递归方法 
//{
//	int i, left, right, mid;
//	for(i = 1; i < n; i *= 2){//最开始每组只有1个成员 以2倍递增 
//	    int left = 0;
//		while(left + i <= n){//后一个子数组存在 需要合并 
//			mid = left + i - 1;
//			right = (mid + i < n) ? mid + i : n - 1;
//			merge(a, left, mid, right);
//			left = right + 1;//合并下一个分好的数组 
//		}
//	}
//}
//int main()
//{
//	int i; 
//    int a[] = {3, 4, 2, 5, 6, 7, 9, 8, 1, 0,};
//	int n = sizeof(a) / sizeof(int);
//	MergeSort(a, n);
//	for(i = 0; i < 10; i++){
//		printf("%d ", a[i]);
//	}
//	printf("\n");
//	return 0;
//} 
//下面是递归实现方法 
void MergeSort(int a[], int left, int right)
{
	if(left == right)
	    return;
	else{
		int mid = (left + right) / 2;
		MergeSort(a, left, mid);
		MergeSort(a, mid + 1, right);
		merge(a, left, mid, right);
	}
}
int main()
{
	int i; 
    int a[] = {3, 4, 2, 5, 6, 7, 9, 8, 1, 0,};
	int n = sizeof(a) / sizeof(int);
	MergeSort(a, 0, n - 1);
	for(i = 0; i < 10; i++){
		printf("%d ", a[i]);
	}
	printf("\n");
	return 0;
} 

