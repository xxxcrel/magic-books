/*哈希表的分离链表法的操作函数*/
#include"hash.h"
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define MinTableSize 5
#define MaxTableSize 100000

int Hash(ElementType Key, int TableSize)
{
	return Key % TableSize;
}

/*取得TableSize的下一个素数*/
static int NextPrime(int TableSize)
{
	int nextprime, i;
	for(nextprime = TableSize; nextprime < MaxTableSize;nextprime++)
	{
		int IsPrime = 1;//1代表是素数，0代表不是素数
		for(i = 2; i < sqrt(nextprime); i++)
		{
			if(nextprime % i == 0)
			{
				IsPrime = 0;
				break;
			}
		}
		if(IsPrime == 1)
			break;
	}
	return nextprime;
}
	//陈越姥姥的方法改进
//	nextprime = (TableSize % 2) ? TableSize + 2 : TableSize + 1;//从大于TableSize的下一个奇数开始
//	for(; nextprime < MaxTableSize; nextprim += 2)
//	{
//		for(i = 2; i < sqrt(nextprime); i++)
//		{
//			if(nextprime % i == 0)
//			{
//				IsPrime = 0;
//				break;
//            }
//		}
//		if(IsPrime == 1)
//			return nextprime;
//	}



HashTable InitializeTable(int TableSize)
{
	HashTable H;
	int i;

	if(TableSize < MinTableSize)
    {
		printf("Table size is too small!");
		return NULL;
    }

	H = (HashTable)malloc(sizeof(struct HashTbl));
	if(NULL == H)
		printf("Allocation failure!");
	else
	{
		H->TableSize = NextPrime(TableSize);//取得下一个素数并设为表大小

		H->TheLists = (List*)malloc(sizeof(List) * H->TableSize);//申请的是TableSize个list指针的空间
		if(NULL == H->TheLists)
			printf("Allocation failure!");
		else
		{
			for(i = 0; i < H->TableSize; i++)
			{
				H->TheLists[i] = (List)malloc(sizeof(struct ListNode));
				if(NULL == H->TheLists[i])
					printf("Allocation failure!");
				else
					H->TheLists[i]->Next = NULL;
			}
		}
        /*下面是书上的另一种写法,目前实现不了*/
//        H->TheLists = (List*)malloc(sizeof(struct ListNode) * H->TableSize);
//        if(NULL == H->TheLists)
//			printf("Allocation failure!");
//		else
//		{
//			for(i = 0; i < H->TableSize; i++)
//			{
//				H->TheLists[i]->Next = NULL;
//			}
//		}
	}

	return H;
}

Position Find(HashTable H, ElementType Key)
{
	List L;
	Position P;
	L = H->TheLists[Hash(Key, H->TableSize)];//取得含有当前关键字的链表头结点（哑元结点）
	P = L->Next;
	while(P != NULL && P->Element != Key)
	{
		P = P->Next;
	}
	return P;
}

void Insert(HashTable H, ElementType Key)
{
	List L;
	Position P, NewCell;
	P = Find(H, Key);

	if(NULL == P)    /*X is not found*/
	{
		NewCell = (List)malloc(sizeof(struct ListNode));
		if(NULL == NewCell)
			printf("Allocatin failure!");
		else
		{
			L = H->TheLists[Hash(Key, H->TableSize)];
			NewCell->Element = Key;
			/*插入到头节点后，这样更方便，往往也利于删除操作*/
			NewCell->Next = L->Next;
			L->Next = NewCell;
		}
	}
}

void Delete(HashTable H, ElementType Key)
{
	List L;
	Position P, Previous, TmpCell;
	P = Find(H, Key);
	if(NULL == P)
		printf("Sorry Key is not in the Table!");
	else
	{
		L = H->TheLists[Hash(Key, H->TableSize)];
		Previous = L;
		while(Previous->Next != P)
		{
			Previous = Previous->Next;//寻找删除结点的前驱
		}
		TmpCell = Previous->Next;
		Previous->Next = Previous->Next->Next;
		free(TmpCell);
	}
}

void DestroyTable(HashTable H)
{
	int i;
	Position TmpCell, NextCell;
	if(NULL != H)
	{
		for(i = 0; i < H->TableSize; i++)
		{
			TmpCell = H->TheLists[i];

			while(TmpCell != NULL)
			{
				NextCell = TmpCell->Next;
				free(TmpCell);
				TmpCell = NextCell;
			}
		}
		free(H->TheLists);
		free(H);
	}
}

void PrintHash(HashTable H)
{
	Position TmpCell;
	int i;
	for(i = 0; i < H->TableSize; i++)
	{
		printf("%d:\thead->", i);
		TmpCell = H->TheLists[i]->Next;
		if(NULL == TmpCell)
			printf("NULL\n");
		else
		{
			while(TmpCell->Next != NULL)
			{
				printf("%d->", TmpCell->Element);
				TmpCell = TmpCell->Next;
			}
			printf("%d\n", TmpCell->Element);
		}
	}
}
