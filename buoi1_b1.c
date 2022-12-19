#include <stdio.h>
#define MAX_EDGES 100

// x:dinh, y:cung 3->2 : 2
typedef struct {
    int x, y;
}Edge;

// n: so luong dinh , m: so luong cac cung (size)
typedef struct {
    int n, m;
    Edge edges[MAX_EDGES];
}Graph;

void init_graph(Graph* G, int n){
	G->n = n;
	G->m = 0;
}

void add_edge(Graph *G, int x, int y)
{
    if (x >= 1 && y >= 1 && x <= G->n && y <= G->n)
    {
        G->edges[G->m].x = x;
        G->edges[G->m].y = y;
        G->m ++;
    }
}

void print_Graph(Graph G)
{
    int i;
    for (i = 1; i <= G.n; i++)
        printf("%d %d\n", G.edges[G.m].x, G.edges[G.m].y);
}

//========================================
int main ()
{
    Graph G;
    init_graph(&G, 6);

    add_edge(&G, 4, 5);
    add_edge(&G, 1, 3);
    add_edge(&G, 4, 2);
    add_edge(&G, 2, 4);
    add_edge(&G, 2, 4);
    add_edge(&G, 3, 2);

    print_Graph(G);

    return 0;
}