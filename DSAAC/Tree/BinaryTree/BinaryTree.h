#ifndef TREE_H
#define TREE_H

typedef char TreeElementType;

typedef struct TreeNode *PtrToNode;
typedef PtrToNode BinTree;

struct TreeNode
{
	TreeElementType Element;
	struct TreeNode *Left;
	struct TreeNode *Right;
};

BinTree CreateTree();		   //先序遍历创建二叉树
BinTree IterationCreateTree(); //先序非递归创建二叉树

void PreOrderTraversal(BinTree BT);
void IterationPreOrderTraversal(BinTree BT);

void InOrderTraversal(BinTree BT);
void IterationInOrderTraversal(BinTree BT);

void PostOrderTraversal(BinTree BT);
void IterationPostOrderTraversal(BinTree BT);

void LevelTraversal(BinTree BT);

int SumNode(BinTree BT);
int SumLeafNode(BinTree BT);
int Depth(BinTree BT); //输出整个二叉树的深度

#endif
