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

int main(){
    int n;
    scanf("%d", &n);
    int arr[n];
    for(int i = 0; i < n; i++){
        scanf("%d", &arr[i]);
    }
    int v;
    scanf("%d ", &v);
    for(int i = 0; i < n; i++){
        if(arr[i] == v){
            printf("%d\n", i);
            return 0;
        }
    }
    printf("%d\n", -1);
    return 0;
}