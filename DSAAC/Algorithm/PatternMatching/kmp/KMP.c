#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void getnext(char *p, int *next);
int KMP(char *s, char *p, int *next);

int main()
{
	int pos, next[10];
    char s[100], p[10];
	printf("please enter the main string s:\n");
	gets(s);
	printf("please enter the pattern string p:\n");
	gets(p);
	getnext(p, next);
	int i;
	printf("The string p's next array is:\n");
	for(i = 0; i < strlen(p); i++){
		printf("%d ", next[i]);
	}
	printf("\n");
	pos = KMP(s, p, next);
	printf("%d", pos);
	return 0;
}
//得到next数组
void getnext(char *p, int *next)
{

    int len = strlen(p);//strlen函数计算字符长度不包括\0
    int i = 0;
    int j = -1;
    next[0] = -1;
    while(i < len){
    	if(j == -1 || p[i] == p[j]){
    		next[++i] = ++j;
    	}else{
    		j = next[j];//使用自己之前得到的next数组 递归思想
    	}
    }
}
//KMP算法
int KMP(char *s, char *p, int *next){
	int pos = -1;
	int i = 0;
	int j = 0;
	int slen = strlen(s);
	//printf("slen = %d", slen);
	int plen = strlen(p);
	//printf("plen = %d\n", plen);
	while(i < slen && j < plen){
	    if(j == -1 || s[i] == p[j]){
			i++;
			j++;
			//printf("%d, %d\n", i, j);
		}else{
			j = next[j];
		}
	}
	if(j == plen)
	    pos = i - j;
	return pos;
}
