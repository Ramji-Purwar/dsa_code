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

bool le(size_t *p, size_t *q , size_t n){
    for(int i = 0; i < n; i++){
        if(p[i] >  q[i]) return false;
        if(p[i] < q[i]) return true;
    }
    return true;
}

int main(){
    size_t n;
    scanf("%zu", &n);
    size_t p[n], q[n];
    for(size_t i = 0; i < n; i++){
        scanf("%zu", &p[i]);
    }
    for(size_t i = 0; i < n; i++){
        scanf("%zu", &q[i]);
    }
    bool result = le(p, q, n);
    if(result){
        printf("YES\n");
    } else {
        printf("NO\n");
    }
    return 0;
}