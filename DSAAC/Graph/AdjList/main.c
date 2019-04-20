#include<stdio.h>
#include"lgraph.h"

int main(int argc, char const *argv[])
{
    printf(" ∞");
    LGraph G;
    G = BuildGraph();
    // printf("DFS:\n");
    // DFS(G, 0);
    // ResetVisitedArray();
    // printf("BFS:\n");
    // BFS(G, 0);
    PrintAdjList(G);
    Table T;
    T = CreateTable(G);
    InitTable(G, T, 2);
    //Unweighted(G, T, 0);
    //Unweighted2(G, T, 0);
    //Dijkstra(G, T, 1);
    Prim(G, T, 1);
    PrintTable(T, G);
    PrintWeighted(G);
    PrintPath(T, 5);
    return 0;
}
