#include <stdio.h>

#define MAX 20

int adj[MAX][MAX];
int visited[MAX];
int stack[MAX], top = -1;
int queue[MAX], front = -1, rear = -1;

void DFS(int start, int n) {
    int i, k;
    for (i = 0; i < n; i++)
        visited[i] = 0;

    top = -1;
    stack[++top] = start;
    visited[start] = 1;

    printf("DFS: %d ", start + 1);

    while (top >= 0) {
        k = stack[top];
        int found = 0;

        for (i = n - 1; i >= 0; i--) {
            if (adj[k][i] == 1 && visited[i] == 0) {
                stack[++top] = i;
                visited[i] = 1;
                printf("%d ", i + 1);
                found = 1;
                break;
            }
        }

        if (!found)
            top--;
    }
    printf("\n");
}

void BFS(int start, int n) {
    int i, k;
    for (i = 0; i < n; i++)
        visited[i] = 0;

    front = rear = -1;
    queue[++rear] = start;
    visited[start] = 1;

    printf("BFS: %d ", start + 1);

    while (front != rear) {
        k = queue[++front];

        for (i = 0; i < n; i++) {
            if (adj[k][i] == 1 && visited[i] == 0) {
                queue[++rear] = i;
                visited[i] = 1;
                printf("%d ", i + 1);
            }
        }
    }
    printf("\n");
}

int main() {
    int n, i, j, start;

    printf("N: ");
    scanf("%d", &n);

    printf("Mat:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%d", &adj[i][j]);
        }
    }

    printf("Start: ");
    scanf("%d", &start);
    start--;

    BFS(start, n);
    DFS(start, n);

    return 0;
}

