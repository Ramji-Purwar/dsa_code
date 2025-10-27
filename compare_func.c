#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#define int long long
#define REP(i, a, b) for(int i = a; i < b; i++)

typedef struct Pair{
    int fi;
    int se;
} pair;

int cmp(const void* x, const void* y){
    pair* a = (pair*)x;
    pair* b = (pair*)y;
    if(a->fi != b->fi)
        return a->fi - b->fi;
    return a->se - b->se;
}

int main(){
    int n;
    scanf("%lld", &n);
    pair* v = malloc(n * sizeof(pair));
    REP(i, 0, n){
        scanf("%d %d", &v[i].fi, &v[i].se);
    }
    qsort(v, n, sizeof(pair), cmp);
    for(int i = 0; i < n; i++){
        printf("%lld %lld\n", v[i].fi, v[i].se);
    }
    return 0;
}