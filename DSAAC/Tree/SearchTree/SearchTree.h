#ifndef SERACH_TREE
#define SERACH_TREE

typedef char ElementType;
struct TreeNode;
typedef struct TreeNode *Position;
typedef Position SearchTree;

struct TreeNode{
	ElementType Element;
	Position Left;
	Position Right;
};

SearchTree MakeEmpty(SearchTree T);
Position Find(SearchTree T, ElementType X);
Position FindMin(SearchTree T);
Position FindMax(SearchTree T);
SearchTree Insert(SearchTree T, ElementType X);
SearchTree Delete(SearchTree T, ElementType X);

#endif
