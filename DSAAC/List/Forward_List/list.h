#ifndef LIST_H
#define LIST_H

typedef char ElementType;

struct Node;
typedef struct Node *PtrToNode;
typedef PtrToNode Position;
typedef PtrToNode List;

struct Node{
	ElementType Element;
	PtrToNode Next;
};

List MakeEmpty(List L);
int IsLast(Position P, List L);
int IsEmpty(List L);
Position FindPrevious(List L, ElementType x);
Position Find(List L, ElementType x);
void Delete(List L, ElementType x);
void Insert(List L, ElementType x, Position P);
void InsertToTail(List L, ElementType x);
void InsertToHead(List L, ElementType x);
void PrintList(List L);
void DeleteList(List L);
void Reverse(List L);

#endif
