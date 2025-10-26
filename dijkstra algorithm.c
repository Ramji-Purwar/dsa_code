#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#define REP(i, a, b) for(int i = a; i < b; i++)
#define ll long long
const ll INF = 1e18;

////////////////////////////////////////////////////////////

typedef struct Pair{
    ll fi;
    ll se;
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

void hPush(minHeap* h, ll dist, ll vertex){
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
    ll val;
    ll wt;
    struct Node* next;
} node;

node* cnode(ll x, ll wt){
    node* new = malloc(sizeof(node));
    new->val = x;
    new->wt = wt;
    new->next = NULL;
    return new; 
}

///////////////////////////////////////////////////////////

typedef struct Graph{
    int n;
    node** aj;
    int* vis;
    ll* dist;
    int* p;
} graph;

graph* cgraph(int n){
    graph* g = malloc(sizeof(graph));
    
    g->n = n;
    g->aj = malloc(n * sizeof(node*));
    g->vis = malloc(n * sizeof(int));
    g->dist = malloc(n * sizeof(ll));
    g->p = malloc(n * sizeof(int));
    
    REP(i, 0, n){
        g->aj[i] = NULL;
        g->vis[i] = 0;
        g->dist[i] = INF;
        g->p[i] = -1;
    }
    return g;
}

void addEdge(graph* g, int u, int v, ll wt){
    node* new = cnode(v, wt);
    new->next = g->aj[u];
    g->aj[u] = new;
    
    new = cnode(u, wt);
    new->next = g->aj[v];
    g->aj[v] = new;
}

//////////////////////////////////////////////////////////////

void dijkstra(graph* g, int src){
    minHeap* pq = cMinHeap(g->n * 10);
   
    hPush(pq, 0, src);
    g->dist[src] = 0;

    while(!hEmpty(pq)){
        pair cur = hPop(pq);
        ll d = cur.fi;
        int v = cur.se;
        
        if(g->vis[v]) continue;
        g->vis[v] = 1;
        
        node* ch = g->aj[v];
        while(ch != NULL){
            int el = ch->val;
            ll wt = ch->wt;
            
            if(!g->vis[el] && g->dist[v] + wt < g->dist[el]){
                g->dist[el] = g->dist[v] + wt;
                g->p[el] = v;
                hPush(pq, g->dist[el], el);
            }
            ch = ch->next;
        }
    }

    if(pq){
        if(pq->arr) free(pq->arr);
        free(pq);
    }
}

//////////////////////////////////////////////////////////////////

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    graph* g = cgraph(n);
    REP(i, 0, m){
        int x, y;
        ll wt;
        scanf("%d %d %lld", &x, &y, &wt);
        addEdge(g, x, y, wt);
    }

    return 0;
}