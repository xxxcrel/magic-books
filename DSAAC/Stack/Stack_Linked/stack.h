/*栈———链表实现申明*/
#ifndef STACK_H
#define STACK_H

typedef char ElementType;
struct Node;
typedef struct Node *PtrToNode;
typedef PtrToNode Stack;

struct Node{
	ElementType Element;
	PtrToNode Next;
};

int IsEmpty(Stack S);
Stack CreatStack();
void MakeEmpty(Stack S);
void DiseposeStack(Stack S);
void Push(Stack S, ElementType X);
void Pop(Stack S);
ElementType Top(Stack S);
ElementType PopAndTop(Stack S);

#endif
