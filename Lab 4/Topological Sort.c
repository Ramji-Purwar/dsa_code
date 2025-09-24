#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stddef.h>
#include <float.h>
#include <limits.h>
#include <math.h>
#include <assert.h>

struct pair{
    int first;
    int second;
};

int cmp(const void *a, const void *b) {
    const struct pair *pa = (const struct pair *)a;
    const struct pair *pb = (const struct pair *)b;
    if (pa->second != pb->second)
        return pa->second - pb->second;
    return pa->first - pb->first;
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    struct pair to[n+1];
    for(int i = 0; i <= n; i++){
        to[i].first = i;
        to[i].second = 0;
    }
    for(int i = 0; i < m; i++){
        int u, v;
        scanf("%d %d", &u, &v);
        to[v].second++;
    }
    qsort(to, n + 1, sizeof(struct pair), cmp);
    for (int i = 1; i <= n; i++) {
        printf("%d ", to[i].first);
    }
    printf("\n");
}