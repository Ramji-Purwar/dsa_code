#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#define REP(i, a, b) for(int i = a; i < b; i++)
const int INF = 1e9 + 1;

////////////////////////////////////////////////////////////

typedef struct Pair{
    int fi;
    int se;
} pair;

typedef struct MinHeap{
    int n;
    int size;
    pair* arr;
} minHeap;

minHeap* cMinHeap(int n){
    minHeap* h = malloc(sizeof(minHeap));
    h-> n = n;
    h-> size = 0;
    h-> arr = malloc(n * sizeof(pair));
    return h;
}

void swap(pair* a, pair* b){
    pair temp = *a;
    *a = *b;
    *b = temp;
}

void heapifyUp(minHeap* h, int idx){
    while(idx > 0){
        int parent = (idx - 1) / 2;
        if(h->arr[idx].fi < h->arr[parent].fi){
            swap(&h->arr[idx], &h->arr[parent]);
            idx = parent;
        } else {
            break;
        }
    }
}

void heapifyDown(minHeap* h, int idx){
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;
    
    if(left < h-> size && h-> arr[left].fi < h-> arr[smallest].fi){
        smallest = left;
    }
    if(right < h-> size && h-> arr[right].fi < h-> arr[smallest].fi){
        smallest = right;
    }
    
    if(smallest != idx){
        swap(&h-> arr[idx], &h-> arr[smallest]);
        heapifyDown(h, smallest);
    }
}

void push(minHeap* h, int dist, int vertex){
    if(h-> size >= h-> n) return;
    
    h-> arr[h-> size].fi = dist;
    h-> arr[h-> size].se = vertex;
    heapifyUp(h, h-> size);
    h-> size++;
}

pair pop(minHeap* h){
    pair result = h-> arr[0];
    h-> size--;
    h-> arr[0] = h->arr[h->size];
    heapifyDown(h, 0);
    return result;
}

bool isEmpty(minHeap* h){
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
    new->val = x;
    new->wt = wt;
    new->next = NULL;
    return new; 
}

typedef struct Graph{
    int n;
    node** aj;
    int* vis;
    int* dist;
} graph;

graph* cgraph(int n){
    graph* g = malloc(sizeof(graph));
    
    g->n = n;
    g->aj = malloc(n * sizeof(node*));
    g->vis = malloc(n * sizeof(int));
    g->dist = malloc(n * sizeof(int));
    
    REP(i, 0, n){
        g->aj[i] = NULL;
        g->vis[i] = 0;
        g->dist[i] = INF;
    }
    return g;
}

void addEdge(graph* g, int u, int v, int wt){
    node* new = cnode(v, wt);
    new->next = g->aj[u];
    g->aj[u] = new;
    
    new = cnode(u, wt);
    new->next = g->aj[v];
    g->aj[v] = new;
}

void dijkstra(graph* g, int src){
    minHeap* pq = cMinHeap(g->n * 100);
   
    push(pq, 0, src);
    g->dist[src] = 0;

    while(!isEmpty(pq)){
        pair cur = pop(pq);
        int d = cur.fi;
        int v = cur.se;
        
        if(g-> vis[v]) continue;
        g->vis[v] = 1;
        
        node* ch = g-> aj[v];
        while(ch != NULL){
            int el = ch-> val;
            int wt = ch-> wt;
            
            if(!g-> vis[el] && g-> dist[v] + wt < g-> dist[el]){
                g-> dist[el] = g-> dist[v] + wt;
                push(pq, g-> dist[el], el);
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
        int x, y, wt;
        scanf("%d %d %d", &x, &y, &wt);
        addEdge(g, x-1, y-1, wt);
    }
    dijkstra(g, 0);
    return 0;
}