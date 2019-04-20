#include<stdio.h>
#include"mgraph.h"

int main(int argc, char const *argv[])
{
    MGraph G;
    G = BuildGraph();
    MGraph MST;
    int MSTWeight = Kruskal(G, MST);
    printf("MST totalWeight = %d\n", MSTWeight);
    return 0;
}
