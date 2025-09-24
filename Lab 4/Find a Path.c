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
    int* depth;
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
    g -> depth = malloc(n * sizeof(int));

    for(int i = 0; i < n; i++){
        g -> adjList[i] = NULL;
        g -> depth[i] = -1;
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

struct Queue{
    struct Node* front;
    struct Node* rear;
};

struct Queue* createQueue(){
    struct Queue* q = malloc(sizeof(struct Queue));
    q -> front = q -> rear = NULL;
    return q;
}

void qPush(struct Queue* q, int x){
    struct Node* newNode = createNode(x);
    if(q -> rear == NULL){
        q -> front = q -> rear = newNode;
        return;
    }
    q -> rear -> next = newNode;
    q -> rear = newNode;
}

bool qEmpty(struct Queue* q){
    if(q -> front == NULL) 
        return true;
    return false; 
}

void qPop(struct Queue* q){
    if(qEmpty(q))
        return;
    struct Node* temp = q -> front;
    q -> front  = q -> front -> next;
    if(q -> front == NULL)
        q -> rear = NULL;
    free(temp);
}

int qFront(struct Queue* q){
    if(qEmpty(q))
        return -1;
    return q -> front -> val;
}

void bfs(struct Graph* g, int st){
    struct Queue* q = createQueue();
    qPush(q, st);
    g -> depth[st] = 0;
    while(!qEmpty(q)){
        int el = qFront(q);
        qPop(q);
        struct Node* child = g -> adjList[el];
        while(child != NULL){
            int x = child -> val;
            if(g -> depth[x] == -1){
                qPush(q, x);
                g -> depth[x] = g -> depth[el] + 1;
            }
            child = child -> next;
        }
    }
    free(q);
}

void dfs(struct Graph* g, int v, int en, int* path){
    int d = g -> depth[v];
    path[d] = v;
    if(!d){
        return;
    }
    struct Node* child = g -> adjList[v];
    while(child != NULL){
        int x = child -> val;
        if(g -> depth[x] + 1 == d){
            dfs(g, x, en, path);
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
    int u, v;
    scanf("%d %d", &u, &v);
    bfs(g, u);
    int k = g -> depth[v];
    if(k == -1){
        printf("N\n");
        return 0;
    }
    int path[k + 1];
    dfs(g, v, u, path);
    for(int i = 0; i < k+1; i++){
        printf("%d ", path[i]);
    }
    printf("\n");
    return 0;
}