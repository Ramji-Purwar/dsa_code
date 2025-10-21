#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

int main(){
    
    return 0;
}