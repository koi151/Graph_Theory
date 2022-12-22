/*
    Perform undirected graph with vertice-vertice matrix
*/

#include <stdio.h>
#define Max_Vertices 20
#define Max_Length 20
int i,j;

typedef struct {
    int A[Max_Vertices][Max_Vertices];
    int n; // number of edges
}Graph;

typedef struct {
    int Data[Max_Length];
    int size;
}List;

void make_null_list(List *list)
{
    list->size = 0;
}

void push_back(List *list, int x)
{
    list->Data[list->size] = x;
    list->size ++;
}

int element_at(List list, int pos)
{
    return list.Data[pos-1];
}

void init_Graph(Graph *G, int n)
{
    G->n = n;
    for (i = 1; i <= n; i++)
        for(j = 1; j <= n; j++)
            G->A[i][j] = 0;
}

// Add new edge to graph
void add_Edge(Graph *G, int x, int y)
{
    G->A[x][y] = 1;
    G->A[y][x] = 1;
}

// Check whether 2 vertices are neighbor or not
int Adjacent(Graph G, int x, int y)
{
    return G.A[x][y] != 0;
}

// find the level of a specific vertice
int Degree(Graph G, int x)
{
    int deg = 0;
    for(i = 1; i <= G.n; i++)
        if (G.A[x][i] == 1) ++deg;
    return deg;
}

// Find the list of neighbors of vertice x
List neighbors(Graph G, int x)
{
    int i;
    List L;
    make_null_list(&L);
    for (i = 1; i <= G.n; i++)
        if (G.A[i][x] == 1)
            push_back(&L, i);
    return L;
}

//=========================================
int main ()
{
    Graph G;
    freopen("graph1.txt", "r", stdin);
    int n, m, i, j, k; // n: number of vertices  ,   m: number of edges
    int u, v; // u, v: vertice u, vertice v

    scanf("%d%d", &n, &m);
    printf("n:%d m:%d\n", n, m);
    init_Graph(&G, n);

    for (k = 1; k <= m; k++)
    {
        scanf("%d%d", &u, &v);
        add_Edge(&G, u, v);
    }

    // printf("%d\n", Adjacent(G,2,3));

    for (int i = 1; i <= G.n; i++)
        printf("degree(%d) = %d\n",i, Degree(G,i));

    List L;
    make_null_list(&L);
    
    printf("List of all neighbors of a specific vertice:\n");
    for (i = 1; i <= G.n; i++)
    {
        List list = neighbors(G,i);
        printf("Neighbors(%d) = [ ", i);
        for (j = 1; j <= list.size; j++)
            printf("%d ", element_at(list,j));
            printf("]\n");
    }
    
    // fclose(file);//----------------------------------------------------
    for (i = 1; i <= G.n; i++)
    {
        for (j = 1; j <= G.n; j ++)
            printf("%d ", G.A[i][j]);
        printf("\n");
    }


    return 0;
}