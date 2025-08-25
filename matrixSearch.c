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

int cmp(const void *a, const void *b) {
    return (*(int*)a) - (*(int*)b);
}

int main(){
    int n;
    scanf("%d", &n);
    int arr[n*n];
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++) {
            scanf("%d", &arr[i*n + j]);
        }
    }
    qsort(arr, n*n, sizeof(int), cmp);
    int k;
    scanf("%d", &k);
    printf("%d\n", arr[k-1]);
    return 0;
}