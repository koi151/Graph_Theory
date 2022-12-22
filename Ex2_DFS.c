/*
    Using DFS algorithm for traversing graph
*/

#include <stdio.h>
#define Max_Vertices 20
#define Max_Length 20
#define Max_Element 40
int i, j, k;

typedef struct {
    int A[Max_Vertices][Max_Vertices];
    int n;
}Graph;

typedef struct {
    int Data[Max_Length];
    int size;
}List;

typedef struct {
    int data[Max_Element];
    int size;
}Stack;

//----------------Stack---------------------------------

void make_null_stack(Stack *S)
{
    S->size = 0;
}

void push_stack(Stack *S, int x)
{
    S->data[S->size] = x;
    S->size ++;
}

int top(Stack S)
{
    return S.data[S.size-1];
}

void pop(Stack *S)
{
    S->size --;
}

int empty(Stack S)
{
    return S.size == 0;
}

//----------------List-----------------------

void make_null_list(List *L)
{
    L->size = 0;
}

void push_back(List *L, int x)
{
    L->Data[L->size] = x;
    L->size ++;
}

int element_at(List L, int pos)
{
    return L.Data[pos-1];
}

//---------------Graph-------------------

void init_Graph(Graph *G, int n)
{
    G->n = n;
    for (i = 1; i <= n; i++)
        for(j = 1; j <= n; j++)
            G->A[i][j] = 0;
}

void add_Edge(Graph *G, int x, int y)
{
    G->A[x][y] = 1;
    G->A[y][x] = 1;
}

int adjacent(Graph G, int x, int y)
{
    return G.A[x][y] != 0;
}

int Degree(Graph G, int x)
{
    int deg = 0;
    for(i = 1; i <= G.n; i++)
        if (G.A[x][i] == 1) ++deg;
    return deg;
}

List neighbors(Graph G, int x)
{
    List L;
    make_null_list(&L);
    for (i = 1; i <= G.n; i++)
        if (G.A[i][x] == 1)
            push_back(&L, i);
    return L;
}

List depth_first_search(Graph G, int x)
{
    List dfs;
    make_null_list(&dfs);
    Stack S;
    make_null_stack(&S);
    push_stack(&S, x);
    int mark[Max_Vertices];
    int n = 0;

    for (i = 1; i <= G.n; i++)
        mark[i] = 0;

    while (!empty(S))
    {
        int u = top(S);
        pop(&S);
        if (mark[u]) continue; // already traversed
        push_back(&dfs, u);
        mark[u] = 1;

        List L = neighbors(G, u);

        for (i = 1; i <= L.size; i++)
        {
            int v = element_at(L, i);
            if (!mark[v])
                push_stack(&S, v);
        }
    }
    return dfs;
}

//=========================================
int main ()
{
    Graph G;
    freopen("graph2.txt", "r", stdin);
    int n, m; // n: number of vertices  ,   m: number of edges
    int u, v; // u, v: vertice u, vertice v

    scanf("%d%d", &n, &m);
    init_Graph(&G, n);

    for (k = 1; k <= m; k++)
    {
        scanf("%d%d", &u, &v);
        add_Edge(&G, u, v);
    }

    for (i = 1; i <= G.n; i++)
    {
        for (j = 1; j <= G.n; j ++)
            printf("%d ", G.A[i][j]);
        printf("\n");
    }

    int mark_dfs[Max_Vertices];
    for (i = 1; i <= G.n; i++)
        mark_dfs[i] = 0;

    printf("Elements in DFS list:\n");
    for (i = 1; i <= G.n; i++)
    {
        if (!mark_dfs[i])
        {
            List dfs_list = depth_first_search(G, i);
            for (j = 1; j <= dfs_list.size; j++)
            {
                printf("Traversed: %d\n", element_at(dfs_list, j));
                mark_dfs[element_at(dfs_list, j)] = 1;
            }
        }
    }
    return 0;
}