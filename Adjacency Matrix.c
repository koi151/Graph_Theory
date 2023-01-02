#include <stdio.h>
#define Max_Vertices 100

typedef struct {
    int A[Max_Vertices][Max_Vertices];
    int n, m;
}Graph;

void init_graph(Graph *G, int n)
{
    G->n = n;
    G->m = 0;
    int i, j;
    for (i = 1; i <= G->n; i++)
        for (j = 1; j <= G->n; j++)
            G->A[i][j] = 0;
}

void add_edge(Graph *G, int u, int v)
{
    G->A[u][v] ++;
    G->m ++;
}

int indegree(Graph *pG, int u)
{
    int deg = 0, i;
    for (i = 1; i <= pG->n; i++)
        deg += pG->A[i][u];
}

//=========================================
int main ()
{
    Graph G;
    int n, m, u, v ,i, j;
    scanf("%d %d", &n, &m);
    init_graph(&G, n);

    for ( i =1; i <= m; i++)
    {
        scanf("%d %d", &u, &v);
        add_edge(&G, u, v);
    }
    printf("Ma tran ke:\n");
    for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= n; j++)
            printf("%d ", G.A[i][j]);
        printf("\n");
    }
    
    return 0;
}