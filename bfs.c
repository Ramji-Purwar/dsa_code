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

typedef struct Queue{
    node* f;
    node* r;
} qu;

qu* cq(){
    qu* q = malloc(sizeof(qu));
    q-> f = q-> r = NULL;
    return q;
}

bool qEmp(qu* q){
    return q-> f == NULL;
}

void qPush(qu* q, int x){
    node* new = cnode(x);
    if(qEmp(q)){
        q-> f = q-> r = new;
        return;
    }
    q-> r-> next = new;
    q-> r = new;
}

void qPop(qu* q){
    if(qEmp(q)) return;
    q-> f = q-> f -> next;
    if(qEmp(q)) q-> r = NULL;
}

int qF(qu* q){
    if(qEmp(q)) return -1;
    return q-> f-> val;
}

void bfs(graph* g){
    qu* q = cq();
    qPush(q, 0);
    g-> vis[0] = true;
    while(qEmp(q)){
        int v = qF(q); qPop(q);
        node* ch = g-> aj[v];
        while(ch != NULL){
            int el = ch-> val;
            if(!g-> vis[el]){
                g-> vis[el] = true;
                qPush(q, el);
            }
            ch = ch-> next;
        }
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
    bfs(g);
    return 0;
}