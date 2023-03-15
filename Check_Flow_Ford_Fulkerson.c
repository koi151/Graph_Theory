#include <stdio.h>

#define Max_Vertices 100
#define NO_EDGE 0
#define INF 999999

typedef struct {
    int n, m;
    int C[Max_Vertices][Max_Vertices];
    int F[Max_Vertices][Max_Vertices];
}Graph;

void init_graph(Graph *G, int n)
{
    G->m = 0;
    G->n = n;
    int i, j;
    for (i = 1; i <= G->n; i++)
        for (j = 1; j <= G->n; j++)
            G->C[i][j] = 0;
}

void init_flow(Graph *G)
{
    int i, j;
    for (i = 1; i <= G->n; i++)
        for (j = 1; j <= G->n; j++)
            G->F[i][j] = 0;
}

int sum_incoming_flow (Graph *G, int s)
{
    int i, sum = 0;
    for (i = 1; i <= G->n; i++)
        if (G->F[s][i]) sum += G->F[s][i];
    return sum;
}

int sum_outcoming_flow (Graph *G, int s)
{
    int i, sum = 0;
    for (i = 1; i <= G->n; i++)
        if (G->F[i][s]) sum += G->F[i][s];
    return sum;
}

int check_flow (Graph *G, int s, int t)
{
    int i;
    if (sum_incoming_flow(G, s) != sum_outcoming_flow(G, t)) return 0;
    for (i = 1; i <= G->n; i++)
        if (i != s && i != t)
            if (sum_incoming_flow(G, i) != sum_outcoming_flow(G, i)) return 0;
    return 1;
}

//=========================================
int main ()
{
    int n, m, u, v, c, f, i;
    Graph G;

    scanf("%d %d", &n, &m);
    init_graph(&G, n);
    init_flow(&G);
    for (i = 1; i <= m; i++)
    {
        scanf("%d %d %d %d", &u, &v, &c, &f);
        if (f > c)
        {
            printf("NO");
            return 0;
        }
        G.C[u][v] = c;
        G.F[u][v] = f;
    }

    printf(check_flow(&G, 1, n) ? "YES" : "NO");
    return 0;
}