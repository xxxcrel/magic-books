#ifndef _LGRAPH_H
#define _LGRAPH_H
#include <stdbool.h>
#define INFINITY 65536
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
void InsertEdge(LGraph G, Edge E);
LGraph BuildGraph();
int Kruskal(LGraph G, LGraph MST);
void PrintAdjList(LGraph G);

#endif	// _LGRA