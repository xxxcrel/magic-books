#include<stdio.h>
#include"mgraph.h"

int main(int argc, char const *argv[])
{
    MGraph G;
    G = BuildGraph();
    // printf("The Adjacence matrix is:\n");
    // PrintAdjMatrix(Graph);
    // printf("BFS:\n");
    // BFS(Graph, 0);

    // ResetVisitedArray();
    // printf("DFS:\n");
    // DFS(Graph, 0);
    Table T;
    T = CreateTable(G);

    //Unweighted(G, T, 3);
    //Unweighted2(G, T, 3);
    //Dijkstra(G, T, 1);
    Prim(G, T, 1);
    PrintTable(T, G);
    PrintAdjMatrix(G);
    PrintPath(T, 5);
    return 0;
}
