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
}

struct Stack{
    struct Node* top;
};

struct Stack* createStack(){
    struct Stack* st = malloc(sizeof(struct Stack));
    st -> top = NULL;
    return st;
}

void sPush(struct Stack* st, int x){
    struct Node* newNode = createNode(x);
    newNode -> next = st -> top;
    st -> top = newNode;
}

bool sEmpty(struct Stack* st){
    return st -> top == NULL;
}

void sPop(struct Stack* st){
    if(sEmpty(st))
        return;
    struct Node* temp = st -> top;
    st -> top = temp -> next;
    free(temp);
}

int sTop(struct Stack* st){
    if(sEmpty(st))
        return -1;
    return st -> top -> val;
}

void dfs(struct Graph *graph, struct Stack* st, int v){
    struct Node *child = graph -> adjList[v];
    graph -> visited[v]  = true;
    while(child != NULL){
        int el = child -> val;
        if(graph -> visited[el] == false){
            dfs(graph, st, el);
        }
        child = child -> next;
    }
    sPush(st, v);
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
    struct Stack* st = createStack();
    int ans[n];
    int idx = 0;
    for(int i = 1; i < n+1; i++){
        if(g -> visited[i] == false){
            dfs(g, st, i);
        }
    }
    while(!sEmpty(st)){
        printf("%d ", sTop(st));
        sPop(st);
    }
    printf("\n");
}