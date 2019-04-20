#ifndef _LGRAPH_H
#define _LGRAPH_H
#include <stdbool.h>

#define INFINITY 65536
#define MaxVertexNum 100
#define MaxSize 100

typedef int Vertex;
typedef int WeightType;
typedef char DataType;

//definition adjacency vertex node
typedef struct AdjVertexNode *PtrToAdjVNode;
struct AdjVertexNode
{
    Vertex v;
    WeightType weight;
    PtrToAdjVNode next;
};

typedef struct VertexNode *PtrToVNode;
struct VertexNode
{
    DataType data;
    PtrToAdjVNode FirstEdge;
};
typedef PtrToVNode List;

struct EdgeNode
{
    Vertex v;
    Vertex w;
    WeightType weight;
};
typedef struct EdgeNode *Edge;

struct LGraphRecord
{
    int Nv;
    int Ne;
    List AdjList;
};
typedef struct LGraphRecord *LGraph;

//创建一个图
LGraph CreateGraph(int NumVertex);
void Insert(LGraph G, Edge E);
LGraph BuildGraph();

//两种遍历
void Visiting(Vertex v);
void DFS(LGraph G, Vertex s);
void BFS(LGraph G, Vertex s);
void ResetVisitedArray();


#endif	// _LGRA

//求最短路径和最小生成树需要的表条目
#ifndef _TABLE_
#define _TABLE_
typedef int DistType;

struct TableEntry
{
    List header;
    DistType dist;
    Vertex path;
    bool known;
};
typedef struct TableEntry *Table;

#define NotAVertex (-1)

//各种打印函数
void PrintAdjList(LGraph G);
void PrintPath(Table T, Vertex v);
void PrintTable(Table T, LGraph G);
void PrintWeighted(LGraph G);

void ReadGraphToTable(LGraph G, Table T);
Table CreateTable(LGraph G);
void InitTable(LGraph G, Table T, Vertex S);
Vertex FindMinDist(LGraph G, Table T);

//单源最短路径算法
void Unweighted(LGraph G, Table T, Vertex S);
void Unweighted2(LGraph G, Table T, Vertex S);
void Dijkstra(LGraph G, Table T, Vertex S);

//最小生成树算法
void Prim(LGraph G, Table T, Vertex S);
#endif	// _TABLE_