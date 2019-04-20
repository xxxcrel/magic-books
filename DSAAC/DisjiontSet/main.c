#include<stdio.h>
#include"disjset.h"

int main(int argc, char const *argv[])
{
    DisjSet S;
    InitializeSet(S);
    SetUnion(S, 3, 5);
    SetUnion(S, 4, 8);
    SetUnion(S, 2, 4);
    SetUnion(S, 1, 3);
    SetUnion(S, 3, 4);
    PrintSet(S);
    Find(S, 8);
    PrintSet(S);
    return 0;
}