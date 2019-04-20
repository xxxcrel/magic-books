#include"hash.h"
#include<stdio.h>
#include<stdlib.h>
int main()
{
	HashTable H;
	ElementType Key;
	int TableSize;

	printf("Please enter the table size：");
	scanf("%d", &TableSize);
	H = InitializeTable(TableSize);
	printf("Really table size is: %d\n", H->TableSize);
	if(H)
		printf("Initialize is ok ！\n");
	printf("Please enter the element and end of -1:\n");
	while(~scanf("%d", &Key) && Key != -1)
	{
		Insert(H, Key);
    }
//    Insert(H, 16);
//    Insert(H, 17);
//    Insert(H, 12);
//    Insert(H, 18);
//    Insert(H, 20);
	PrintHash(H);
	printf("Please enter the element you want delete:\n");
	ElementType Del;
	while(~scanf("%d", &Del) && Del != -1)
	{
		Delete(H, Del);
	}
//	Delete(H, 12);
//	Delete(H, 20);
	PrintHash(H);
	DestroyTable(H);
	return 0;
}
