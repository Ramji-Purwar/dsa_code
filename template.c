#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>
#include <ctype.h>
#include <time.h>
#include <assert.h>
#include <stdint.h>
#include <stddef.h>

#define endl printf("\n");

// ================= Input Macros =================

#define scanInt(x)        scanf("%d", &(x))
#define scanLL(x)         scanf("%lld", &(x))
#define scanFloat(x)      scanf("%f", &(x))
#define scanDouble(x)     scanf("%lf", &(x))
#define scanChar(x)       scanf(" %c", &(x))
#define scanString(x)     scanf("%s", (x))
#define scanInt2(a, b)    scanf("%d %d", &(a), &(b))
#define scanInt3(a, b, c) scanf("%d %d %d", &(a), &(b), &(c))
#define scanLL2(a, b)     scanf("%lld %lld", &(a), &(b))
#define scanLL3(a, b, c)  scanf("%lld %lld %lld", &(a), &(b), &(c))

// ================= VECTOR TEMPLATE ==================

typedef struct { int *data; int size; int capacity; } Vector;
#define vectorInit(v)    do { (v).data = NULL; (v).size = 0; (v).capacity = 0; } while(0)
#define vectorSize(v)    ((v).size)
#define vectorEmpty(v)   ((v).size == 0)
#define vectorAt(v,i)    ((v).data[i])
#define vectorBack(v)    ((v).data[(v).size-1])
static inline void __vectorPushBack(Vector *v, int value) { 
    if (v->size == v->capacity) { 
        v->capacity = (v->capacity == 0 ? 4 : v->capacity * 2); 
        v->data = (int*) realloc(v->data, v->capacity * sizeof(int)); 
    } 
    v->data[v->size++] = value; 
}
static inline void __vectorPopBack(Vector *v) { if (v->size > 0) v->size--; }
#define vectorPushBack(v, x)   __vectorPushBack(&(v), (x))
#define vectorPopBack(v)       __vectorPopBack(&(v))

// ================= VECTOR OF VECTORS ==================

typedef struct { Vector *data; int size; int capacity; } VectorVec;
#define vectorVecInit(vv)   do { (vv).data = NULL; (vv).size = 0; (vv).capacity = 0; } while(0)
#define vectorVecSize(vv)   ((vv).size)
#define vectorVecAt(vv,i)   ((vv).data[i])
static inline void __vectorVecPushBack(VectorVec *vv, Vector value) { \
    if (vv->size == vv->capacity) { \
        vv->capacity = (vv->capacity == 0 ? 4 : vv->capacity * 2); \
        vv->data = (Vector*) realloc(vv->data, vv->capacity * sizeof(Vector)); \
    } \
    vv->data[vv->size++] = value; \
}
#define vectorVecPushBack(vv, x)   __vectorVecPushBack(&(vv),(x))

// ================= SORTING FUNCTIONS ==================

static inline int compare_asc(const void *a, const void *b) {
    int ia = *(const int*)a;
    int ib = *(const int*)b;
    return (ia > ib) - (ia < ib);
}

static inline int compare_desc(const void *a, const void *b) {
    int ia = *(const int*)a;
    int ib = *(const int*)b;
    return (ib > ia) - (ib < ia);
}

#define vectorSort(v)      qsort((v).data, (v).size, sizeof(int), compare_asc)
#define vectorSortDesc(v)  qsort((v).data, (v).size, sizeof(int), compare_desc)

// ================= VECTOR UTILITY FUNCTIONS ==================

void vectorClear(Vector *v) {
    v->size = 0;
}

void vectorDestroy(Vector *v) {
    if (v->data) {
        free(v->data);
        v->data = NULL;
    }
    v->size = 0;
    v->capacity = 0;
}

void vectorResize(Vector *v, int new_size, int default_value) {
    if (new_size > v->capacity) {
        v->capacity = new_size;
        v->data = (int*) realloc(v->data, v->capacity * sizeof(int));
    }
    
    for (int i = v->size; i < new_size; i++) {
        v->data[i] = default_value;
    }
    
    v->size = new_size;
}

// ================= VECTORVEC UTILITY FUNCTIONS ==================

void vectorVecClear(VectorVec *vv) {
    vv->size = 0;
}

