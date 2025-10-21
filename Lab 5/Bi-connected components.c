#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#define REP(i, a, b) for(int i = a; i < b; i++)

int timer = 0;

int min(int a, int b){
    if(a < b) return a;
    return b;
}

typedef struct Edge{
    int u, v;
} edge;

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
    int* d;
    int* l;
    bool* mark;
} graph;

graph* cgraph(int n){
    graph* g = malloc(sizeof(graph));
    g-> n = n;
    g-> aj = malloc(n * sizeof(node*));
    g-> d = malloc(n * sizeof(int));
    g-> l = malloc(n * sizeof(int));
    g-> mark = malloc(n * sizeof(bool));
    REP(i, 0, n){
        g-> aj[i] = NULL;
        g-> d[i] = g-> l[i] = -1;
        g-> mark[i] = false;
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

int cnt = 0;

void dfs(graph* g, int v, int p){
    g-> d[v] = g-> l[v] = cnt;
    node* ch = g-> aj[v];
    int degree = 0;
    while(ch != NULL){
        int el = ch-> val;
        if(el != p){
            if(g-> d[el] == -1){
                dfs(g, el, v);
                g->l[v] = min(g->l[v], g->l[el]);
                if(g-> l[el] >= g-> l[v] && p != -1) g-> mark[v] = true;
                degree++;
            }
            else{
                g-> l[v] = min(g->l[v], g->d[el]);
            }
        }
        ch = ch-> next;
    }
    if(p == -1 && degree > 1) g-> mark[v] = true;
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
}