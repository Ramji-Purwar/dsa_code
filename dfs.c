#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#define REP(i, a, b) for(int i = a; i < b; i++)

typedef struct Node{
    int val;
    struct Node* next;
} node;

node* cnode(int x){
    node* new = malloc(sizeof(node));
    new-> val = x;
    new-> next = NULL;
    return new;
}

typedef struct Graph{
    int n;
    node** aj;
    bool* vis;
} graph;

graph* cgraph(int n){
    graph* g = malloc(sizeof(graph));
    g-> n = n;
    g-> aj = malloc(n * sizeof(node*));
    g-> vis = malloc(n * sizeof(bool));

    REP(i, 0, n){
        g-> aj[i] = NULL;
        g-> vis[i] = false;
    }
    return g;
}

void addEdge(graph* g, int u, int v){
    node* new = cnode(v);
    new-> next = g-> aj[u];
    g-> aj[u] = new;

    new = cnode(u);
    new-> next = g-> aj[v];
    g-> aj[v] = new;
}

void dfs(graph* g, int v){
    g-> vis[v] = true;
    printf("%d ", v);
    node* ch = g-> aj[v];
    while(ch != NULL){
        int el = ch-> val;
        if(!g-> vis[el]){
            dfs(g, el);
        }
        ch = ch-> next;
    }
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    graph* g = cgraph(n);
    REP(i, 0, m){
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(g, u, v);
    }
    dfs(g, 0);
    return 0;
}