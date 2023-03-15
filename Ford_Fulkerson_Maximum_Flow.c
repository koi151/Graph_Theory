#include <stdio.h>
#include <math.h>

#define Max_Vertices 100
#define NO_EDGE 0
#define INF 999999

typedef struct {
    int F[Max_Vertices][Max_Vertices]; // Flow matrix
    int C[Max_Vertices][Max_Vertices]; // Weighted input matrix
    int n, m;
}Graph;

typedef struct {
    int dir; // Direction of traversal when finding augmenting paths (+1, -1)
    int p; // Parent vertex of the vertex being examined on the augmenting path
    int sigma; // The maximum flow that can pass through the vertex being considered on the augmenting path.
}Label;

Label label[Max_Vertices];

void init_graph(Graph *G, int n)
{
    G->n = n;
    G->m = 0;
    int i, j;
    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            G->C[i][j] = 0;
}

void init_flow(Graph *G)
{
    int i, j;
    for (i = 1; i <= G->n; i++)
        for (j = 1; j <= G->n; j++)
            G->F[i][j] = 0;
}


int Ford_Fulkerson (Graph *G, int s, int t) // s: source node   i: sink node
{
    int i, j, max_flow = 0;
    init_flow(G);
    int Queue[Max_Vertices], front = 0, rear = 0;

    do {
        for (i = 1; i <= G->n; i++) // initialize default value of label
            label[i].dir = 0;

        // Initailize default value of source node
        label[s].dir = +1;
        label[s].p = s;
        label[s].sigma = INF;

        // Queue[Max_Vertices] = {0};
        rear = 0; front = 0; // make null queue
        Queue[rear++] = s; // enqueue

        int u, found = 0;
        while (front < rear)
        {
            u = Queue[front++]; // get value at front queue and dequeue. Using u to find all neighbour nodes that connected to u
           
            // Searching and augmenting flow direction
            for (j = 1; j <= G->n; j++)
                if (G->C[u][j] && !label[j].dir && G->F[u][j] < G->C[u][j])
                {
                   label[j].dir = +1;
                   label[j].p = u;
                   // Update the  maximum flow that can pass through node j
                   label[j].sigma = fmin(label[u].sigma, G->C[u][j] - G->F[u][j]); 
                   Queue[rear++] = j;
                }

            // searching and augmenting flow in REVERSE direction
            for (j = 1; j <= G->n; j++)
                if (G->C[j][u] && !label[j].dir && G->F[j][u] > 0)
                {
                    label[j].dir = -1;
                    label[j].p = u;
                    label[j].sigma = fmin(label[u].sigma, G->F[j][u]);
                    Queue[rear++] = j;
                }

            // Augmenting path found, break the loop
            if (label[t].dir)
            {
                found = 1;
                break;
            }
        }

            // Update max flow value
        if (found)
        {
            int sigma = label[t].sigma, temp = t;
            while (temp != s)
            {
                int p = label[temp].p;
                if (label[temp].dir > 0) G->F[p][temp] += sigma;
                else G->F[temp][p] -= sigma;
                temp = p;
            }
            max_flow += sigma;
        }
        else break;
    } while (1);
    return max_flow;
}

//============================================
int main ()
{
    int n, m, u, v, w, i;
    Graph G;

    scanf("%d %d", &n, &m);
    init_graph(&G, n);
    for (i = 1; i <= m; i++)
    {
        scanf("%d %d %d", &u, &v, &w);
        G.C[u][v] = w;
        G.m ++;
    }

    printf("Max flow: %d\n", Ford_Fulkerson(&G, 1, n));

    printf("S: ");
    for (i = 1; i <= G.n; i++)
        if (label[i].dir) printf("%d ", i); 

    printf("\nT: ");
    for (i = 1; i <= G.n; i++)
        if (!label[i].dir) printf("%d ", i);

    return 0;
}