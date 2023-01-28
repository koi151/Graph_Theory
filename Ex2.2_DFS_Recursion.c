#include <stdio.h>

#define Max_Elements 100
#define Max_Vertices 100
#define NO_EDGE -999

typedef struct {
    int A[Max_Vertices][Max_Vertices];
    int n, m;
}Graph;

typedef struct {
    int data[Max_Elements];
    int size;
}Stack;
//---------------------------GRAPH------------------------------------
void init_graph(Graph *G, int n)
{
    G->m = 0;
    G->n = n;
    int i, j;
    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            G->A[i][j] = NO_EDGE;
}

void add_edge(Graph *G, int x, int y)
{
    G->A[x][y] = 1;
    G->m ++;
}

int adjacent(Graph *G, int x, int y)
{
    return G->A[x][y] == 1;
}
//------------------------------GLOBAL VARIABLES-----------------------
int mark[Max_Vertices];
//---------------------------------------------------------------------
void DFS(Graph *G, int s)
{
    if (mark[s]) return;
    mark[s] = 1;
    printf("%d\n", s);
    int i;
    for (i = 1; i <= G->n; i++)
        if (!mark[i] && adjacent(G, s, i))
            DFS(G, i);
}
//====================================================================
int main ()
{
    int n, m, u, v, i;
    Graph G;

    scanf("%d %d", &n, &m);
    init_graph(&G, n);
    for (i = 1; i <= m; i++)
    {
        scanf("%d %d", &u, &v);
        add_edge(&G, u, v);
    }

    for (i = 1; i <= n; i++)
        mark[i] = 0;
    
    for (i = 1; i <= n; i++)
        if (!mark[i]) DFS(&G, i);

    return 0;
}