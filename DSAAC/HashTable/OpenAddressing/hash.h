/*哈希表的开放定址法函数声明*/
#ifndef HASHQUAD_H
#define HASHQUAD_H

typedef int ElementType;
typedef unsigned int Index;
typedef Index Position;

struct HashTbl;
typedef struct HashTbl *HashTable;

enum KindOfEntry{Legitimate, Deleted, Empty};//元素的状态

struct Entry
{
	ElementType Element;
	enum KindOfEntry Info;
};
typedef struct Entry Cell;
struct HashTbl
{
	int TableSize;
	Cell *TheCells;
};

HashTable InitializeTable(int TableSize);
Position Find(HashTable H, ElementType Key);
void Insert(HashTable H, ElementType Key);
void Delete(HashTable H, ElementType Key);
void DestroyTable(HashTable H);
HashTable Rehash(HashTable H);
//hash函数
int Hash(ElementType Key, int TableSize);
void PrintHash(HashTable H);



#endif

