#include <stdio.h>
#define Max_Vertices 100
#define Max_Elements 100

typedef struct {
    int A[Max_Vertices][Max_Vertices];
    int n, m;
}Graph;

typedef struct {
    int data[Max_Vertices];
    int size;
}Stack;

//-----------------------Stack-------------------

void make_null_stack(Stack *S)
{
    S->size = 0;
}

int top_Stack(Stack S)
{
    return S.data[S.size-1];
}

int empty_stack(Stack S)
{
    return S.size == 0;
}

void push_stack(Stack *S, int x)
{
    S->data[S->size] = x;
    S->size ++;
}

void pop_stack(Stack *S)
{
    S->size --;
}

//---------------------Graph-----------------------

void init_Graph(Graph *G, int n)
{
    G->n = n;
    G->m = 0;
    int i, j;
    for (i = 1; i <= n ; i++)
        for (j = 1; j <= n ; j++)
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

int num[Max_Vertices], min_num[Max_Vertices], on_stack[Max_Vertices];
int k, check = 0;
Stack S;

int min(int a, int b)
{
    return (a > b ? b : a);
}

void SCC(Graph G, int x)
{
    num[x] = min_num[x] = k;
    k++;
    push_stack(&S, x);
    on_stack[x] = 1;

    int i;
    for (i = 1; i <= G.n; i++)
        if (adjacent(G, x, i))
        {
            if (num[i] < 0)
            {
                SCC(G, i);
                min_num[x] = min(min_num[x], min_num[i]);    
            }
            else if (on_stack[i]) 
                min_num[x] = min(min_num[x], num[i]);
        }

    if (num[x] == min_num[x])
    {
        check ++;
        int t;
        do 
        {
            t = top_Stack(S);
            pop_stack(&S);
            on_stack[x] = 0;
        } while (t != x);
    }
}

//================================================
int main ()
{
    make_null_stack(&S);
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
    {
        num[i] = min_num[i] = -1;
        on_stack[i] = 0;
    }
    
    for (i = 1; i <= n; i++)
        if (num[i] == -1) SCC(G, i);

    printf(check==1 ? "STRONG CONNECTED" : "DISCONNECTED");    

    return 0;
}

/* --- SHORT VERSION ---
#include <stdio.h>
#include <math.h>

#define Max_Vertices 100
#define NO_EDGE 0

typedef struct {
    int A[Max_Vertices][Max_Vertices];
    int n, m;
}Graph;

void init_graph(Graph *G, int n)
{
    G->m = 0;
    G->n = n;
    int i, j;
    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            G->A[i][j] = NO_EDGE;
}

void add_edge(Graph *G, int x, int y, int type)
{
    G->A[x][y] ++;
    G->m ++;  
    if (type == 2) G->A[y][x] ++;
}

int min_num[Max_Vertices], num[Max_Vertices], on_stack[Max_Vertices];
int k = 0, cnt = 0;
int stack[Max_Vertices], size = 0;

void SCC(Graph *G, int s)
{
    min_num[s] = num[s] = k++;
    on_stack[s] = 1;
    stack[size++] = s;

    int i;
    for (i = 1; i <= G->n; i++)
        if (G->A[s][i])
        {
            if (num[i] == -1)
            {
                SCC(G, i);
                min_num[s] = fmin(min_num[s], min_num[i]);
            }
            if (on_stack[i])
                min_num[s] = fmin(min_num[s], num[i]);
        }

    if (num[s] == min_num[s])
    {
        cnt ++;
        int temp;
        do {
            temp = stack[size--];
            on_stack[s] = 0;
        } while (temp != s);
    }
}
//======================================
int main ()
{
    Graph G;
    int n, m, u, v, type, i;
    
    scanf("%d %d", &n, &m);
    init_graph(&G, n);
    for (i = 1; i <= m; i++)
    {
       scanf("%d %d %d", &u, &v, &type);
       add_edge(&G, u, v, type);
    }

    for (i = 1; i <= G.n; i++)
    {
        on_stack[i] = 0;
        num[i] = min_num[i] = -1;
    }

    for (i = 1; i <= G.n; i++)
        if (num[i] == -1) SCC(&G, i);

    printf(cnt == 1 ? "OKIE" : "NO");

    return 0;
}

*/