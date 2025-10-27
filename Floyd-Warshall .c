#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#define int long long
#define REP(i, a, b) for(int i = a; i < b; i++)
const int INF = 1e14;

int min(int a, int b){
    return a > b ? b : a;
}

int main(){
    int n, m;
    scanf("%lld %lld", &n, &m);
    int** dist = malloc(n * sizeof(int*));
    REP(i, 0, n){
        dist[i] = malloc(n * sizeof(int));
        REP(j, 0, n){
            if(i == j) dist[i][j] = 0;
            else dist[i][j] = INF;
        }
    }

    REP(i, 0, m){
        int u, v, wt;
        scanf("%lld %lld %lld", &u, &v, &wt);
        dist[u][v] = min(dist[u][v], wt);
    }

    REP(k, 0, n){
        REP(i, 0, n){
            REP(j, 0, n){
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }

    REP(i, 0, n) free(dist[i]);
    free(dist);

    return 0;
}
