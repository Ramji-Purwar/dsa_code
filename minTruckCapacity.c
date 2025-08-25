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

bool check(int x, int d, int arr[], int n){
    int cur = 0;
    for(int i = 0; i < n; i++){
        if(cur + arr[i] > x){
            d--;
            cur = 0;
        }
        cur += arr[i];
    }
    return d >= 0;
}

int main(){
    int n, d;
    scanf("%d %d", &n, &d);
    int arr[n];
    for(int i = 0; i < n; i++){
        scanf("%d", &arr[i]);
    }
    int l = 1, r = n;
    while(r - l > 1){
        int m = (r + l) / 2;
        if(check(m)) r = m;
        else l = m - 1;
    }
    if(check(l)) printf("%d\n", l);
    else printf("%d\n", r);
    return 0;
}