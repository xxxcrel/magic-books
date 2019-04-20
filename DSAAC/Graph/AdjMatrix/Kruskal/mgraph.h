#ifndef _MGRAPH_H
#define _MGRAPH_H
#include<stdbool.h>

#define MaxVertexNum 100 //矩阵最大的行和列
#define MaxSize 100//用于BFS创建的队列
#define INFINITY 65535 //INFINITY在math.h已经定义了的
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
    //DataType Data[MaxVertexNum];
};
typedef PtrToGRecord MGraph;

MGraph CreateGraph(int vertexNum);
void InsertEdge(MGraph G, Edge E);
MGraph BuildGraph();
int Kruskal(MGraph G, MGraph MST);
void PrintAdjMatrix(MGraph G);

#endif