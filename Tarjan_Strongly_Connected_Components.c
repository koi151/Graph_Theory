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