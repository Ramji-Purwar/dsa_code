#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#define REP(i, a, b) for(int i = a; i < b; i++)
#define N 200005

void swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

typedef struct Edge{
    int u;
    int v;
    int wt;
} edge;

int cmp(const void* x, const void* y){
    edge* a = (edge*)x;
    edge* b = (edge*)y;
    if(a->wt > b->wt) return 1;
    if(a->wt < b->wt) return -1;
    return 0;
}

int par[N];
int sz[N];

void make(int v){
    par[v] = v;
    sz[v] = 1;
}

int find(int v){
    if(par[v] == v) return v;
    return par[v] = find(par[v]);
}

void merge(int a, int b){
    a = find(a);
    b = find(b);
    if(a != b){
        if(sz[a] < sz[b]) swap(&a, &b);
        par[b] = a;
        sz[a] += sz[b];
    }
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    
    edge E[m];
    REP(i, 0, m)
        scanf("%d %d %d", &E[i].u, &E[i].v, &E[i].wt);
    qsort(E, m, sizeof(edge), cmp);

    REP(i, 1, n+1) make(i);

    int total = 0;
    REP(i, 0, m){
        if(find(E[i].u) == find(E[i].v)) continue;
        merge(E[i].u, E[i].v);
        total += E[i].wt;
        printf("%d %d\n", E[i].u, E[i].v);
    }
    printf("%d\n", total);

    return 0;
}