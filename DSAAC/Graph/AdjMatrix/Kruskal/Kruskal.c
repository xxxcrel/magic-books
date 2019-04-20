#include "mgraph.h"
#include "heap.h"
#include "disjset.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

MGraph CreateGraph(int vertexNum)
{
    MGraph G;
    G = malloc(sizeof(struct GraphRecord));
    if (NULL == G)
        return NULL;
    G->Nv = vertexNum;
    G->Ne = 0;
    for (Vertex v = 0; v < G->Nv; ++v)
        for (Vertex w = 0; w < G->Nv; ++w)
            G->Matrix[v][w] = INFINITY;
    return G;
}

void InsertEdge(MGraph G, Edge E)
{
    G->Matrix[E->v][E->w] = E->weight;
    //无向图需要下面的代码
    G->Matrix[E->w][E->v] = E->weight;
}

MGraph BuildGraph()
{
    int vertexNum;
    printf("Enter the vertex number:");
    scanf("%d", &vertexNum);
    MGraph G = CreateGraph(vertexNum);

    printf("Enter the edge number:");
    scanf("%d", &G->Ne);
    Edge E;
    FILE *fr = fopen("graph.txt", "r");
    if (G->Ne != 0)
    {
        E = malloc(sizeof(struct EdgeNode));
        for (int i = 0; i < G->Ne; ++i)
        {
            fscanf(fr, "%d %d %d", &E->v, &E->w, &E->weight);
            InsertEdge(G, E);
        }
    }
    fclose(fr);
    //如果顶点有数据则输入
    // for (int i = 0; i < G->Nv; ++i)
    //     scanf("Enter the vertex's data:%d", G->Data[i]);
    return G;
}
void ReadGraphIntoHeapArray(MGraph G, PriorityQueue H)
{
    Edge E;
    for (Vertex v = 1; v <= G->Nv - 1; ++v)
        for (Vertex w = 1; w <= G->Nv - 1; ++w)
            if(G->Matrix[v][w] != INFINITY)
                if(v < w)//防止无向图的重复边被录入
                {
                    E = malloc(sizeof(struct EdgeNode));
                    if(NULL == E)
                        return;
                    E->v = v;
                    E->w = w;
                    E->weight = G->Matrix[v][w];
                    printf("%p\n", E);
                    printf("v = %d, w = %d, weight = %d\n", E->v, E->w, E->weight);
                    H->Elements[++H->Size] = E;
                }
    // printf("over\n");
}
void PrintHastTable(PriorityQueue H)
{
    for (int i = 1; i <= H->Size; ++i)
    {
        printf("%d-->%3d\n", i, H->Elements[i]->weight);
        //printf("PrintHashing\n");
    }
}

int Power(int X, int N)
{
    if(N == 0)
        return 1;
    if(N == 1)
        return X;
    else if(N % 2 != 0)
        return X * Power(X * X, N / 2);
    else
        return Power(X * X, N / 2);
}
void OutSpace(int SpaceOnFront)
{
	for(int i = 0; i < Power(2, SpaceOnFront); i++)
		printf(" ");
	printf("\b");
}
void PrintHeap(PriorityQueue H)
{
	int LineStart, LineEnd, Depth = 0;
    //计算该堆的深度，从1开始计数
	for(int i = 1; i <= H->Size; i *= 2)
		Depth++;
	int SpaceOnFront = Depth - 1;
	int Interal = Depth;
	for(int Line = 0; Line < Depth; Line++)
	{
		OutSpace(SpaceOnFront);
		LineStart = Power(2, Line);
		LineEnd = LineStart * 2;
		for(int i = LineStart; i < LineEnd; i++)
		{
			if(i <= H->Size)
			{
				printf("%d", H->Elements[i]->weight);
				OutSpace(Interal);
			}
		}
		printf("\n");
		SpaceOnFront--;
		Interal--;
	}
}
void PrintAdjMatrix(MGraph G)
{
    printf("  0  1  2  3  4  5  6  7\n");
    for (int i = 0; i < G->Nv; ++i)
    {
        printf("%d ", i);
        for (int j = 0; j < G->Nv; ++j)
            printf(G->Matrix[i][j] == INFINITY ? "∞  " : "%d  ", G->Matrix[i][j]);
        printf("\n");
    }
}
int Kruskal(MGraph G, MGraph MST)
{
    MST = CreateGraph(G->Nv);
    WeightType totalWeight = 0;
    Edge E;
    DisjSet S;
    InitializeSet(S);
   // PrintSet(S);

    PriorityQueue H;
    H = Initialize(G->Ne);
    ReadGraphIntoHeapArray(G, H);
    BuildHeap(H);
    printf("After BuildHeap:\n");
    PrintHeap(H);
    //printf("----------------------------\n");
    SetType Vset, Wset;
    int EdgesAccepted = 0;
    while(EdgesAccepted < G->Nv - 2)//最小生成树的边数等于顶点数|v|-1
    {
        E = DeleteMin(H);
       // printf("After DeleteMin->%d(%d, %d):\n", E->weight, E->v, E->w);
       // PrintHeap(H);
        Vset = Find(S, E->v);
        Wset = Find(S, E->w);
       // printf("Vset = %d, Wset = %d\n", Vset, Wset);
        if(Vset != Wset)
        {
            totalWeight += E->weight;
            InsertEdge(MST, E);
            ++EdgesAccepted;
            SetUnion(S, Vset, Wset);
        }
        //PrintSet(S);
        //printf("________________________\n");
    }
    PrintAdjMatrix(MST);
    return totalWeight;
    //printf("Finally the Set:\n");
    //PrintSet(S);
}

