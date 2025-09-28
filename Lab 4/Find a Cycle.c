#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <ctype.h>
#include <assert.h>
#include <time.h>
#include <math.h>
#include <limits.h>
#include <float.h>

struct Node {
    int val;
    struct Node *next;
};

struct Node* createNode(int x) {
    struct Node *newNode = malloc(sizeof(struct Node));
    newNode->val = x;
    newNode->next = NULL;
    return newNode;
}

struct Graph {
    int N;
    struct Node **adjList;
    bool *visited;
    int *parent;
    int *cycle;
    int cycle_length;
    bool cycle_found;
};

struct Graph* createGraph(int n) {
    struct Graph *graph = malloc(sizeof(struct Graph));
    graph->N = n;
    graph->adjList = malloc(n * sizeof(struct Node*));
    graph->visited = malloc(n * sizeof(bool));
    graph->parent = malloc(n * sizeof(int));
    graph->cycle = malloc(n * sizeof(int));
    graph->cycle_length = 0;
    graph->cycle_found = false;
    
    for (int i = 0; i < n; i++) {
        graph->adjList[i] = NULL;
        graph->visited[i] = false;
        graph->parent[i] = -1;
    }
    return graph;
}

void addEdge(struct Graph *graph, int u, int v) {
    struct Node *newNode = createNode(v);
    newNode->next = graph->adjList[u];
    graph->adjList[u] = newNode;
    
    newNode = createNode(u);
    newNode->next = graph->adjList[v];
    graph->adjList[v] = newNode;
}

void dfs(struct Graph *graph, int v, int par) {
    if (graph->cycle_found) return;
    
    graph->visited[v] = true;
    graph->parent[v] = par;
    
    struct Node *child = graph->adjList[v];
    while (child != NULL) {
        int neighbor = child->val;
        
        if (neighbor == par) {
            child = child->next;
            continue;
        }
        
        if (graph->visited[neighbor]) {
            graph->cycle_found = true;
            graph->cycle_length = 0;
            
            int current = v;
            while (current != neighbor) {
                graph->cycle[graph->cycle_length++] = current;
                current = graph->parent[current];
            }
            graph->cycle[graph->cycle_length++] = neighbor;
            graph->cycle[graph->cycle_length++] = v;
            
            return;
        } else {
            dfs(graph, neighbor, v);
            if (graph->cycle_found) return;
        }
        child = child->next;
    }
}

void findCycle(struct Graph *graph) {
    for (int i = 0; i < graph->N && !graph->cycle_found; i++) {
        if (!graph->visited[i]) {
            dfs(graph, i, -1);
        }
    }
    
    if (graph->cycle_found) {
        for (int i = 0; i < graph->cycle_length; i++) {
            printf("%d", graph->cycle[i] + 1);
            if (i < graph->cycle_length - 1) printf(" ");
        }
        printf("\n");
    } else {
        printf("N\n");
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    
    struct Graph *graph = createGraph(n);
    
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(graph, u - 1, v - 1);
    }
    
    findCycle(graph);
    return 0;
}
