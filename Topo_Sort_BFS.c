#include <stdio.h>

#define Max_Vertices 100
#define Max_Elements 100
#define ElementType int

typedef struct {
    int A[Max_Vertices][Max_Vertices];
    int n, m;
}Graph;

typedef struct {
    ElementType data[Max_Elements];
    int front, rear;
}Queue;

typedef struct {
    ElementType data[Max_Elements];
    int size;
}List;
//---------------------------List------------------------------
void make_null_list(List *L)
{
    L->size = 0;
}

int empty_list(List *L)
{
    return L->size == 0;
}

int element_at(List *L, ElementType p)
{
    return L->data[p-1];
}

void push_back(List *L, ElementType x)
{
    L->data[L->size] = x;
    L->size ++;
}
//----------------------------Queue----------------------------
void make_null_queue(Queue *Q)
{
    Q->front = 0;
    Q->rear = -1;
}

int empty_queue(Queue *Q)
{
    return Q->front > Q->rear;
}

int front_queue(Queue *Q)
{
    return Q->data[Q->front];
}

void enqueue(Queue *Q, ElementType x)
{
    Q->rear ++;
    Q->data[Q->rear] = x;
}

void dequeue(Queue *Q)
{
    Q->front ++;
}
//----------------------------Graph----------------------------
void init_graph(Graph *G, int n)
{
    G->m = 0;
    G->n = n;
    int i, j;
    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            G->A[i][j] = 0;
}

void add_edge(Graph *G, int x, int y)
{
    G->A[x][y] = 1;
    G->m ++;
}

List topo_sort(Graph *G)
{
    List L;
    make_null_list(&L);
    int d[Max_Vertices];
    int i, j;

    // initial d, update the data of list d
    for (i = 1; i <= G->n; i++)
    {
        d[i] = 0;
        for (j = 1; j <= G->n; j++)
            if (G->A[j][i] > 0)
                d[i]++;
    }

    // add vertices that has -deg = 0 to queue
    Queue Q;
    make_null_queue(&Q);
    for (i = 1; i <= G->n; i++)
        if (!d[i]) enqueue(&Q, i);

    ElementType u;
    while (!empty_queue(&Q))
    {
        u = front_queue(&Q);
        push_back(&L, u);
        dequeue(&Q);
        
        //delete all the edges of vertex that traversed recently
        for (i = 1; i <= G->n; i++)
            if (G->A[u][i] > 0)
            {
                d[i]--;
                if (!d[i]) enqueue(&Q, i);
            }
    }
    return L;
}
//=============================================================
/*
Test case:
7 10
1 2
1 3
1 4
2 3
2 6
3 7
4 5
5 3
5 7
6 7
*/
//=============================================================
int main ()
{
    int n, m, u, v, i;
    Graph G;

    printf("Topo sort using BFS algorimth\n---------------------------------------------------\n");
    printf("Please enter the number of vertices and edges\n");
    scanf("%d %d", &n, &m);
    init_graph(&G, n);
    printf("\nEnter the value of 2 vertices that create an edge\n");
    for (i = 1; i <= m; i++)
    {
        printf("Edge %d/%d:\n", i, m);
        scanf("%d %d", &u, &v);
        add_edge(&G, u, v);
    }

    List L = topo_sort(&G);
    printf("\nTopo sort: ");
    for (i = 1; i <= L.size; i++)
        printf("%d ", element_at(&L, i));

    return 0;
}