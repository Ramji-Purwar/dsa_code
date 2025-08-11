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

size_t movements[8][2] = {
    {2, 1}, {1, 2}, {-1, 2}, {-2, 1},
    {-2, -1}, {-1, -2}, {1, -2}, {2, -1}
};

bool validMove(size_t cord[2], size_t n, size_t m){
    size_t x = cord[0];
    size_t y = cord[1];
    return ((x < n && y < m) && (x >= 0 && y >= 0));
}

bool found = false;

void knightPath(size_t r, size_t c, size_t n, size_t m, size_t board[n][m], size_t path[n*m][2], int k){
    if(found) return;
    if(k == n*m){
        for(size_t i = 0; i < n*m; i++){
            printf("%zu %zu\n", path[i][0], path[i][1]);
        }
        found = true;
        return;
    }
    size_t moves[8][2];
    for (size_t i = 0; i < 8; i++) {
        moves[i][0] = movements[i][0] + r;
        moves[i][1] = movements[i][1] + c;
    }
    for(size_t i = 0; i < 8; i++){
        if(validMove(moves[i], n, m)){
            size_t x = moves[i][0];
            size_t y = moves[i][1];
            if(board[x][y] == 0){
                board[x][y] = 1;
                path[k][0] = x;
                path[k][1] = y;
                knightPath(x, y, n, m, board, path, k + 1);
                board[x][y] = 0;
                path[k][0] = 0;
                path[k][1] = 0;
            }
        }
    }
}

int main(){
    size_t n, m;
    scanf("%zu %zu", &n, &m);
    size_t board[n][m];
    size_t path[n*m][2];
    memset(path, 0, sizeof(path));
    memset(board, 0, sizeof(board));
    board[0][0] = 1;
    path[0][0] = 0;
    path[0][1] = 0;
    knightPath(0, 0, n, m, board, path, 1);
    if(!found) printf("No solution found.\n");
    return 0;
}
