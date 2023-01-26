#include <stdio.h>

#define INF 1e9+7
#define NO_EDGE -999
#define Max_Vertices 100

typedef struct {
    int u, v, w;
}Edge;

typedef struct {
    int n, m;
    Edge edge[Max_Vertices];
}Graph;

void init_Graph(Graph *G, int n)
{
    G->m = 0;
    G->n = n;
}

void add_edge(Graph *G, int u, int v, int w)
{
    G->edge[G->m].u = u;
    G->edge[G->m].v = v;
    G->edge[G->m].w = w;
    G->m ++;
}

void Bellman_Ford(Graph *G, int s, int mark[], int pi[], int parent[])
{
    pi[s] = 0;
    parent[s] = -1;
    int i, j, u, v, w;
    for (i = 1; i < G->n; i++)
        for (j = 0; j < G->m; j++)
        {
            u = G->edge[j].u;
            v = G->edge[j].v;
            w = G->edge[j].w;
            if (pi[u] + w < pi[v])
            {
                pi[v] = pi[u] + w;
                parent[v] = u;
            }
        } 
}

//=====================================================================
int main ()
{
    int i, n, m ,u, v, w;
    int mark[Max_Vertices], pi[Max_Vertices], parent[Max_Vertices];
    Graph G;
    printf("Bellman Ford algorithm finding shortest way\n-------------------------------------------\n");
    printf("Enter the number of n vertices and m edges\n");
    scanf("%d %d", &n, &m);
    init_Graph(&G, n);
    printf("\nEnter the number of vertice u and v to create an edge, and weight w\n");
    for (i = 1; i <= m; i++)
    {
        printf("Edge %d/%d\n", i, m);
        scanf("%d %d %d", &u, &v, &w);
        add_edge(&G, u, v, w);
    }

    for (i = 1; i <= n; i++)
    {
        mark[i] = 0;
        pi[i] = INF;
    }
    int s, t;
    printf("\nEnter the start vertice and end vertice to find the shortest way\n");
    scanf("%d %d", &s, &t);

    Bellman_Ford(&G, s, mark, pi, parent);
    int temp = t, cnt = 0, path[Max_Vertices];
    while (temp != s)
    {
        path[cnt++] = temp;
        temp = parent[temp];
    }
    path[cnt] = s;

    printf("\nPATH:\n");
    for (i = cnt; i > 0; i--)
        printf("%d -> ", path[i]);
    printf("%d\n", path[0]);
    if (pi[t] < INF) printf("Distance: %d\n", pi[t]);
    else printf("Can not find the way\n");

    return 0;
}
