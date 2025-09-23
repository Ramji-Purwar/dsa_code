#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LAST 20
long long fact[MAX_LAST+1];

void precompute_fact() {
    fact[0] = 1;
    for (int i = 1; i <= MAX_LAST; i++)
        fact[i] = fact[i-1] * i;
}

void kth_perm(int *arr, int len, long long k) {
    int used[MAX_LAST] = {0};
    for (int i = 0; i < len; i++) {
        long long f = fact[len-i-1];
        int idx = k / f;
        k %= f;
        int cnt = 0;
        for (int j = 0; j < len; j++) {
            if (!used[j]) {
                if (cnt == idx) {
                    printf("%d ", arr[j]);
                    used[j] = 1;
                    break;
                }
                cnt++;
            }
        }
    }
}

int main() {
    int n;
    long long k;
    scanf("%d %lld", &n, &k);
    precompute_fact();
    if (n <= MAX_LAST) {
        int arr[MAX_LAST];
        for (int i = 0; i < n; i++) arr[i] = i+1;
        kth_perm(arr, n, k-1);
        printf("\n");
    } else {
        for (int i = 1; i <= n-MAX_LAST; i++) printf("%d ", i);
        int arr[MAX_LAST];
        for (int i = 0; i < MAX_LAST; i++) arr[i] = n-MAX_LAST+1+i;
        kth_perm(arr, MAX_LAST, k-1);
        printf("\n");
    }
    return 0;
}