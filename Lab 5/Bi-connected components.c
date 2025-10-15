#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#define REP(i, a, b) for(int i = a; i < b; i++)

int min(int a, int b){
    if(a < b) return a;
    return b;
}

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
} graph;

graph* cgraph(int n){
    graph* g = malloc(sizeof(graph));
    g-> n = n;
    g-> aj = malloc(n * sizeof(node*));
    g-> d = malloc(n * sizeof(int));
    g-> l = malloc(n * sizeof(int));
    REP(i, 0, n){
        g-> aj[i] = NULL;
        g-> d[i] = g-> l[i] = -1;
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

void dfs(graph* g, int v, int p){
    node* ch = g-> aj[v];
    while(ch != NULL){
        int el = ch-> val;
        if(g-> d[el] == -1){
            g-> d[el] = g-> l[el] = g-> d[v] + 1;
            dfs(g, el, v);
        }
        ch = ch-> next;
    }
    ch = g-> aj[v];
    while(ch != NULL){
        int el = ch-> val;
        if(el != p) g->l[v] = min(g->l[v], g->l[el]);
        ch = ch-> next;
    }
}

void dfs2(graph* g, int v){
    node* ch = g-> aj[v];
    g-> d[v] = 1;
    while(ch != NULL){
        int el = ch-> val;
        if(g-> d[el] == 0 && g-> l[el] == g-> l[v]){
            dfs2(g, el);
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

    g->d[0] = g->l[0] = 0;
    dfs(g, 0, -1);

    REP(i, 0, n) g-> d[i] = 0;

    int cnt = 1;
    REP(i, 0, n){
        if(g-> d[i] == 0){
            dfs2(g, i);
            cnt++;
        }
    }
    
    printf("%d\n", cnt);
    return 0;
}