#include"lgraph.h"
#include"disjset.h"
#include"heap.h"
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
/*
创建一个图时，输入的节点比真实的节点多1个，留零当作哑节点
初始化一个不相交集合时，也比真实节点多1个
很多细节在图的顶点个数与其它数据结构的耦合
具体在各个函数的循环中体现
*/
LGraph CreateGraph(int NumVertex)
{
    LGraph G = (LGraph)malloc(sizeof(struct LGraphRecord));
    if (NULL == G)
        return NULL;
    G->Nv = NumVertex;
    G->Ne = 0;
    G->AdjList = (List)malloc(sizeof(struct VertexNode) * G->Nv);
    if (NULL == G->AdjList)
        return NULL;
    for (int i = 0; i < G->Nv; ++i)
    {
        G->AdjList[i].FirstEdge = NULL;
    }
    //printf("Create successful\n");
    return G;
}

void InsertEdge(LGraph G, Edge E)
{
    //均采用头插法
    PtrToAdjVNode NewNode;
    NewNode = malloc(sizeof(struct AdjVertexNode));
    if (NULL == NewNode)
        return;
    NewNode->v = E->w;
    NewNode->weight = E->weight;
    NewNode->next = G->AdjList[E->v].FirstEdge;
    G->AdjList[E->v].FirstEdge = NewNode;

    //当图是一个无向图时，每一个边需放入两个连接表中
    NewNode = malloc(sizeof(struct AdjVertexNode));
    if (NULL == NewNode)
        return;
    NewNode->v = E->v;
    NewNode->weight = E->weight;
    NewNode->next = G->AdjList[E->w].FirstEdge;
    G->AdjList[E->w].FirstEdge = NewNode;
}

LGraph BuildGraph()
{
    LGraph G;
    int VertexNum;
    printf("Enter the Vertex number:");
    //输入顶点要多于实际顶点一个，避免后续算法的误差，即抛弃0位置
    scanf("%d", &VertexNum);
    G = CreateGraph(VertexNum);
    printf("Eneter the Edge number:");
    scanf("%d", &G->Ne);
    Edge E;
    E = malloc(sizeof(struct EdgeNode));
    if(E == NULL)
        printf("alloc failed\n");
    FILE *fr = fopen("graph.txt", "r");
    if(fr == NULL)
        printf("fopen failed\n");
    for (int e = 0; e < G->Ne; ++e)
    {
        fscanf(fr, "%d %d %d", &E->v, &E->w, &E->weight);
        //printf("fsanf succeccful\n");
        InsertEdge(G, E);
    }
    fclose(fr);
    return G;
}
void ReadGraphIntoHeapArray(LGraph G, PriorityQueue H)
{
    Edge E;
    Vertex v;
    PtrToAdjVNode w;
    for (v = 1; v <= G->Nv - 1; ++v)
        for (w = G->AdjList[v].FirstEdge; w; w = w->next)
            if(v < w->v)//防止无向图的重复边被录入
            {
                E = malloc(sizeof(struct EdgeNode));
                if(NULL == E)
                    return;
                E->v = v;
                E->w = w->v;
                E->weight = w->weight;
                // printf("%p\n", E);
                // printf("v = %d, w = %d, weight = %d\n", E->v, E->w, E->weight);
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
void OutSpace(int SpaceOnFront)
{
	for(int i = 0; i < pow(2, SpaceOnFront); i++)
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
		LineStart = pow(2, Line);
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
void PrintAdjList(LGraph G)
{
    printf("The MST is:\n");
    if(NULL == G)
        return;
    for (Vertex v = 1; v < G->Nv; ++v)
    {
        printf("%d", v);
        PtrToAdjVNode last = G->AdjList[v].FirstEdge;
        while(last)
        {
            printf("-->%d", last->v);
            last = last->next;
        }
        printf("\n");
    }
}
int Kruskal(LGraph G, LGraph MST)
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
    PrintAdjList(MST);
    return totalWeight;
    //printf("Finally the Set:\n");
    //PrintSet(S);
}