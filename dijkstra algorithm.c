#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#define int long long
#define REP(i, a, b) for(int i = a; i < b; i++)
const int INF = 1e14;

////////////////////////////////////////////////////////////

typedef struct Pair{
    int fi;
    int se;
} pair;

typedef struct MinHeap{
    int capacity;
    int size;
    pair* arr;
} minHeap;

minHeap* cMinHeap(int initial_capacity){
    minHeap* h = malloc(sizeof(minHeap));
    h->capacity = initial_capacity;
    h->size = 0;
    h->arr = malloc(initial_capacity * sizeof(pair));
    return h;
}

void resizeHeap(minHeap* h){
    h->capacity *= 2;
    h->arr = realloc(h->arr, h->capacity * sizeof(pair));
    if(h->arr == NULL){
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
}

void pair_swap(pair* a, pair* b){
    pair temp = *a;
    *a = *b;
    *b = temp;
}

void heapifyMinUp(minHeap* h, int idx){
    while(idx > 0){
        int parent = (idx - 1) / 2;
        if(h->arr[idx].fi < h->arr[parent].fi){
            pair_swap(&h->arr[idx], &h->arr[parent]);
            idx = parent;
        } else {
            break;
        }
    }
}

void heapifyMinDown(minHeap* h, int idx){
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;
    
    if(left < h->size && h->arr[left].fi < h->arr[smallest].fi){
        smallest = left;
    }
    if(right < h->size && h->arr[right].fi < h->arr[smallest].fi){
        smallest = right;
    }
    
    if(smallest != idx){
        pair_swap(&h->arr[idx], &h->arr[smallest]);
        heapifyMinDown(h, smallest);
    }
}

void hPush(minHeap* h, int dist, int vertex){
    if(h->size >= h->capacity){
        resizeHeap(h);
    }
    
    h->arr[h->size].fi = dist;
    h->arr[h->size].se = vertex;
    heapifyMinUp(h, h->size);
    h->size++;
}

void freeHeap(minHeap* h){
    free(h->arr);
    free(h);
}

pair hPop(minHeap* h){
    pair result = h->arr[0];
    h->size--;
    h->arr[0] = h->arr[h->size];
    heapifyMinDown(h, 0);
    return result;
}

bool hEmpty(minHeap* h){
    return h->size == 0;
}

////////////////////////////////////////////////////////

typedef struct Node{
    int val;
    int wt;
    struct Node* next;
} node;

node* cnode(int x, int wt){
    node* new = malloc(sizeof(node));
    new-> val = x;
    new-> wt = wt;
    new-> next = NULL;
    return new; 
}

///////////////////////////////////////////////////////////

typedef struct Graph{
    int n;
    node** aj;
    int* vis;
    int* dist;
    int* p;
} graph;

graph* cgraph(int n){
    graph* g = malloc(sizeof(graph));
    
    g-> n = n;
    g-> aj = malloc(n * sizeof(node*));
    g-> vis = malloc(n * sizeof(int));
    g-> dist = malloc(n * sizeof(int));
    g-> p = malloc(n * sizeof(int));
    
    REP(i, 0, n){
        g-> aj[i] = NULL;
        g-> vis[i] = 0;
        g-> dist[i] = INF;
        g-> p[i] = -1;
    }
    return g;
}

void freeGraph(graph* g){
    for(int i = 0; i < g-> n; i++){
        node* it = g-> aj[i];
        while(it){
            node* tmp = it-> next;
            free(it);
            it = tmp;
        }
    }
    free(g-> aj);
    free(g-> vis);
    free(g-> dist);
    free(g-> p);
    free(g);
}

void addEdge(graph* g, int u, int v, int wt){
    node* new = cnode(v, wt);
    new-> next = g-> aj[u];
    g-> aj[u] = new;
    
    new = cnode(u, wt);
    new-> next = g-> aj[v];
    g-> aj[v] = new;
}

//////////////////////////////////////////////////////////////

void dijkstra(graph* g, int src){
    minHeap* pq = cMinHeap(g-> n * 10);
   
    hPush(pq, 0, src);
    g-> dist[src] = 0;

    while(!hEmpty(pq)){
        pair cur = hPop(pq);
        int u = cur.se;
        
        if(g-> vis[u]) continue;
        g-> vis[u] = 1;
        
        node* ch = g-> aj[u];
        while(ch != NULL){
            int v = ch-> val;
            int wt = ch-> wt;
            
            if(!g-> vis[v] && g-> dist[u] + wt < g-> dist[v]){
                g-> dist[v] = g-> dist[u] + wt;
                g-> p[v] = u;
                hPush(pq, g-> dist[v], v);
            }
            ch = ch-> next;
        }
    }

    freeHeap(pq);
}

//////////////////////////////////////////////////////////////////

int main(){
    int n, m;
    scanf("%lld %lld", &n, &m);
    graph* g = cgraph(n);
    REP(i, 0, m){
        int x, y, wt;
        scanf("%lld %lld %lld", &x, &y, &wt);
        addEdge(g, x, y, wt);
    }

    freeGraph(g);
    return 0;
}