#include<stdio.h>

void ShellSort(int a[], int n)
{
	int i, j, gap;
//	for(gap = n / 2; gap >= 1; gap /= 2){//gap 是步长 
//		for(i = 0; i < gap; i++){//一组有gap个数 
//		//下面其实就是普通插入排序 
//		    for(j = i + gap; j < n; j += gap){
//		    	if(a[j] < a[j-gap]){
//			    	int get = a[j];
//			    	int k = j - gap;
//			    	//get与前面的比较，比它大的往后移  
//				    while(k >= 0 && a[k] > get){
//				    	a[k+gap] = a[k];
//						k -= gap;
//					}
//					a[k+gap] = get;
//				}
//			}
//		}
//	}
//下面是改良版的shell排序
//    for(gap = n / 2; gap > 0; gap /= 2){//gap 是步长 
//	    for(j = gap; j < n; j++){//具体细节查看浏览器笔记 
//	    	if(a[j] < a[j-gap]){
//		    	int get = a[j];
//		    	int k = j - gap;
//		    	//get与前面的比较，比它大的往后移  
//			    while(k >= 0 && a[k] > get){
//			    	a[k+gap] = a[k];
//					k -= gap;
//				}
//				a[k+gap] = get;
//			}
//		}
//	}
//	}	
	
//下面是普通插入排序可做比较 
//	  int j; 
//    for(j = 1; j < n; j++){
//    	int get = a[j];
//    	int k = j - 1;
//    	while(k >= 0 && a[k] > get){
//    		a[k+1] = a[k];
//    		k--;
//    	}
//    	a[k+1] = get;
//    }
}
int main()
{
	int i; 
	int a[] = {3, 4, 2, 5, 6, 7, 9, 8, 1, 0,};
	int n = sizeof(a) / sizeof(int);
	ShellSort(a, n);
	for(i = 0; i < 10; i++){
		printf("%d ", a[i]);
	}
	printf("\n");
	return 0;
}
