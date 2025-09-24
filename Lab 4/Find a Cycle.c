#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <limits.h>
#include <float.h>
#include <math.h>
#include <ctype.h>
#include <time.h>
#include <stddef.h>
#include <assert.h>

struct Node{
    int val;
    struct Node* next;
};

struct Graph{
    int N;
    struct Node** adjList;
    bool* visited;
};

struct Node* createNode(int val){
    struct Node* newNode = malloc(sizeof(struct Node));
    newNode -> val = val;
    newNode -> next = NULL;
    return newNode;
}

struct Graph* createGraph(int n){
    struct Graph* graph = malloc(sizeof(struct Graph));

    graph -> N = n;
    graph -> adjList = malloc(n * sizeof(struct Node*));
    graph -> visited = malloc(n * sizeof(bool));

    for(int i = 0; i < n; i++){
        graph -> visited[i] = false;
        graph -> adjList[i] = NULL;
    }

    return graph;
}

void addEdge(struct Graph* graph, int u, int v){
    struct Node* newNode = createNode(v);
    newNode -> next = graph -> adjList[u];
    graph -> adjList[u] = newNode;

    newNode = createNode(u);
    newNode -> next = graph -> adjList[v];
    graph -> adjList[v] = newNode;
}

void dfs(struct Graph* graph, int v){
    struct Node* child = graph -> adjList[v];
    graph -> visited[v] = true;
    printf("%d ", v);

    while(child != NULL){
        int el = child -> val;
        if(graph -> visited[el] == false){
            dfs(graph, el);
        }
        child = child -> next;
    }
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    struct Graph* g = createGraph(n);
    for(int i = 0; i < m; i++){
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(g, u, v);
    }
    dfs(g, 0);
}