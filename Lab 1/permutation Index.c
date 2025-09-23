#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005

int bit[MAXN];

void add(int x, int n) {
    for (; x <= n; x += x & -x) bit[x]++;
}

int sum(int x) {
    int s = 0;
    for (; x > 0; x -= x & -x) s += bit[x];
    return s;
}

long long fact[MAXN];

void precompute_fact(int n) {
    fact[0] = 1;
    for (int i = 1; i <= n; i++)
        fact[i] = fact[i - 1] * i;
}

long long find_idx(int *arr, int n) {
    memset(bit, 0, sizeof(int) * (n + 2));
    precompute_fact(n);
    long long idx = 0;
    for (int i = 0; i < n; i++) {
        int less = arr[i] - 1 - sum(arr[i] - 1);
        idx += less * fact[n - i - 1];
        add(arr[i], n);
    }
    return idx + 1;
}

int main() {
    int n;
    scanf("%d", &n);
    int *arr = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    long long idx = find_idx(arr, n);
    printf("%lld\n", idx);
    free(arr);
    return 0;
}