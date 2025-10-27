#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#define int long long
#define REP(i, a, b) for(int i = 0; i < b; i++)

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
} graph;

graph* cgraph(int n){
    graph* g = malloc(sizeof(graph));
    g-> n = n;
    g-> aj = malloc(n * sizeof(node*));
    g-> d = malloc(n * sizeof(int));
    REP(i, 0, n){
        g-> aj[i] = NULL;
        g-> d[i] = -1;
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
        if(el != p){
            g-> d[el] = g-> d[v] + 1;
            dfs(g, el, v);
        }
        ch = ch-> next;
    }
    free(ch);
}

int main(){
    int n;
    scanf("%lld", &n);
    graph* g = cgraph(n);
    REP(i, 1, n){
        int u, v;
        scanf("%lld %lld", &u, &v);
        addEdge(g, u-1, v-1);
    }
    
    g-> d[0] = 0;
    dfs(g, 0, -1);

    int v = 0;
    REP(i, 0, n)
        if(g-> d[i] > g-> d[v]) v = i;
    REP(i, 0, n) g-> d[i] = -1;
    dfs(g, v, -1);

    int dia = -1;
    REP(i, 0, n)
        if(g-> d[i] > dia) dia = g-> d[i];

    printf("%lld\n", dia+1);
    return 0;
}