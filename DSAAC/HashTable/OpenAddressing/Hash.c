#include "hash.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define MinTableSize 5
#define MaxTableSize 10000

int Hash(ElementType Key, int TableSize)
{
	return Key % TableSize;
}

/*取得TableSize的下一个素数*/
static int NextPrime(int TableSize)
{
	int nextprime, i;
	for (nextprime = TableSize; nextprime < MaxTableSize; nextprime++)
	{
		int IsPrime = 1; //1代表是素数，0代表不是素数
		for (i = 2; i < sqrt(nextprime); i++)
		{
			if (nextprime % i == 0)
			{
				IsPrime = 0;
				break;
			}
		}
		if (IsPrime == 1)
			break;
	}
	//姥姥的方法改进
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
	return nextprime;
}

HashTable InitializeTable(int TableSize)
{
	HashTable H;
	if (TableSize < MinTableSize)
	{
		printf("TableSize is too small!");
		return NULL;
	}
	else
	{
		H = (HashTable)malloc(sizeof(struct HashTbl));
		if (NULL == H)
			printf("Allocation failure!");
		else
		{
			H->TableSize = NextPrime(TableSize);
			H->TheCells = (Cell *)malloc(sizeof(Cell) * H->TableSize); //注意这里与分离链表法的区别
			if (NULL == H->TheCells)
				printf("Allocation failure!");
			else
			{
				int i;
				for (i = 0; i < H->TableSize; i++)
					H->TheCells[i].Info = Empty;
			}
		}
	}

	return H;
}

Position Find(HashTable H, ElementType Key)
{
	Position CurrentPos;
	int ColisionNum = 0;
	CurrentPos = Hash(Key, H->TableSize);
	while (H->TheCells[CurrentPos].Info != Empty && H->TheCells[CurrentPos].Element != Key)
	{
		CurrentPos += 2 * (++ColisionNum) - 1; //平方探测法
		if (CurrentPos >= H->TableSize)
			CurrentPos -= H->TableSize;
	}

	return CurrentPos;
}

void Insert(HashTable H, ElementType Key)
{
	Position Pos;
	Pos = Find(H, Key);
	if (H->TheCells[Pos].Info != Legitimate)
	{
		H->TheCells[Pos].Info = Legitimate;
		H->TheCells[Pos].Element = Key;
	}
}

void Delete(HashTable H, ElementType Key)
{
	Position Pos;
	Pos = Find(H, Key);
	if (H->TheCells[Pos].Info != Legitimate)
		printf("Sorry! This cell is no element or already deleted!"); //当前域内没有插入过要删除的元素或者已经被删除了
	else
		H->TheCells[Pos].Info = Deleted;
}

void DestroyTable(HashTable H)
{
	if (NULL != H)
	{
		free(H->TheCells);
		free(H);
	}
}

void PrintHash(HashTable H)
{
	int i;
	for (i = 0; i < H->TableSize; i++)
	{
		if (H->TheCells[i].Info == Empty || H->TheCells[i].Info == Deleted)
			printf("Empty\n");
		else
			printf("%d\n", H->TheCells[i].Element);
	}
}
