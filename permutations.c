#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>
#include <assert.h>
#include <float.h>
#include <math.h>
#include <limits.h>
#include <ctype.h>

// void swap(int *a, int *b){
//     int temp = *a;
//     *a = *b;
//     *b = temp;
// }

void permutations(int *arr, int n, int *b, int k, int cur){
    if(cur == k){
        for(int i = 0; i < k; i++){
            printf("%d ", b[i]);
        }
        printf("\n");
    }
    for(int i = 0; i < n; i++){
        swap(&arr[0], &arr[i]);
        b[cur] = arr[0];
        permutations(arr + 1, n - 1, b, k, cur + 1);
        swap(&arr[0], &arr[i]);
    }
} 

int main(){
    int n, k;
    scanf("%d %d", &n, &k);
    int arr[n], b[k];
    for(int i = 0; i < n; i++)
        arr[i] = i;
    permutations(arr, n, b, k, 0);
    return 0;
}