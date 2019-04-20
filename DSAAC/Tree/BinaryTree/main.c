#include "binarytree.h"
#include "queue.h"
#include "stack.h"
// #include "Stack.c"
// #include "Queue.c"
// #include "Tree.c"
#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[])
{
	BinTree BT;
	printf("Please enter tree element like as:abc00d00gh00t00:");
	BT = CreateTree();
	//BT = IterationCreateTree();

	printf("先序遍历(递归)：\t");
	PreOrderTraversal(BT);
	printf("\n");
	printf("先序遍历(迭代)：\t");
	IterationPreOrderTraversal(BT);
	printf("\n\n");

	printf("中序遍历(递归)：\t");
	InOrderTraversal(BT);
	printf("\n");
	printf("中序遍历(迭代)：\t");
	IterationInOrderTraversal(BT);
	printf("\n\n");

	printf("后序遍历(递归)：\t");
	PostOrderTraversal(BT);
	printf("\n");
	printf("后序遍历(迭代)：\t");
	IterationPostOrderTraversal(BT);
	printf("\n\n");

	printf("层次遍历(迭代)：\t");
	LevelTraversal(BT);
	printf("\n\n");

	int allnode, leafnode, treedepth;
	allnode = SumNode(BT);
	leafnode = SumLeafNode(BT);
	treedepth = Depth(BT);
	printf("二叉树结点总数：%d\t\n", allnode);
	printf("二叉树叶节点总数：%d\t\n", leafnode);
	printf("二叉树深度：%d\t\n", treedepth); //输出整棵树的深度
	printf("\n");

	return 0;
}
