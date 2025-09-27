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
    bool visited;
};

struct Node* createGraph(int x){
    struct Node* newNode = malloc(sizeof(struct Node));
    newNode -> val = x;
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
}

int main(){
    
}