/*哈希表的分离链表法的函数声明*/
#ifndef HASHSEP_H
#define HASHSEP_H

typedef int ElementType;
struct ListNode;
typedef struct ListNode *Position;
typedef struct ListNode *List;

struct HashTbl;
typedef struct HashTbl *HashTable;

struct ListNode
{
	ElementType Element;
	struct ListNode *Next;
};

struct HashTbl
{
	int TableSize;
	List *TheLists;//TheLists 实际上是一个指向struct ListNode结构体的指针的指针
};

HashTable InitializeTable(int TableSize);
void MakeEmpty(HashTable H);
Position Find(HashTable H, ElementType Key);
void Insert(HashTable H, ElementType Key);
void Delete(HashTable H, ElementType Key);
void DestroyTable(HashTable H);
void PrintHash(HashTable H);

int Hash(ElementType Key, int TableSize);
#endif
