#include <stdio.h>
#define Max_length 20
#define Max_Vertices 20
#define Max_Elements 40

typedef struct{
    int A[Max_Vertices][Max_Vertices];
    int n;
}Graph;

typedef struct {
    int data[Max_length];
    int size;
}List;

typedef struct {
    int data[Max_Elements];
    int size;
}Stack;

//------------------------------Stack-------------------------------

void make_null_stack(Stack *S)
{
    S->size = 0;
}

int empty_stack(Stack S)
{
    return S.data == 0;
}

int top(Stack S)
{
    return S.data[S.size-1];
}

void push_stack(Stack *S, int x)
{
    S->data[S->size] = x;
    S->size ++;
}

void pop(Stack *S)
{
    S->size --;
}


//---------------------------------List-----------------------------

void make_null_list(List *L)
{
    L->size = 0;
}

int element_at(List L, int pos)
{
    return L.data[pos-1];
}

void push_back(List *L, int x)
{
    L->data[L->size] = x;
    L->size ++; 
}

//-------------------------Graph-----------------------

void init_Graph(Graph *G, int n)
{
    int i, j;
    G->n = n;
    for (i = 1; i <= G->n; i++)
        for (j = 1; j <= G->n; j++)
            G->A[i][j] = 0;
}

void add_Edges(Graph *G, int x, int y)
{
    G->A[x][y] = 1;
    G->A[y][x] = 1;
}

int adjacent(Graph *G, int x, int y)
{
    return G->A[x][y] != 0;
}

int degree(Graph G, int x)
{
    int i, deg = 0;
    for (i = 1; i <= G.n; i++)
        if (G.A[x][i]) ++deg;
    return deg; 
}

List neighbors(Graph G, int x)
{
    int i;
    List L;
    make_null_list(&L);
    for (i = 1; i <= G.n; i++)
        if (G.A[i][x]) push_back(&L, i);
    return L;
}

int mark[Max_Vertices], parent[Max_Vertices];
// void DFS_Recursion(Graph G, int x)
// {
//     if (mark[x]) return;
//     printf("Traversed: %d\n", x);
//     mark[x] = 1;
//     List nei = neighbors(G, x);
//     int i;
//     for (i = 1; i <= nei.size; i++)
//         DFS_Recursion(G, element_at(nei, i));
// }

void DFS_Recursion_2(Graph G, int x, int p)
{
    if (mark[x]) return;
    // printf("Traversed: %d\n", x);
    mark[x] = 1;
    parent[x] = p;
    List nei = neighbors(G, x);
    int i;
    for (i = 1; i <= nei.size; i++)
        DFS_Recursion_2(G, element_at(nei, i), x);
}

//====================================================
int main ()
{
    freopen("graph3.txt", "r", stdin);
    Graph G;
    int n, m, i, j, u, v;

    scanf("%d%d", &n, &m);
    init_Graph(&G, n);
    for (i = 1; i <= m; i++)
    {
        scanf("%d%d", &u, &v);
        add_Edges(&G, u, v);
    }

    for (i = 1; i <= n; i++)
        {
        for (j = 1; j <= n; j ++)
            printf("%d ", G.A[i][j]);
            printf("\n");
        }

    for (i = 1; i <= n; i++)
    {
        mark[i] = 0;
        parent[i] = -1;
    }

    // DFS_Recursion(G, 1);

    for (i = 1; i <= n; i++)
        if (!mark[i])
            DFS_Recursion_2(G, i, 0);

    for (i = 1; i <= n; i++)
            printf("%d %d\n", i, parent[i]);

    

    
  


    return 0;
}