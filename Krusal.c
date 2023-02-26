#include <stdio.h>

#define Max_Vertices 100
#define Max_Elements 100

//---GLOBAL VARIABLES---
int parent[Max_Vertices];

typedef struct {
    int u, v, w;
}Edge;

typedef struct {
    Edge edges[Max_Elements];
    int n, m;
}Graph;

void init_graph(Graph *G, int n)
{
    G->n = n;
    G->m = 0;
}

void add_edge(Graph *G, int u, int v, int w)
{
    G->edges[G->m].u = u;
    G->edges[G->m].v = v;
    G->edges[G->m].w = w;
    G->m ++;
    if (u != v)
    {
        G->edges[G->m].u = v;
        G->edges[G->m].v = u;
    }
}

//---SORTING---------------------
void Swap(Edge *a, Edge *b)
{
    Edge temp = *a;
    *a = *b;
    *b =temp;
}

void Insertion_sort(Graph *G)
{
    int i, j;
    int edge_lk, edge_li;
    for (i = 0; i < G->m-1; i++)
    {
        edge_li = i;
        edge_lk = G->edges[i].w;
        for (j = i+1; j < G->m; j++)
        {
            if (G->edges[j].w < edge_lk)
            {
                edge_lk = G->edges[j].w;
                edge_li = j;
            }   
        }
        Swap(&G->edges[edge_li], &G->edges[i]);
    }
}

void BubbleSort(Graph* pG) {
	for (int i = 0; i < pG->m - 1; i++) {
		for (int j = pG->m - 1; j > i; j--) {
			if (pG->edges[j].w < pG->edges[j - 1].w)
				Swap(&pG->edges[j], &pG->edges[j - 1]);
		}
	}
}

//------------------------------------
int find_root(int x)
{
    while (parent[x] != x)
        x = parent[x];
    return x;
}

void print_tree (Graph G)
{
    printf("**********\n");
    int i;
    for (i = 0; i < G.m; i++)
        printf("%d %d %d\n", G.edges[i].u, G.edges[i].v, G.edges[i].w);
}

int Krusal(Graph *G, Graph *pG)
{  
    Insertion_sort(G);
    print_tree(*G);
    int i;
    init_graph(pG, G->n);

    int u, v, w, sum_w = 0;
    int root_u, root_v;
    for (i = 0; i < G->m; i++)
    {
        u = G->edges[i].u;
        v = G->edges[i].v;
        w = G->edges[i].w;
        root_u = find_root(u); root_v = find_root(v);

        if (root_u != root_v)
        {
            add_edge(pG, u, v, w);
            sum_w += w;
            parent[root_v] = root_u; // convert 2 cycle part
        }
    }
    return sum_w;
}
//=======================================================
int main ()
{
    int n, m, u, v, w, i;
    Graph G, pG;

    scanf("%d %d", &n, &m);
    init_graph(&G, n);
    for (i = 1; i <= m; i++)
    {
        scanf("%d %d %d", &u, &v, &w);
        add_edge(&G, u, v, w);
    }

    for (i = 1; i <= G.n; i++)
        parent[i] = i;

    printf("%d\n", Krusal(&G, &pG));

    for (i = 0; i < pG.m; i++)
    {
        if (pG.edges[i].u <= pG.edges[i].v)
            printf("%d %d %d\n", pG.edges[i].u, pG.edges[i].v, pG.edges[i].w);
        else printf("%d %d %d\n", pG.edges[i].v, pG.edges[i].u, pG.edges[i].w);
    }
    return 0;
}