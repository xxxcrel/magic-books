#include"cursor.h"
#include<stdio.h>
#include"CursorSpace.c"

int main()
{
	InitializeCursorSpace();
	ElementType Elem, De, PreElem, Ins;
	Position Tmp;
	List L;
	L = CursorAlloc();
	if(L == 0)
		printf("No space for Allocation");
	L = MakeEmpty(L);
	printf("Please enter the element and end of #:\n");
	while((Elem = getchar()) != '#')
	{
		InsertToTail(L, Elem);
	}
	getchar();
	PrintList(L);

	printf("Please enter the element you want delete:");
	scanf("%c", &De);
	getchar();
	Delete(L, De);
	PrintList(L);

	printf("Please enter exist element you want insert into:");
	scanf("%c", &PreElem);
	getchar();
	Tmp = Find(L, PreElem);

	printf("And the element is:");
	scanf("%c", &Ins);
	Insert(L, Ins, Tmp);
	PrintList(L);

	return 0;
}
