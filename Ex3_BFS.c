#include <stdio.h>
#define Max_Vertices 100
#define Max_Elements 100

typedef struct {
    int A[Max_Vertices][Max_Vertices];
    int n, m;
}Graph;

typedef struct {
    int data[Max_Elements];
    int front, rear;
}Queue;

//--------------------------Queue-------------------------

void make_null_queue(Queue *Q)
{
    Q->front = 0;
    Q->rear = -1;
}

int empty_queue(Queue Q)
{
    return Q.rear < Q.front;
}

int top_queue(Queue Q)
{
    return Q.data[Q.front];
} 

void enqueue(Queue *Q, int x)
{
    Q->rear ++;
    Q->data[Q->rear] = x;
}

void dequeue(Queue *Q)
{
    Q->front ++;
}

//---------------------------Graph---------------------------

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

int mark[Max_Vertices], parent[Max_Vertices];

void breadth_first_search(Graph G, int x, int p)
{
    Queue Q;
    make_null_queue(&Q);
    enqueue(&Q, x);
    parent[x] = p;

    int i;
    while (!empty_queue(Q))
    {
        int t = top_queue(Q);
        dequeue(&Q);
        if (mark[t]) continue;
        mark[t] = 1;
        
        for (i = 1; i <= G.n; i++)
            if (adjacent(G, t, i) && !mark[i])
            {
                if (parent[i] == -1) parent[i] = t;
                enqueue(&Q, i);
            }
    }
}

//==============================================
int main ()
{
    freopen("graph3.txt", "r", stdin);
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
    {
        mark[i] = 0;
        parent[i] = -1;
    }

    for (i = 1; i <= n; i++)
    {
        if (!mark[i])
            breadth_first_search(G, i, 0);
    }

    for(i = 1; i <= n; i++)
        printf("%d %d\n", i,parent[i]);
    
    return 0;
}
