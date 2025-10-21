#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#define REP(i, a, b) for(int i = a; i < b; i++)

typedef struct Pair{
    int fi;
    int se;
} pair;

typedef struct Node{
    int fi; 
    int se;
    struct Node* next;
} node;

node* cnode(int x, int y){
    node* new = malloc(sizeof(node));
    new-> fi = x;
    new-> se = y;
    new-> next = NULL;
    return new;
}

typedef struct Queue{
    node* f;
    node* r;
} qu;

qu* cq(){
    qu* q = malloc(sizeof(qu));
    q-> f = q-> r = NULL;
    return q;
}

bool qEmp(qu* q){
    return q-> f == NULL;
}

void qPush(qu* q, int x, int y){
    node* new = cnode(x, y);
    if(qEmp(q)){
        q-> f = q-> r = new;
        return;
    }
    q-> r-> next = new;
    q-> r = new;
}

void qPop(qu* q){
    if(qEmp(q)) return;
    q-> f = q-> f-> next;
    if(qEmp(q)) q-> r = NULL;
}

pair qF(qu* q){
    pair p; p.fi = p.se = -1;
    if(qEmp(q)) return p;
    p.fi = q-> f-> fi;
    p.se = q-> f-> se;
    return p;
}

//////////////////////////////////////////////////////////

int n, m, r, c;
int g[100][100];
int d[100][100];
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

bool valid(int x, int y){
    if(x >= 0 && x < n && y >= 0 && y < m) return true;
    return false;
}

void bfs(){
    qu* q = cq();
    qPush(q, r, c);
    d[r][c] = 0;

    while(!qEmp(q)){
        pair p = qF(q); qPop(q);
        int x = p.fi;
        int y = p.se;

        REP(i, 0, 4){
            int nx = x + dx[i];
            int ny = y + dy[i];
            if(valid(nx, ny) && g[nx][ny] <= g[x][y] && d[nx][ny] == 1e9){
                qPush(q, nx, ny);
                d[nx][ny] = d[x][y] + 1;
            }
        }
    }
}

int min(int a, int b){
    if(a < b) return a;
    return b;
}

int main(){
    REP(i, 0, 100){
        REP(j, 0, 100) d[i][j] = 1e9;
    }
    scanf("%d %d", &n, &m);
    REP(i, 0, n)
        REP(j, 0, m) scanf("%d", &g[i][j]);
    scanf("%d %d", &r, &c);

    bfs();
    int ans = 1e9;
    REP(j, 0, m){
        ans = min(ans, d[0][j]);
        ans = min(ans, d[n-1][j]);
    }
    REP(i, 0, n){
        ans = min(ans, d[i][0]);
        ans = min(ans, d[i][m-1]);
    }
    if(ans == 1e9) ans = -2;
    printf("%d", ans+1);
    return 0;
}