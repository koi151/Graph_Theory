#include <stdio.h>

#define Max_Vertices 100
#define Max_Elements 100
#define NONE -1
#define WHITE 1
#define BLACK 2

typedef struct {
    int A[Max_Vertices][Max_Vertices];
    int n, m;
}Graph;

void init_Graph(Graph *G, int n)
{
    G->n = n;
    G->m = 0;
    int i, j;
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

int color[Max_Vertices], conflict = 0;

void BFS_colorize(Graph G, int x, int c)
{
    color[x] = c;
    int i;
    for (i = 1; i <= G.n; i++)
        if (adjacent(G, x, i))
        {
            if (color[i] == NONE) BFS_colorize(G, i, 3 - c); 
            else if (color[i] == color[x])
            {
                conflict = 1;
                return;
            }
        }
}

//==========================================================
int main ()
{
    freopen("test.txt", "r", stdin);
    int n, m, u, v, i;
    Graph G;

    scanf("%d %d", &n , &m);
    init_Graph(&G, n);
    for (i = 1; i <= m; i++)
    {
        scanf("%d %d", &u, &v);
        add_Edge(&G, u, v);
    }

    for (i =1; i <= n; i++)
        color[i] = NONE;

    BFS_colorize(G, 1, WHITE);
    printf(conflict ? "Bipartite graph" : "Not the bipartite graph");

    return 0;
}