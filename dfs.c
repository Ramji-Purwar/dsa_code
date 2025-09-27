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

struct Node{
    int val;
    struct Node *next;
};

struct Graph{
    int N;
    struct Node **adjList;
    bool *visited;
};

struct Node* createNode(int val){
    struct Node *newNode = malloc(sizeof(struct Node));
    newNode -> val = val;
    newNode -> next = NULL;
    return newNode;
}

struct Graph* createGraph(int n){
    struct Graph *graph = malloc(sizeof(struct Graph));

    graph -> N = n;
    graph -> adjList = malloc(n * sizeof(struct Node*));
    graph -> visited = malloc(n * sizeof(bool));

    for(int i = 0; i < n; i++){
        graph -> adjList[i] = NULL;
        graph -> visited[i] = false;
    }

    return graph;
}

void addEdge(struct Graph *graph, int u, int v){
    struct Node *newNode = createNode(v);
    newNode -> next = graph -> adjList[u];
    graph -> adjList[u] = newNode;

    newNode = createNode(u);
    newNode -> next = graph -> adjList[v];
    graph -> adjList[v] = newNode;
}

void dfs(struct Graph *graph, int v){
    struct Node *child = graph -> adjList[v];
    graph -> visited[v]  = true;
    while(child != NULL){
        int el = child -> val;
        if(graph -> visited[el] == false){
            dfs(graph, el);
        }
        child = child -> next;
    }
}

int main(){
    int n = 5;
    struct Graph *graph = createGraph(n);
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 2, 3);
    addEdge(graph, 2, 4);
    dfs(graph, 0);
}