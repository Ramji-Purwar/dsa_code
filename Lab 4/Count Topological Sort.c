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
    int* degree;
};

struct Node* createNode(int x){
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
    g -> degree = malloc(n * sizeof(int));

    for(int i = 0; i < n; i++){
        g -> adjList[i] = NULL;
        g -> visited[i] = false;
        g -> degree[i] = 0;
    }

    return g;
}

void addEdge(struct Graph* g, int u, int v){
    struct Node* newNode = createNode(v);
    newNode -> next = g -> adjList[u];
    g -> adjList[u] = newNode;
    g -> degree[v]++;
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

int countTopologicalSorts(struct Graph* g, int* currentSort, int index){
    int available[g -> N];
    int availableCount = 0;
    
    for(int i = 1; i < g->N; i++){
        if(g -> degree[i] == 0 && g -> visited[i] == false){
            available[availableCount++] = i;
        }
    }
    
    if(availableCount == 0){
        return (index == g -> N-1) ? 1 : 0;
    } 
    
    int totalCount = 0;
    for(int i = 0; i < availableCount; i++) {
        int v = available[i];
        
        currentSort[index] = v;
        g -> visited[v] = true;
        g -> degree[v] = -1;
        
        struct Node* child = g -> adjList[v];
        while(child != NULL) {
            g->degree[child->val]--;
            child = child->next;
        }
        
        totalCount += countTopologicalSorts(g, currentSort, index + 1);
        
        child = g -> adjList[v];
        while(child != NULL) {
            g -> degree[child -> val]++;
            child = child -> next;
        }
        
        g -> degree[v] = 0;
        g -> visited[v] = false;
    }
    
    return totalCount;
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    struct Graph* g = createGraph(n + 1);
    for(int i = 0; i < m; i++){
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(g, u, v);
    }
    
    int* currentSort = malloc(n * sizeof(int));
    int ans = countTopologicalSorts(g, currentSort, 0);
    
    printf("%d\n", ans);
    return 0;
}