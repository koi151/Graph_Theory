#include <stdio.h>

#define Max_Vertices 100
#define INF 1e9+7
#define NO_EDGE -999

typedef struct {
    int A[Max_Vertices][Max_Vertices];
    int n, m;
}Graph;

void init_graph(Graph *G, int n)
{
    G->m = 0;
    G->n = n;
    int i, j;
    for (i = 1; i <= G->n; i++)
        for (j = 1; j <= G->n; j++)
            G->A[i][j] = NO_EDGE;
}

void add_edge(Graph *G, int x, int y, int w)
{
    G->A[x][y] = w;
    G->m ++;
}
//---------------------------------GLOBAL VARIABLES---------------------------
int dis[Max_Vertices][Max_Vertices], next[Max_Vertices][Max_Vertices];
//----------------------------------------------------------------------------
void Floyd_Warshall(Graph *G)
{
    int i, j, k;
            
    for (i = 1; i <= G->n; i++)
    {
        dis[i][i] = 0;
        for (j = 1; j <= G->n; j++)
            if (G->A[i][j] != NO_EDGE)
            {
                dis[i][j] = G->A[i][j];
                next[i][j] = j;
            }
    }

    for (i = 1; i <= G->n; i++)
    {
        for (j = 1; j <= G->n; j++)
        {
            if (dis[j][i] == INF) continue;
            for (k = 1; k <= G->n; k++)
            {
                if (dis[i][k] == INF) continue;
                if (dis[j][i] + dis[i][k] < dis[j][k])
                {
                    dis[j][k] = dis[j][i] + dis[i][k];
                    next[j][k] = next[j][i];
                }
            }
        }
    }
}
//==========================================================
/*
Test case:
3 4
1 2 9
2 3 4
1 3 4
2 1 -3
*/
//==========================================================
int main ()
{
    int n, m, u, v, w, i, j;
    Graph G;

    printf("Floyd - Warshaw algorimth to find the distances between all vertices\n---------------------------------------------------------------------\n");
    printf("Enter the number of vertices and edges\n");
    scanf("%d %d", &n, &m);
    init_graph(&G, n);

    printf("\nEnter the value of two vertices to create an edge and weight of edge\n");
    for (i = 1; i <= m; i++)
    {
        printf("Edge %d/%d\n", i, m);
        scanf("%d %d %d", &u, &v, &w);
        add_edge(&G, u, v, w);
    }

    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
        {
            dis[i][j] = INF;
            next[i][j] = -1;
        }

    printf("\nThe distance between all edges:\n");
    Floyd_Warshall(&G);
    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            if (dis[i][j] < INF)
                printf("%d -> %d: %d\n", i, j, dis[i][j]);
            else printf("%d -> %d: NO PATH\n", i, j);

    return 0;
}