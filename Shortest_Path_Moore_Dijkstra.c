#include <stdio.h>

#define NO_EDGE -1
#define Inf 1e9+7
#define Max_Vertices 100
#define Max_Elements 100

typedef struct {
    int A[Max_Vertices][Max_Vertices];
    int n, m;
}Graph;

void init_graph(Graph *G, int n)
{
    G->m = 0;
    G->n = n;
    int i, j;
    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            G->A[i][j] = NO_EDGE;
}

// w is the weigh of vertice
void add_edge(Graph *G, int x, int y, int w)
{
    G->A[x][y] = w;
    G->m ++;
}

//-----------------------Global Variables----------------------------------------------------------------------
int pi[Max_Vertices], parent[Max_Vertices], mark[Max_Vertices];
//------------------------------------------------------------------------------------------------------------

void Moore_Dijkstra(Graph G, int x)
{
    pi[x] = 0;
    parent[x] = -1;

    int i, j, k, u, min_pi;
    // this loop used for traversing every vertices in graph, except the last vertice which is unnecessary
    for (i = 1; i < G.n; i++)
    {
        min_pi = Inf;
        // this loop used for finding nearby vertice that unmarked and nearest from the current traversing vertice 
        for (j = 1; j <= G.n; j++)       
            if (!mark[j] && pi[j] < min_pi)
            {
                min_pi = pi[j];
                u = j; 
            }

        mark[u] = 1;

        // this loop used for update the value && parent of nearby vertices (u)
        for (k = 1; k <= G.n; k++)
            if (G.A[u][k] != NO_EDGE && !mark[k] && G.A[u][k] + pi[u] < pi[k])
            {
                pi[k] = G.A[u][k] + pi[u];
                parent[k] = u;
            }
    }
}
//=======================================================================================
int main ()
{
    /*
    freopen("test.txt", "r", stdin);
    Test case:
        3 4  
        1 2 9
        2 3 5
        1 3 4
        3 2 0
    */
    Graph G;
    int n, m, u, v, w, i;

    printf("This file used adjacency matrix\n");
    printf("Please enter the number of vertices and edges in graph\n");
    scanf("%d %d", &n, &m);
    init_graph(&G, n);
    printf("\nEnter the value of two vertices that create an edge and its weight (u, v, w)\n");
    for (i = 1; i <= m; i++)
    {
        printf("%d/%d edges:\n", i, m);
        scanf("%d %d %d", &u, &v, &w);
        add_edge(&G, u, v, w);
    }

    for (i = 1; i <= n; i++)
    {
        pi[i] = Inf;
        parent[i] = -1;
        mark[i] = 0; 
    }

    printf("\n");
    Moore_Dijkstra(G, 1);
    for ( i = 1; i <= n; i++)
        printf("pi[%d] = %d, p[%d] = %d\n", i, pi[i], i, parent[i]);
    
    printf("\n");
    if (pi[n] < Inf) printf("Shortest path from 1 to n: %d", pi[n]);
    else printf("There is no way from 1 to n");

    return 0;
}
