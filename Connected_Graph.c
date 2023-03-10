#include <stdio.h>
#define Max_Vertices 100
#define Max_Elements 100

typedef struct {
    int A[Max_Vertices][Max_Vertices];
    int n, m;
}Graph;

//------------------------Graph-------------------------

void init_Graph(Graph *G, int n)
{
    int i, j;
    G->n = n;
    G->m = 0;
    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            G->A[i][j] = 0;
}

void add_Edge(Graph *G, int x, int y)
{
    G->A[x][y] = 1;
    G->A[y][x] = 1;
    G->m ++;
}

int adjacent(Graph G, int x, int y)
{
    return G.A[x][y] == 1;
}

int mark[Max_Vertices];
void DFS(Graph G, int x)
{
    int i;
    mark[x] = 1;
    for ( i = 1; i <= G.n; i++)
        if (adjacent(G, x, i) && !mark[i]) DFS(G, i);
}

int connected(Graph G)
{
    int i;
    DFS(G, 1);
    for (i = 1; i <= G.n; i++)
        if (!mark[i]) return 0;
    return 1;
}

int count_connected(Graph G)
{
    int cnt = 0, i;
    for (i = 1; i <= G.n; i++)
        if (!mark[i])
        {
            DFS(G, i);
            ++cnt;
        }
    return cnt;
}

int highest_degree_in_connected_part(Graph G)
{
    int i, cnt_vertices = 0, highest_deg = 0;
    for (i = 1; i <= G.n; i++)
        if (!mark[i])
        {
            DFS(G, i);
            if (highest_deg < cnt_vertices)
                highest_deg = cnt_vertices;
            cnt_vertices = 0;
        }
}

//============================================
int main ()
{
    freopen("test.txt", "r", stdin);
    int n, m, u, v, i;
    Graph G;

    scanf("%d %d", &n, &m);
    init_Graph(&G, n);
    for (i = 1; i <= m; i++)
    {
        scanf("%d %d", &u, &v);
        add_Edge(&G, u, v);
    }

    for (i = 1; i <= n; i++)
        mark[i] = 0;
    
    connected(G) ? printf("GRAPH CONNECTED") : printf("GRAPH DISCONNECTED");
    printf("\nNumber of connected parts in the graph: %d\n", count_connected(G));
    printf("Highest degree in the connected part of graph: %d", highest_degree_in_connected_part(G));
    
    return 0;
}