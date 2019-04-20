//朴素模式配对法
#include<stdio.h>
#include<string.h>

int Index(char *s, char *p);

int main()
{
    char s[100], p[100];
	int pos;
	printf("please input main string:\n");
	gets(s);
	printf("please input model string:\n");
	gets(p);
	pos = Index(s, p);
	printf("%d\n", pos);
	return 0;
}
int Index(char *s, char *p)
{
	int i = 0;
	int j = 0;
	int slen = strlen(s);
	int plen = strlen(p);
	while(i < slen && j < plen){
		if(s[i] == p[j]){
			i++;
			j++;
		}else{
			i = i - j + 1;
			j = 0;
		}
	}
	/*匹配成功*/
    if(j == plen){
    	return i - j;//如果改成 i-j+1的话自己数的时候按正常123数 i-j是按012数的
    }else{
    	return -1;
    }
}
