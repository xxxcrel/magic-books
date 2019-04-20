#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "lgraph.h"


static bool Visited[MaxVertexNum] = {false};

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

void Insert(LGraph G, Edge E)
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
        Insert(G, E);
    }
    fclose(fr);
    return G;
}

void Visiting(Vertex v)
{
    printf("Now is visiting:%d\n", v);
}

void DFS(LGraph G, Vertex s)
{
    PtrToAdjVNode NextNode;
    Visiting(s);
    Visited[s] = true;

    for (NextNode = G->AdjList[s].FirstEdge; NextNode; NextNode = NextNode->next)
    {
        if(!Visited[NextNode->v])
            DFS(G, NextNode->v);
    }
}

void BFS(LGraph G, Vertex s)
{
    Vertex currV;
    Queue Q;
    Q = CreatQueue(MaxSize);
    MakeEmpty(Q);

    Visiting(s);
    Visited[s] = true;
    Enqueue(Q, s);
    PtrToAdjVNode adjV;
    while(!IsEmpty(Q))
    {
        printf("------------\n");
        currV = FrontAndDequeue(Q);
        for (adjV = G->AdjList[currV].FirstEdge; adjV; adjV = adjV->next)
        {
            if(!Visited[adjV->v])
            {
                Visiting(adjV->v);
                Visited[adjV->v] = true;
                Enqueue(Q, adjV->v);
            }
        }
    }
    DisposeQueue(Q);
}

void ResetVisitedArray()
{
    for (int i = 0; i < MaxVertexNum; ++i)
        Visited[i] = false;
}
/*-------------上面部分代码用来创建一个图---------------*/
void PrintAdjList(LGraph G)
{
    printf("The Adjacency list is:\n");
    if(NULL == G)
        return;
    for (Vertex v = 0; v < G->Nv; ++v)
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

void PrintWeighted(LGraph G)
{
    PtrToAdjVNode w;
    printf("v-->w  weighted\n");
    for (Vertex v = 0; v < G->Nv; ++v)
    {
        for (w = G->AdjList[v].FirstEdge; w; w = w->next)
        {
            printf("%d-->%d  %d\n", v, w->v, w->weight);
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

void PrintTable(Table T, LGraph G)
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
/*---------这一部分代码用来打印许需要的，方便调试-------*/
//求单源最短路径
void ReadGraphToTable(LGraph G, Table T)
{
    for (Vertex v = 0; v < G->Nv; ++v)
    {
        T[v].header = &G->AdjList[v];
    }
}

Table CreateTable(LGraph G)
{
    Table T = malloc(sizeof(struct TableEntry) * G->Nv);
    if(NULL == T)
        return NULL;
    return T;
}

void InitTable(LGraph G, Table T, Vertex S)
{
    ReadGraphToTable(G, T);
    for (Vertex v = 0; v < G->Nv; ++v)
    {
        T[v].dist = INFINITY;
        T[v].path = 0;
        T[v].known = false;
    }
    T[S].dist = 0;
}
//无权单源最短路径求法(第一种方法)
void Unweighted(LGraph G, Table T, Vertex S)//假设T已经被初始化
{
    Vertex v;
    PtrToAdjVNode adjV;
    InitTable(G, T, S);
    for (DistType currDist = 0; currDist < G->Nv; ++currDist)
        for (v = 1; v < G->Nv; ++v)
            if (!T[v].known && T[v].dist == currDist)
            {
                T[v].known = true;
                for (adjV = T[v].header->FirstEdge; adjV; adjV = adjV->next)
                {
                    if(T[adjV->v].dist == INFINITY)
                    {
                        T[adjV->v].dist = currDist + 1;
                        T[adjV->v].path = v;
                    }
                }
            }
}
//第二种方法(队列)
void Unweighted2(LGraph G, Table T, Vertex S)
{
    Vertex v;
    PtrToAdjVNode adjV;
    Queue Q;
    Q = CreatQueue(G->Nv);
    MakeEmpty(Q);
    InitTable(G, T, S);

    Enqueue(Q, S);
    while(!IsEmpty(Q))
    {
        v = FrontAndDequeue(Q);
        T[v].known = true;//不是必须
        for (adjV = T[v].header->FirstEdge; adjV; adjV = adjV->next)
        {
            if(T[adjV->v].dist == INFINITY)
            {
                T[adjV->v].dist = T[v].dist + 1;
                T[adjV->v].path = v;
                Enqueue(Q, adjV->v);
            }
        }
        //printf("recyle\n");
    }
    DisposeQueue(Q);
}
//有权单源最短路径
Vertex FindMinDist(LGraph G, Table T)
{
    printf("finding.....\n");
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
void Dijkstra(LGraph G, Table T, Vertex S)
{
    InitTable(G, T, S);
    Vertex v;
    PtrToAdjVNode adjV;

    for (;;)
    {
        v = FindMinDist(G, T);
        printf("in Dijkstra algorithm\n");
        printf("minV = %d\n", v);
        if(v == NotAVertex)
            break;
        T[v].known = true;
        for (adjV = G->AdjList[v].FirstEdge; adjV; adjV = adjV->next)
            if(!T[adjV->v].known)
            {
                //当前顶点的dist加上它和该邻接点之间的权重小于它之前的dist时则更新
                if( (T[v].dist + adjV->weight) < T[adjV->v].dist )
                {
                    T[adjV->v].dist = T[v].dist + adjV->weight;
                    T[adjV->v].path = v;
                }
            }
    }
}
/*------------两种最小生成树的算法-------------*/
//运行Prim算法时最好使用无向图，有向图虽然也是有意义的，但是更麻烦
void Prim(LGraph G, Table T, Vertex S)
{
    InitTable(G, T, S);
    Vertex v;
    PtrToAdjVNode adjV;

    for (;;)
    {
        v = FindMinDist(G, T);
        printf("in Prim algorithm\n");
        printf("minV = %d", v);

        if(v == NotAVertex)
            break;
        T[v].known = true;
        for (adjV = G->AdjList[v].FirstEdge; adjV; adjV = adjV->next)
            if(!T[adjV->v].known)
            {
                //当前顶点与该邻接点之间的权重小于它在之前dist时则更新
                if( adjV->weight < T[adjV->v].dist )
                {
                    T[adjV->v].dist = adjV->weight;
                    T[adjV->v].path = v;
                }
            }
    }
}