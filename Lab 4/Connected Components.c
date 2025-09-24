#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <float.h>
#include <limits.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>
#include <time.h>

struct Node{
    int val;
    struct Node* next;
};

struct Graph{
    int N;
    struct Node** adjList;
    bool* visited;
};

struct Node* createNode(int v){
    struct Node* newNode = malloc(sizeof(struct Node));
    newNode -> val = v;
    newNode -> next = NULL;
    return newNode;
}

struct Graph* createGraph(int n){
    struct Graph* g = malloc(sizeof(struct Graph));
    g -> N = n;
    g -> adjList = malloc(n * sizeof(struct Node*));
    g -> visited = malloc(n * sizeof(bool));

    for(int i = 0; i < n; i++){
        g -> adjList[i] = NULL;
        g -> visited[i] = false;
    }

    return g;
}

void addEdge(struct Graph* g, int u, int v){
    struct Node* newNode = createNode(v);
    newNode -> next = g -> adjList[u];
    g -> adjList[u] = newNode; 

    newNode = createNode(u);
    newNode -> next = g -> adjList[v];
    g -> adjList[v] = newNode; 
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
    int n, m;
    scanf("%d %d", &n, &m);
    struct Graph* g = createGraph(n+1);
    for(int i = 0; i < m; i++){
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(g, u, v);
    }
    int cnt = 0;
    for(int i = 1; i < n+1; i++){
        if(g -> visited[i] == false){
            dfs(g, i);
            cnt++;
        }
    }
    printf("%d\n", cnt);
    return 0;
}