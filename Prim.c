/*
    Prim algorimth finding the minimun spanning tree.
    Prim will give the correct result as Krusal algorimth, best using for graph that has more vertices than edges.
    (on the contrary, using Krusal algorimth instead).
*/
//==================================================================
#include <stdio.h>

#define Max_Vertices 100
#define NO_EDGE -999
#define INF 1e9+7

//-- Global varibles
int pi[Max_Vertices], parent[Max_Vertices], mark[Max_Vertices];

typedef struct {
    int A[Max_Vertices][Max_Vertices];
    int n, m;
}Graph;

//---- Functions
void init_graph(Graph *G, int n)
{
    G->m = 0;
    G->n = n;
    int i, j;
    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            G->A[i][j] = NO_EDGE;
}

void add_edge(Graph *G, int x, int y, int w)
{
    G->A[x][y] = w;
    G->A[y][x] = w;
    G->m ++;
}

int Prim_tree_weight(Graph *G, Graph *T, int s)
{
    pi[s] = 0;
    int i, j, min_dist, u;

    for (i = 1; i < G->n; i++)
    {
        min_dist = INF;
        for (j = 1; j <= G->n; j++)
            if (!mark[j] && min_dist > pi[j])
            {
                min_dist = pi[j];
                u = j;
            }

        mark[u] = 1;

        for (j = 1; j <= G->n; j++)
            if (G->A[u][j] != NO_EDGE && !mark[j] && pi[j] > G->A[u][j])
            {
                pi[j] = G->A[u][j];
                parent[j] = u;
            }
    }
    
    int w, sum = 0;
    init_graph(T, G->n);
    for (i = 1; i <= G->n; i++)
    {
        if (parent[i] != -1)
        {
            w = G->A[parent[i]][i];
            add_edge(T, parent[i], i, w);
            sum += w;
        }
    }
    return sum;

}
//==========================================================
/* TEST CASE:
4 4
1 2 4
2 3 6
3 4 1
1 4 8
*/
//======================================================
int main ()
{
    int n, m, u, v, w, i, j;
    Graph G;

    scanf("%d %d", &n, &m);
    init_graph(&G, n);
    for (i = 1; i <= m; i++)
    {
        scanf("%d %d %d", &u, &v, &w);
        add_edge(&G, u, v, w);
    }

    for (i = 1; i <= G.n; i++)
    {
        mark[i] = 0;
        pi[i] = INF;
        parent[i] = -1;
    }

    Graph T;
    printf("%d\n", Prim_tree_weight(&G, &T, 1));

    for (i = 1; i <= T.n; i++)
        for (j = i+1; j <= T.n; j++)
            if (T.A[i][j] != NO_EDGE)
                printf("%d %d %d\n", i, j, T.A[i][j]);

    return 0;
}
