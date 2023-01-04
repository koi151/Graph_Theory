#include <stdio.h>

#define Max_Vertices 100
#define WHITE 0
#define GRAY 1
#define BLACK 2

typedef struct {
    int A[Max_Vertices][Max_Vertices];
    int n, m;
}Graph;

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

int color[Max_Vertices], parent[Max_Vertices];
int has_cycle = 0, begin, end;

void DFS(Graph G, int x, int p)
{
    int i;
    color[x] = GRAY;
    parent[x] = p;

    for (i = 1; i <= G.n; i++)
    {
        if (adjacent(G, x, i))
        {
            if (i == p) continue;
            if (color[i] == WHITE)
                DFS(G, i, x);
            else if (color[i] == GRAY)
            {
                has_cycle ++;
                begin = x;
                end = i;
                
            }
        }
    }
    color[x] = BLACK;    
}

//======================================
int main()
{
    freopen("test.txt", "r", stdin);
	int n, m, u, v, i, j;
	scanf("%d %d", &n, &m);
	Graph G;
	init_Graph(&G, n);

	for (int i = 1; i <= m; i++)
    {
		scanf("%d %d", &u, &v);
		add_Edge(&G, u, v);
	}

	for (int i = 1; i <= n; i++)
    {
		color[i] = WHITE;
		parent[i] = -1;
	}
	
	for (int i = 1; i <= n; i++) 
		if (color[i] == WHITE) 
			DFS(G, i, -1);
	
	if (has_cycle != 0)
    {
        printf("Graph has cycle (and maybe more): ");
		int A[Max_Vertices];
		A[0] = begin;
		int b = begin, e = end;
        int i = 0;
		do 
        {
			b = parent[b];
			A[++i] = b;
		} while (b != e);

        for (int j = i; j >= 0; j--)
			printf("%d ", A[j]);
		printf("%d\n", A[i]);

	}
	else printf("Graph does not have cycle");
	return 0;
}

// int main()
// {
//     freopen("test.txt", "r", stdin);
// 	int n, m, u, v, i, j;
// 	scanf("%d %d", &n, &m);

// 	Graph G;
// 	init_Graph(&G, n);

// 	for (int i = 1; i <= m; i++)
//     {
// 		scanf("%d %d", &u, &v);
// 		add_Edge(&G, u, v);
// 	}

// 	for (int i = 1; i <= n; i++)
//     {
// 		color[u] = WHITE;
// 		parent[u] = -1;
// 	}

// 	for (i = 1; i <= n; i++)
// 		if (color[i] == WHITE) 
// 			DFS(G, i, -1);
	
// 	if (has_cycle != 0) 
//     {
// 		int A[Max_Vertices], i = 0;
// 		A[0] = begin;
// 		int u = begin, v = end;
// 		do
//         {
// 			u = parent[u];
			
// 			A[++i] = u;
// 		} while (u != v);

// 		for (int j = i; j >= 0; j--)
// 			printf("%d ", A[j]);

// 		printf("%d\n", A[i]);
// 	}
// 	else printf("-1");

// 	return 0;
// }