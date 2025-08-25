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
    int n, m;
    scanf("%d %d", &n, &m);
    int arr[n + m];
    for(int i = 0; i < n + m; i++){
        scanf("%d", &arr[i]);
    }
    qsort(arr, n + m, sizeof(int), cmp);
    double med;
    if((n + m) & 1){
        med = arr[(n + m) / 2]; 
    }
    else{
        med = (arr[(n + m) / 2 - 1] + arr[(n + m) / 2]) / 2.0;
    }
    if(fabs(med - (int)med) < 1e-9) {
        printf("%d\n", (int)med);
    } 
    else{
        printf("%.1f\n", med);
    }
}