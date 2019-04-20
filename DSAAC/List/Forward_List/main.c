#include"list.h"
#include<stdio.h>
#include<stdlib.h>

int main()
{
	ElementType Elem, De, PreElem, Ins;
	Position Tmp;
	List L;
	L = (List)malloc(sizeof(struct Node));
	if(NULL == L)
		printf("Allocation failure!!!");
	L = MakeEmpty(L);
	printf("Please enter the element until the end of '#':");
	while((Elem = getchar()) != '#')
	{
		InsertToTail(L, Elem);
	}
	getchar();
	PrintList(L);
	//删除并输出
    printf("Please enter the element you want to delete:");
    scanf("%c", &De);
    getchar();

    Delete(L, De);
    PrintList(L);
    //插入并输出
    printf("After which element do you want to insert:");
    scanf("%c", &PreElem);
    getchar();
    Tmp = Find(L, PreElem);

    printf("What element do you want to insert:");
    scanf("%c", &Ins);
    getchar();

    Insert(L, Ins, Tmp);
    PrintList(L);
    //将整个表倒置
	Reverse(L);
	printf("Now the reverse list is:");
	PrintList(L);
    //删除整个表
	DeleteList(L);
	return 0;
}

