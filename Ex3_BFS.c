#include <stdio.h>
#define Max_length 100
#define Max_Vertices 100
#define Max_Elements 100

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
    int front, rear;
}Queue;

//-------------------------------Queue------------------------------

void make_null_queue(Queue *Q)
{
    Q->front = 0;
    Q->rear = -1;
}

void push_Queue(Queue *Q, int x)
{
    Q->rear ++;
    Q->data[Q->rear] = x;
}

int empty_Queue(Queue Q)
{
    return Q.front > Q.rear;
}

int top_Queue(Queue Q)
{
    return Q.data[Q.front];
}

int pop_Queue(Queue *Q)
{
    Q->front ++;
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

List breadth_first_search(Graph G, int x)
{
    List bfs;
    make_null_list(&bfs);
    Queue Q;
    make_null_queue(&Q);
    push_Queue(&Q, x);
    
    int mark[Max_Vertices];
    int i;
    for (i = 1; i <= G.n; i++)
        mark[i] = 0;

    while (!empty_Queue(Q))
    {
        int u = top_Queue(Q);
        pop_Queue(&Q);
        if (mark[u]) continue;
        push_back(&bfs, u);
        mark[u] = 1;

        List nei = neighbors(G, u);
        for (i = 1; i <= nei.size; i++)
        {
            int v = element_at(nei, i);
            if (!mark[v])
                push_Queue(&Q, v);
        }
    }
    return bfs;
}

List breadth_first_search_2(Graph G, int x, int parent[])
{
    List bfs;
    make_null_list(&bfs);
    Queue Q;
    make_null_queue(&Q);
    push_Queue(&Q, x);
    parent[x] = 0;

    int mark[Max_Vertices];
    int i;
    for (i = 1; i <= G.n; i++)
        mark[i] = 0;

    while (!empty_Queue(Q))
    {
        int u = top_Queue(Q);
        pop_Queue(&Q);
        if (mark[u]) continue;
        push_back(&bfs, u);
        mark[u] = 1;
        

        List nei = neighbors(G, u);
        for (i = 1; i <= nei.size; i++)
        {
            int v = element_at(nei, i);
            if (!mark[v])
            {
                if (parent[v] == -1) parent[v] = u;
                push_Queue(&Q, v);
            }
        }
    }
    return bfs;
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

    int mark_bfs[Max_Elements], parent[Max_Vertices];
    for (i = 1; i <= n; i++)
    {
        mark_bfs[i] = 0;
        parent[i] = -1;
    }

    printf("\nTraversing elements with BFS:\n");
    for (i = 1; i <= n; i++)
    {
        if (!mark_bfs[i])
        {
            List bfs_list = breadth_first_search(G, i);
            for (j = 1; j <= bfs_list.size; j++)
            {
                printf("Traversed: %d\n", element_at(bfs_list, j));
                mark_bfs[element_at(bfs_list, j)] = 1;
            }
        }    
    }
    
    for (i = 1; i <= n; i++)
        mark_bfs[i] = 0;
    printf("\n");

    for (i = 1; i <= n; i++)
    {
        if (!mark_bfs[i])
        {
            List bfs_list = breadth_first_search_2(G, i, parent);
            for (j = 1; j <= bfs_list.size; j++)
            {
                // printf("Traversed: %d\n", element_at(bfs_list, j));
                mark_bfs[element_at(bfs_list, j)] = 1;
            }
        }    
    }

    for(i = 1; i <= n; i++)
        printf("parent[%d] = %d\n", i, parent[i]);



    return 0;
}