void vectorVecDestroy(VectorVec *vv) {
    if (vv->data) {
        // First destroy all individual vectors
        for (int i = 0; i < vv->size; i++) {
            vectorDestroy(&vv->data[i]);
        }
        free(vv->data);
        vv->data = NULL;
    }
    vv->size = 0;
    vv->capacity = 0;
}

void vectorVecResize(VectorVec *vv, int new_size) {
    if (new_size > vv->capacity) {
        vv->capacity = new_size;
        vv->data = (Vector*) realloc(vv->data, vv->capacity * sizeof(Vector));
    }
    
    // Initialize new vectors if size is increasing
    for (int i = vv->size; i < new_size; i++) {
        vectorInit(vv->data[i]);
    }
    
    vv->size = new_size;
}

// ================== QUEUE ==================

typedef struct { int *data; int front; int rear; int size; int capacity; } Queue;

#define queueInit(q)    do { (q).data = NULL; (q).front = 0; (q).rear = 0; (q).size = 0; (q).capacity = 0; } while(0)
#define queueSize(q)    ((q).size)
#define queueEmpty(q)   ((q).size == 0)
#define queueFull(q)    ((q).size == (q).capacity)
#define queueFront(q)   ((q).data[(q).front])

static inline void __queuePush(Queue *q, int value) {
    if (q->size == q->capacity) {
        int new_capacity = (q->capacity == 0 ? 4 : q->capacity * 2);
        int *new_data = (int*) malloc(new_capacity * sizeof(int));
        
        // Copy existing elements in order
        for (int i = 0; i < q->size; i++) {
            new_data[i] = q->data[(q->front + i) % q->capacity];
        }
        
        if (q->data) free(q->data);
        q->data = new_data;
        q->front = 0;
        q->rear = q->size;
        q->capacity = new_capacity;
    }
    
    q->data[q->rear] = value;
    q->rear = (q->rear + 1) % q->capacity;
    q->size++;
}

static inline int __queuePop(Queue *q) {
    if (q->size == 0) {
        // Handle empty queue error
        return -1; // or handle error as needed
    }
    
    int value = q->data[q->front];
    q->front = (q->front + 1) % q->capacity;
    q->size--;
    return value;
}

#define queuePush(q, x)    __queuePush(&(q), (x))
#define queuePop(q)        __queuePop(&(q))

// ================= QUEUE UTILITY FUNCTIONS ==================

void queueClear(Queue *q) {
    q->front = 0;
    q->rear = 0;
    q->size = 0;
}

void queueDestroy(Queue *q) {
    if (q->data) {
        free(q->data);
        q->data = NULL;
    }
    q->front = 0;
    q->rear = 0;
    q->size = 0;
    q->capacity = 0;
}

// ================== GRAPH UTILITY FUNCTION ==================

void addEdge(VectorVec *adj, int u, int v) {
    vectorPushBack(vectorVecAt(*adj, u), v);
    vectorPushBack(vectorVecAt(*adj, v), u);
}

void dfs(VectorVec *adj, int st, bool visited[]) {
    visited[st] = true;

    Vector child = vectorVecAt(*adj, st);
    for (int i = 0; i < vectorSize(child); i++) {
        int el = vectorAt(child, i);
        if (!visited[el]) {
            dfs(adj, el, visited);
        }
    }
}

void bfs(VectorVec *adj, int st){
    int n = vectorVecSize(*adj);

    bool visited[n];
    memset(visited, false, n * sizeof(bool));
    Queue q;
    queueInit(q);

    visited[st] = true;
    queuePush(q, st);

    while (!queueEmpty(q)) {
        int node = queueFront(q);
        queuePop(q);

        Vector child = vectorVecAt(*adj, node);
        for (int i = 0; i < vectorSize(child); i++) {
            int el = vectorAt(child, i);
            if (!visited[el]) {
                visited[el] = true;
                queuePush(q, el);
            }
        }
    }
    
    queueDestroy(&q);
}

// ================= MAIN SOLUTION ==================

void testcase(){
    
    return;
}

signed main() {
    // freopen("Input.txt","r",stdin);
    // freopen("Output.txt","w",stdout);

    int tc = 1;
    // scanInt(tc);

    while (tc--) {
        testcase();
    }
    
    return 0;
}