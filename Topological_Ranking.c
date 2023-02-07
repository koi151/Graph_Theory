/*  TEST CASE:
7 12
1 2
1 3
2 4
2 5
2 6
3 2
3 5
3 6
4 7
5 7
6 4
6 5

Result:
0
2
1
4
4
3
5
*/
#include <stdio.h>

#define Max_Elements 100
#define Max_Vertices 100
#define ElementType int 

int indeg[Max_Vertices], rank[Max_Vertices];

typedef struct {
    int A[Max_Vertices][Max_Vertices];
    int n, m;
}Graph;

typedef struct {
    ElementType data[Max_Vertices];
    int size;
}List;
//-------------------------List---------------------------
void make_null_list(List *L)
{
    L->size = 0;
}

int empty_list(List *L)
{
    return L->size == 0;
}

ElementType element_at(List *L, int pos)
{
    return L->data[pos-1];
}

void push_back(List *L, ElementType x)
{
    L->data[L->size++] = x;
}

void copy_list(List *L1, List *L2)
{
    make_null_list(L1);
    int i;
    for (i = 1; i <= L2->size; i++)
        push_back(L1, element_at(L2, i));
}

//-----------------------------Graph---------------------
void init_graph(Graph *G, int n)
{
    G->m = 0;
    G->n = n;
    int i, j;
    for (i = 1; i <= n; i++)
    {
        indeg[i] = 0;
        rank[i] = -1;
        for (j = 1; j <= n; j++)
            G->A[i][j] = 0;
    }
}

void add_edge(Graph *G, int x, int y)
{
    if (G->A[x][y] > 0) return;
    G->A[x][y] ++;
    G->m ++;
    indeg[y] ++;
}

void topo_ranking(Graph *G)
{
    List L1, L2;
    make_null_list(&L1);

    int i;
    for (i = 1; i <= G->n; i++)
        if (!indeg[i]) push_back(&L1, i);

    ElementType u;
    int r = 0, j;
    while (!empty_list(&L1))
    {
        make_null_list(&L2);
        for (i = 1; i <= L1.size; i++)
        {
            u = element_at(&L1, i);
            rank[u] = r;
            for (j = 1; j <= G->n; j++)
                if (G->A[u][j] > 0)
                {
                    indeg[j]--;
                    if (!indeg[j]) push_back(&L2, j);
                }
        }
        ++r;
        copy_list(&L1, &L2);
    }
}
//========================================================
int main ()
{
    int n, m, u, v, i;
    Graph G;

    scanf("%d %d", &n, &m);
    init_graph(&G, n);
    for (i = 1; i <= m; i++)
    {
        scanf("%d %d", &u, &v);
        add_edge(&G, u, v);
    }

    topo_ranking(&G);
    for (i = 1; i <= n; i++)
        printf("%d\n", rank[i]);

    return 0;
}
