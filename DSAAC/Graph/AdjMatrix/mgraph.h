#ifndef _MGRAPH_H
#define _MGRAPH_H
#include<stdbool.h>

#define MaxVertexNum 100 //矩阵最大的行和列
#define INFINITY 65535 //一个字的最大表示
#define MaxSize 100//用于BFS创建的队列
typedef int Vertex;
typedef int WeightType;
typedef char DataType;

typedef struct EdgeNode *PtrToENode;
struct EdgeNode
{
    Vertex v;
    Vertex w;
    WeightType weight;
};
typedef PtrToENode Edge;

typedef struct GraphRecord *PtrToGRecord;
struct GraphRecord
{
    int Nv;
    int Ne;
    WeightType Matrix[MaxVertexNum][MaxVertexNum];
    DataType Data[MaxVertexNum];
};
typedef PtrToGRecord MGraph;

MGraph CreateGraph(int vertexNum);
void Insert(MGraph G, Edge E);
MGraph BuildGraph();
void Visiting(Vertex v);
bool IsEdge(MGraph G, Vertex v, Vertex w);
void BFS(MGraph G, Vertex s);
void DFS(MGraph G, Vertex s);
void ResetVisitedArray();

#endif

//求最短路径和最小生成树需要的表条目
#ifndef _TABLE_
#define _TABLE_
typedef int DistType;//相对意义上的路径类型，这里指相对距离

struct TableEntry
{
    DistType dist;
    Vertex path;
    bool known;
};
typedef struct TableEntry *Table;

#define NotAVertex (-1)

//各种打印函数
void PrintAdjMatrix(MGraph G);
void PrintPath(Table T, Vertex v);
void PrintTable(Table T, MGraph G);
void PrintWeighted(MGraph G);

Table CreateTable(MGraph G);
void InitTable(MGraph G, Table T, Vertex S);
Vertex FindMinDist(MGraph G, Table T);

//单源最短路径算法
void Unweighted(MGraph G, Table T, Vertex S);
void Unweighted2(MGraph G, Table T, Vertex S);
void Dijkstra(MGraph G, Table T, Vertex S);

//最小生成树算法
void Prim(MGraph G, Table T, Vertex S);
#endif	// _TABLE_