#include <stdio.h>
#include <stdlib.h>

struct Edge {
    int src, dest, weight;
};

struct Subset {
    int parent, rank;
};

int find(struct Subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

void Union(struct Subset subsets[], int x, int y) {
    int xr = find(subsets, x);
    int yr = find(subsets, y);

    if (subsets[xr].rank < subsets[yr].rank)
        subsets[xr].parent = yr;
    else if (subsets[xr].rank > subsets[yr].rank)
        subsets[yr].parent = xr;
    else {
        subsets[yr].parent = xr;
        subsets[xr].rank++;
    }
}

int compareEdges(const void* a, const void* b) {
    return ((struct Edge*)a)->weight - ((struct Edge*)b)->weight;
}

void KruskalMST(struct Edge edges[], int V, int E) {

    int total = 0;   
    int e = 0, i = 0;

    qsort(edges, E, sizeof(struct Edge), compareEdges);

    struct Subset* subsets = malloc(V * sizeof(struct Subset));
    for (int v = 0; v < V; v++) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    printf("\nMST:\n");

    while (e < V - 1 && i < E) {
        struct Edge next = edges[i++];
        int x = find(subsets, next.src);
        int y = find(subsets, next.dest);

        if (x != y) {
            printf("Edge selected: %d-%d\n", next.src + 1, next.dest + 1);
            total += next.weight;
            e++;
            Union(subsets, x, y);
        }
    }

    printf("\nTotal Cost of MST = %d\n", total);
    printf("\nMST Completed.\n");
}

int main() {

    int V;
    printf("Enter number of vertices: ");
    fflush(stdout);
    scanf("%d", &V);

    int matrix[V][V];
    int E = 0;

    printf("Enter adjacency matrix:\n");
    fflush(stdout);

    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            scanf("%d", &matrix[i][j]);
            if (matrix[i][j] != 0 && i < j)
                E++;
        }
    }

    struct Edge* edges = malloc(E * sizeof(struct Edge));
    int idx = 0;

    for (int i = 0; i < V; i++) {
        for (int j = i + 1; j < V; j++) {
            if (matrix[i][j] != 0) {
                edges[idx].src = i;
                edges[idx].dest = j;
                edges[idx].weight = matrix[i][j];
                idx++;
            }
        }
    }

    KruskalMST(edges, V, E);

    return 0;
}

