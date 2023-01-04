#include <stdio.h>
#define Max_Vertices 100
#define Max_Elements 100
#define WHITE 0 
#define BLACK 1
#define GRAY 2


typedef struct {
    int A[Max_Vertices][Max_Vertices];
    int n, m;
}Graph;

typedef struct {
    int data[Max_Elements];
    int size;
}List;

//---------------------------List-------------------------------

void make_null_List(List *L)
{
    L->size = 0;
}

int empty_List(List L)
{
    return L.size == 0;
}

void push_back(List *L, int x)
{
    L->data[L->size] = x;
    L->size ++;
}

int element_at(List L, int pos)
{
    return L.data[pos-1];
}

//---------------------------Graph-------------------------------

void init_Graph(Graph *G, int n)
{
    G->n = n;
    G->m = 0;
    int i, j;
    for (i = 1; i <= G->n; i++)
        for (j = 1; j <= G->n; j++)
            G->A[i][j] = 0;
}

void add_Edge(Graph *G, int x, int y)
{
    G->A[x][y] = 1;
    G->m ++;
}

int adjacent(Graph G, int x, int y)
{
    return G.A[x][y] == 1;
}

List neighbors(Graph G, int x)
{
    List L;
    make_null_List(&L);
    int i;
    for (i = 1; i <= G.n; i++)
        if (G.A[x][i]) push_back(&L, i);
    return L;
}

int color[Max_Vertices];
int has_cycle = 0;

void DFS(Graph G, int u)
{
    int i;
    color[u] = GRAY;

    List Nei = neighbors(G,u);
    for (i = 0; i < Nei.size; i++)
    {
        int v = Nei.data[i];
        if (color[v] == WHITE)
            DFS(G,v);
        else if (color[v] == GRAY)
        {
            has_cycle = 1;
            return;
        }
    }
    color[u] = BLACK;
}

//=============================================
int main ()
{
    freopen("test2.txt", "r", stdin);
    Graph G;
    int n, m, u, v, i;
    scanf("%d%d", &n, &m);
    init_Graph(&G, n);

    for (i = 1; i <= m; i++)
    {
        scanf("%d%d", &u, &v);
        add_Edge(&G, u, v);
    }    

    for (i = 1; i <= G.n; i++)
        color[i] = 0;

    DFS(G, 3);
    if (has_cycle) printf("Graph cycled");
    else printf("Graph does not contain cycle");
    return 0;
}