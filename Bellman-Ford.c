#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#define int long long
#define REP(i, a, b) for(int i = a; i < b; i++)
const int INF = 1e14;

int main(){
    int n, m;
    scanf("%lld %lld", &n, &m);
    int e[m][3];
    REP(i, 0, m){
        scanf("%lld %lld %lld", &e[i][0], &e[i][1], &e[i][2]);
        e[i][0]--; e[i][1]--;
    }
    int dist[n];
    REP(i, 0, n) dist[i] = 0;
    
    int p[n];
    REP(i, 0, n) p[i] = -1;
    
    REP(i, 0, n){
        REP(j, 0, m){
            int a = e[j][0];
            int b = e[j][1];
            int wt = e[j][2];
            if(dist[b] > wt + dist[a]){
                dist[b] = dist[a] + wt;
                p[b] = a;
            }
        }
    }

    int st = -1;
    REP(i, 0, m){
        int a = e[i][0];
        int b = e[i][1];
        int wt = e[i][2];
        if(dist[b] > wt + dist[a]){
            dist[b] = dist[a] + wt;
            p[b] = a;
            st = b;
        }
    }

    if(st == -1){
        printf("NO\n");
        return 0;
    }
    
    REP(i, 0, n){
        st = p[st];
    }
    
    printf("YES\n");
    
    int cycle[n + 1];
    int idx = 0;
    int cur = st;
    
    do {
        cycle[idx++] = cur;
        cur = p[cur];
    } while(cur != st);
    
    cycle[idx] = st;
    
    for(int i = idx; i >= 0; i--){
        printf("%lld ", cycle[i] + 1);
    }
    printf("\n");
    
    return 0;
}