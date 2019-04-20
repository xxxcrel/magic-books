#ifndef _DISJIONT_H
#define _DISJIONT_H

#define NumSets 10
typedef int SetType;
typedef int DisjSet[NumSets + 1];
typedef int ElementType;

void InitializeSet(DisjSet S);
void SetUnion(DisjSet S, SetType Root1, SetType Root2);
SetType Find(DisjSet S, ElementType X);
void PrintSet(DisjSet S);

#endif	// _DISJIONT_H