#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX 107

bool visited[MAX];
int edges[MAX];
char words[3][15];
int adj[MAX][MAX];
char x[MAX][3][15];

void addEdges(int v, int w) {
    adj[v][edges[v]++] = w;
}

void addWords(int v, int t1, int t2) {
    for (int i = 0; i < v; ++i) {
        if (visited[i]) {
            if (edges[i] < t1) {
                strcpy(x[i][edges[i]], words[0]);
            }
            else if (edges[i] < t2) {
                strcpy(x[i][edges[i]], words[1]);
            }
            else {
                strcpy(x[i][edges[i]], words[2]);
            }
        }
        else {
            strcpy(x[i][edges[i]], words[0]);
        }
    }
}

void bfs(int s) {
    int mQ[MAX];
    int front = 0, rear = 0;
    memset(visited, 0, sizeof(visited));
    visited[s] = true;
    mQ[rear++] = s;
    while (front < rear) {
        s = mQ[front++];
        for (int i = 0; i < edges[s]; ++i) {
            if (!visited[adj[s][i]]) {
                visited[adj[s][i]] = true;
                mQ[rear++] = adj[s][i];
            }
        }
    }
}

int main() {
    int n, a, t1, t2;
    char name[15];

    while (scanf("%d", &n), n) {
        memset(edges, 0, sizeof(edges));
        memset(adj, 0, sizeof(adj));
        memset(x, 0, sizeof(x));
        memset(visited, 0, sizeof(visited));
        for (int i = 0; i < n; ++i)
            while (scanf("%d", &a), a)
                addEdges(i, a - 1);
        while (scanf("%d", &a), a) {
            bfs(a - 1);
            scanf("%d %d", &t1, &t2);
            for (int i = 0; i < 3; ++i) {
                scanf("%s", words[i]);
            }
            addWords(n, t1, t2);
        }
        for (int i = 0; i < n; ++i) {
            scanf("%s", name);
            printf("%s: ", name);
            for (int it = 0; it < edges[i]; ++it) {
                printf("%s ", x[i][it]);
            }
            printf("\n");
        }
    }

    return 0;
}
