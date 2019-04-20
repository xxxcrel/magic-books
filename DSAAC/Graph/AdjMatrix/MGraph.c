#include "mgraph.h"
#include "queue.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool Visited[MaxVertexNum] = {false};

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

void Insert(MGraph G, Edge E)
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
            Insert(G, E);
        }
    }
    fclose(fr);
    //如果顶点有数据则输入
    // for (int i = 0; i < G->Nv; ++i)
    //     scanf("Enter the vertex's data:%d", G->Data[i]);

    return G;
}

void Visiting(Vertex v)
{
    printf("Now is visiting vertex:%d\n", v);
}
//从顶点v开始进行深度优先遍历
void DFS(MGraph G, Vertex s)
{
    Visiting(s);
    Visited[s] = true;
    for (Vertex w = 0; w < G->Nv; ++w)
        if (G->Matrix[s][w])
            if (!Visited[w])
                DFS(G, w);
}
bool IsEdge(MGraph G, Vertex v, Vertex w)
{
    return G->Matrix[v][w] == INFINITY ? false : true;
}
//从顶点v开始进行广度优先遍历
void BFS(MGraph G, Vertex s)
{
    Queue Q;
    Q = CreatQueue(MaxSize);
    MakeEmpty(Q);

    Visiting(s);
    Visited[s] = true;
    Enqueue(Q, s);
    Vertex v; //暂存从队列弹出的顶点
    while (!IsEmpty(Q))
    {
        printf("----------------\n");
        v = FrontAndDequeue(Q);
        for (Vertex w = 0; w < G->Nv; ++w)
        {
            if (!Visited[w] && IsEdge(G, v, w))
            {
                Visiting(w);
                Visited[w] = true;
                Enqueue(Q, w);
            }
        }
    }
    DisposeQueue(Q);
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

void PrintWeighted(MGraph G)
{
    Vertex w;
    printf("v-->w  weighted\n");
    for (Vertex v = 0; v < G->Nv; ++v)
    {
        for (w = 0; w < G->Nv; ++w)
        {
            if(G->Matrix[v][w] != INFINITY)
                printf("%d-->%d  %d\n", v, w, G->Matrix[v][w]);
        }
    }
}
//选定顶点v打印出到s(已经运行了其中一个最短路径算法)的单源最短路径
void PrintPath(Table T, Vertex v)
{
    if(T[v].path != 0)
    {
        PrintPath(T, T[v].path);
        printf("->");
    }
    printf("%d", v);
}

void PrintTable(Table T, MGraph G)
{
    printf("The TableEntry is:\n");
    printf("_______________________\n");
    printf("| v |known| dist| path|\n");
    printf("-----------------------\n");
    for (int cnt = 0; cnt < G->Nv; ++cnt)
    {
        printf("| %d |", cnt);
        printf("  %d  |", T[cnt].known);
        printf(T[cnt].dist == INFINITY ? "  ∞  |" : "  %d  |", T[cnt].dist);
        printf("  %d  |\n", T[cnt].path);
    }
    printf("-----------------------\n");
}
void ResetVisitedArray()
{
    for (int i = 0; i < MaxVertexNum; ++i)
        Visited[i] = false;
}

Table CreateTable(MGraph G)
{
    Table T = malloc(sizeof(struct TableEntry) * G->Nv);
    if(NULL == T)
        return NULL;
    return T;
}
void InitTable(MGraph G, Table T, Vertex S)
{
    for (Vertex v = 0; v < G->Nv; ++v)
    {
        T[v].known = false;
        T[v].dist = INFINITY;
        T[v].path = 0;
    }
    T[S].dist = 0;
}
//求单源最短路径的两种算法（无权）

void Unweighted(MGraph G, Table T, Vertex S)
{
    InitTable(G, T, S);

    for (DistType currDist = 0; currDist < G->Nv; ++currDist)
        for (Vertex v = 1; v < G->Nv; ++v)
            if (!T[v].known && T[v].dist == currDist)
            {
                T[v].known = true;
                //for循环加if判断用来寻找v的邻接点中未被标记的
                for (Vertex w = 1; w < G->Nv; ++w)
                    if(G->Matrix[v][w] != INFINITY && T[w].dist == INFINITY)
                    {
                        T[w].dist = currDist + 1;
                        T[w].path = v;
                    }
            }
}

void Unweighted2(MGraph G, Table T, Vertex S)
{
    Vertex v;
    InitTable(G, T, S);
    Queue Q;
    Q = CreatQueue(G->Nv);
    MakeEmpty(Q);

    Enqueue(Q, S);
    while(!IsEmpty(Q))
    {
        v = FrontAndDequeue(Q);
        //T[v].known = true;
        for (Vertex w = 1; w < G->Nv; ++w)
            if(G->Matrix[v][w] != INFINITY && T[w].dist == INFINITY)
            {
                T[w].dist = T[v].dist + 1;
                T[w].path = v;
                Enqueue(Q, w);
            }
    }
    DisposeQueue(Q);
}

Vertex FindMinDist(MGraph G, Table T)
{
    printf("MinDistFinding.....\n");
    Vertex minV, minDist = INFINITY;
    for (Vertex v = 1; v < G->Nv; ++v)
    {
        if(!T[v].known && T[v].dist < minDist)
        {
            minDist = T[v].dist;
            minV = v;
        }
    }
    if(minDist != INFINITY)
        return minV;//找到最小的Unknown的顶点
    else
        return NotAVertex;//已经遍历完
}

void Dijkstra(MGraph G, Table T, Vertex S)
{
    InitTable(G, T, S);
    Vertex v;

    for (;;)
    {
        v = FindMinDist(G, T);
        printf("in Dijkstra algorithm\n");
        printf("minV = %d\n", v);
        T[v].known = true;
        if(v == NotAVertex)
            break;
        for (Vertex w = 1; w < G->Nv; ++w)
            if(G->Matrix[v][w] != INFINITY && !T[w].known)
            {
                if((T[v].dist + G->Matrix[v][w]) < T[w].dist)
                {
                    T[w].dist = T[v].dist + G->Matrix[v][w];
                    T[w].path = v;
                }
            }
    }
}

void Prim(MGraph G, Table T, Vertex S)
{
    InitTable(G, T, S);
    Vertex v;

    for (;;)
    {
        v = FindMinDist(G, T);
        printf("in Prim algorithm\n");
        printf("minV = %d\n", v);
        T[v].known = true;
        if(v == NotAVertex)
            break;
        for (Vertex w = 1; w < G->Nv; ++w)
            if(G->Matrix[v][w] != INFINITY && !T[w].known)
            {
                if(G->Matrix[v][w] < T[w].dist)
                {
                    T[w].dist = G->Matrix[v][w];
                    T[w].path = v;
                }
            }
    }
}