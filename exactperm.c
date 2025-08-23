#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005

long long fact[MAXN];

void precompute_fact(int n) {
    fact[0] = 1;
    for (int i = 1; i <= n; i++)
        fact[i] = fact[i - 1] * i;
}

int main() {
    int n;
    long long k;
    scanf("%d %lld", &n, &k);

    precompute_fact(n);

    int *used = (int *)calloc(n + 1, sizeof(int));
    int *perm = (int *)malloc(n * sizeof(int));

    k--;

    for (int i = 0; i < n; i++) {
        int cnt = 0;
        for (int j = 1; j <= n; j++) {
            if (used[j]) continue;
            if (k < fact[n - i - 1]) {
                perm[i] = j;
                used[j] = 1;
                break;
            }
            k -= fact[n - i - 1];
        }
    }

    for (int i = 0; i < n; i++)
        printf("%d%c", perm[i], i == n - 1 ? '\n' : ' ');

    free(used);
    free(perm);
    return 0;
}