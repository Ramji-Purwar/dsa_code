#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <limits.h>
#define REP(i, a, b) for(int i = a; i < b; i++)
#define ll long long
const int INF = INT_MAX;

ll min_ll(ll a, ll b){
    return a > b ? b : a;
}

int n, m;
ll** dist;

int main(){
    scanf("%d %d", &n, &m);
    dist = malloc(n * sizeof(ll*));
    REP(i, 0, n){
        dist[i] = malloc(n * sizeof(ll));
        REP(j, 0, n){
            if(i == j) dist[i][j] = 0;
            else dist[i][j] = INF;
        }
    }

    REP(i, 0, m){
        int u, v;
        ll wt;
        scanf("%d %d %lld", &u, &v, &wt);
        dist[u][v] = min_ll(dist[u][v], wt);
    }

    REP(k, 0, n){
        REP(i, 0, n){
            REP(j, 0, n){
                dist[i][j] = min_ll(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
    return 0;
}
