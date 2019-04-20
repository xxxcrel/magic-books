#include<stdio.h>
#include"lgraph.h"

int main(int argc, char const *argv[])
{
    LGraph G;
    G = BuildGraph();
    LGraph MST;
    int MSTWeight = Kruskal(G, MST);
    printf("MST totalWeight = %d\n", MSTWeight);
    return 0;
}
