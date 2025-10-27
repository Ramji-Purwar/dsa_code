#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#define int long long
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
    bool* mark;
    int num_biconnected;
} graph;

graph* cgraph(int n){
    graph* g = malloc(sizeof(graph));
    g-> n = n;
    g-> aj = malloc(n * sizeof(node*));
    g-> d = malloc(n * sizeof(int));
    g-> l = malloc(n * sizeof(int));
    g-> mark = malloc(n * sizeof(bool));
    g-> num_biconnected = 0;
    
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

int cnt;
void dfs(graph* g, int v, int p){
    g-> d[v] = g-> l[v] = cnt++;
    node* ch = g-> aj[v];
    int children = 0;
    
    while(ch != NULL){
        int el = ch-> val;
        if(el != p){
            if(g-> d[el] == -1){
                children++;
                dfs(g, el, v);
                g-> l[v] = min(g-> l[v], g-> l[el]);
                
                if(g-> l[el] >= g-> d[v] && p != -1){
                    g-> mark[v] = true;
                    g-> num_biconnected++;
                }
            }
            else{
                g-> l[v] = min(g-> l[v], g-> d[el]);
            }
        }
        ch = ch-> next;
    }
    
    if(p == -1 && children > 0){
        if(children > 1){
            g-> mark[v] = true;
        }
        g-> num_biconnected += children;
    }
}

int main(){
    int n, m;
    scanf("%lld %lld", &n, &m);
    graph* g = cgraph(n);
    
    REP(i, 0, m){
        int u, v;
        scanf("%lld %lld", &u, &v);
        addEdge(g, u-1, v-1);
    }
    
    REP(i, 0, n){
        if(g-> d[i] == -1){
            cnt = 0;
            dfs(g, i, -1);
        }
    }
    printf("%lld\n", g-> num_biconnected);
    return 0;
}