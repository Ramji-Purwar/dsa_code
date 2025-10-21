#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Pair{
    int fi;
    int se;
} pair;

typedef struct MaxHeap{
    int n;
    int size;
    pair* arr;
} maxHeap;

maxHeap* cMaxHeap(int n){
    maxHeap* h = malloc(sizeof(maxHeap));
    h-> n = n;
    h-> size = 0;
    h-> arr = malloc(n * sizeof(pair));
    return h;
}

void pair_swap(pair* a, pair* b){
    pair temp = *a;
    *a = *b;
    *b = temp;
}

void heapifyMaxUp(maxHeap* h, int idx){
    while(idx > 0){
        int parent = (idx - 1) / 2;
        if(h->arr[idx].fi > h->arr[parent].fi){
            pair_swap(&h->arr[idx], &h->arr[parent]);
            idx = parent;
        } else {
            break;
        }
    }
}

void heapifyMaxDown(maxHeap* h, int idx){
    int largest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;
    
    if(left < h-> size && h-> arr[left].fi > h-> arr[largest].fi){
        largest = left;
    }
    if(right < h-> size && h-> arr[right].fi > h-> arr[largest].fi){
        largest = right;
    }
    
    if(largest != idx){
        pair_swap(&h-> arr[idx], &h-> arr[largest]);
        heapifyMaxDown(h, largest);
    }
}

void HPush(maxHeap* h, int dist, int vertex){
    if(h-> size >= h-> n) return;
    
    h-> arr[h-> size].fi = dist;
    h-> arr[h-> size].se = vertex;
    heapifyMaxUp(h, h-> size);
    h-> size++;
}

pair HPop(maxHeap* h){
    pair result = h-> arr[0];
    h-> size--;
    h-> arr[0] = h->arr[h->size];
    heapifyMaxDown(h, 0);
    return result;
}

bool HEmpty(maxHeap* h){
    return h->size == 0;
}

int main(){
    
    return 0;
}
