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

int permutation_index(const size_t *p, int n) {
    
}

int main() {
    int n;
    scanf("%d", &n);
    size_t p[n];
    for(int i = 0; i < n; i++){
        scanf("%zu", &p[i]);
    }
    int ans = permutation_index(p, n);
    printf("%d\n", ans);
    return 0;
}