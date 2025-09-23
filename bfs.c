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

struct Queue{
    struct Node *front;
    struct Node *rear;
};

struct Queue* createQueue(){
    struct Queue *queue = malloc(sizeof(struct Queue));
    queue -> front = queue -> rear = NULL;
    return queue; 
}

void qPush(struct Queue* queue, int val){
    struct Node *newNode = createNode(val);
    if(queue -> rear == NULL){
        queue -> front = queue -> rear = newNode;
        return;
    }
    queue -> rear -> next = newNode;
    queue -> rear = newNode;
}

bool qEmpty(struct Queue* queue){
    if(queue -> front == NULL)
        return true;
    return false;
}

void qPop(struct Queue* queue){
    if(qEmpty(queue))
        return;
    struct Node *temp = queue->front;
    queue -> front = queue -> front -> next;
    if(queue -> front == NULL)
        queue->rear = NULL;
    free(temp);
}

int qFront(struct Queue* queue){
    if(qEmpty(queue))
        return -1;
    return queue -> front -> val;
}

void bfs(struct Graph* graph){
    struct Queue* q = createQueue();
    qPush(q, 0);
    graph -> visited[0] = true;
    while(!qEmpty(q)){
        int el = qFront(q);
        qPop(q);
        struct Node* child = graph -> adjList[el];
        while(child != NULL){
            int x = child -> val;
            if(graph -> visited[x] == false){
                qPush(q, x);
                graph -> visited[x] = true;
            }
            child = child -> next;
        }
    }
}

int main(){
    int n = 5;
    struct Graph *graph = createGraph(n);
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 2, 3);
    addEdge(graph, 2, 4);
    bfs(graph);
}