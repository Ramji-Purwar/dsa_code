#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdint.h>
#include <time.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>
#include <float.h>
#include <ctype.h>

void swap(size_t *a, size_t *b){
    size_t temp = *a;
    *a = *b;
    *b = temp;
}

void reverse(size_t *arr, size_t start, size_t end){
    while(start < end){
        swap(&arr[start], &arr[end]);
        start++;
        end--;
    }
}

bool prev(size_t n, size_t *perm){
    int idx = -1;
    for(size_t i = n-1; i >= 1; i--){
        if(perm[i-1] > perm[i]){
            size_t j = n-1;
            while(perm[j] > perm[i-1]) j--;
            swap(&perm[i-1], &perm[j]);
            idx = i;
            break;
        }
    }
    if(idx == -1) return false;
    reverse(perm, idx, n-1);
    return true;
}

int main(){
    size_t n;
    scanf("%zu", &n);
    size_t p[n];
    for(size_t i = 0; i < n; i++){
        scanf("%zu", &p[i]);
    }
    bool res = prev(n, p);
    if(!res){
        printf("NOT POSSIBLE\n");
    }
    else{
        for(size_t i = 0; i < n; i++){
            printf("%zu ", p[i]);
        }
        printf("\n");
    }
    return 0;
}