#ifndef AVL_H
#define AVL_H

typedef char ElementType;
struct AvlNode;
typedef struct AvlNode *Position;
typedef Position AvlTree;

struct AvlNode
{
	ElementType Element;
	Position Left;
	Position Right;
	int Height;
};

AvlTree MakeEmpty(AvlTree T);
Position Find(AvlTree T, ElementType X);
Position FindMin(AvlTree T);
Position FindMax(AvlTree T);
AvlTree Insert(AvlTree T, ElementType X);
AvlTree Delete(AvlTree T, ElementType X);

#endif
