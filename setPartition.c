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

int parts[10][10];
int sizes[10];

void print_partition(int k) {
    for (int i = 0; i < k; i++) {
        printf("{");
        for (int j = 0; j < sizes[i]; j++) {
            printf("%d", parts[i][j]);
            if (j < sizes[i] - 1) printf(", ");
        }
        printf("}");
        if (i < k - 1) printf(", ");
    }
    printf("\n");
}

void rec(int n, int k, int idx, int used) {
    if (idx > n) {
        if (used == k) print_partition(k);
        return;
    }
    for (int i = 0; i < k; i++) {
        int first = (sizes[i] == 0);
        parts[i][sizes[i]] = idx;
        sizes[i]++;
        rec(n, k, idx + 1, used + first);
        sizes[i]--;
        if (first) break;
    }
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    for (int i = 0; i < k; i++) sizes[i] = 0;
    rec(n, k, 1, 0);
    return 0;
}