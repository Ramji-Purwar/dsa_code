#include <stdio.h>
#include <stdlib.h>

#define MAX 8

int dx[8] = {2, 1, -1, -2, -2, -1, 1, 2};
int dy[8] = {1, 2, 2, 1, -1, -2, -2, -1};

int n, m;
int board[MAX][MAX];

int is_valid(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m && board[x][y] == -1;
}

int count_onward(int x, int y) {
    int cnt = 0;
    for (int i = 0; i < 8; i++) {
        int nx = x + dx[i], ny = y + dy[i];
        if (is_valid(nx, ny)) cnt++;
    }
    return cnt;
}

int knights_tour(int x, int y, int move_num, int sx, int sy) {
    board[x][y] = move_num;
    if (move_num == n * m - 1) {
        for (int i = 0; i < 8; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            if (nx == sx && ny == sy) return 1;
        }
        board[x][y] = -1;
        return 0;
    }

    int next[8], idx[8];
    for (int i = 0; i < 8; i++) {
        int nx = x + dx[i], ny = y + dy[i];
        if (is_valid(nx, ny)) {
            next[i] = count_onward(nx, ny);
            idx[i] = i;
        } else {
            next[i] = 99;
            idx[i] = i;
        }
    }
    for (int i = 0; i < 8; i++)
        for (int j = i + 1; j < 8; j++)
            if (next[j] < next[i]) {
                int t = next[i]; next[i] = next[j]; next[j] = t;
                t = idx[i]; idx[i] = idx[j]; idx[j] = t;
            }

    for (int k = 0; k < 8; k++) {
        int i = idx[k];
        int nx = x + dx[i], ny = y + dy[i];
        if (is_valid(nx, ny)) {
            if (knights_tour(nx, ny, move_num + 1, sx, sy)) return 1;
        }
    }
    board[x][y] = -1;
    return 0;
}

int main() {
    int r, c;
    scanf("%d %d %d %d", &n, &m, &r, &c);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            board[i][j] = -1;

    if (knights_tour(r, c, 0, r, c)) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++)
                printf("%d ", board[i][j] + 1);
            printf("\n");
        }
    } else {
        printf("-1\n");
    }
    return 0;
}