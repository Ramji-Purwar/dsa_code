#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>
#include <limits.h>
#include <ctype.h>
#include <string.h> 
#include <math.h>
#include <time.h>
#include <float.h>

bool solved(size_t grid[9][9]){
    for(size_t r = 0; r < 9; r++){
        for(size_t c = 0; c < 9; c++){
            if(grid[r][c] == 0) return false;
        }
    }
    return true;
}

bool isValid(size_t r, size_t c, size_t x, size_t grid[9][9]){
    for(size_t i = 0; i < 9; i++)
        if(grid[r][i] == x) return false;

    for(size_t i = 0; i < 9; i++)
        if(grid[i][c] == x) return false;

    size_t R = r/3, C = c/3;
    for(size_t i = R * 3; i < R * 3 + 3; i++){
        for(size_t j = C * 3; j < C * 3 + 3; j++)
            if(grid[i][j] == x) return false;
    }

    return true;
}

void solveSuduko(size_t grid[9][9]){
    if(solved(grid))
        return;
    for(size_t r = 0; r < 9; r++){
        for(size_t c = 0; c < 9; c++){
            if(grid[r][c]) continue;
            for(int x = 1; x <= 9; x++){
                if(isValid(r, c, x, grid)){
                    grid[r][c] = x;
                    solveSuduko(grid);
                    if(solved(grid)) return;
                    grid[r][c] = 0;
                }
            }
            return;
        }
    }
}

int main(){
    size_t grid[9][9];
    for(size_t r = 0; r < 9; r++){
        for(size_t c = 0; c < 9; c++)
            scanf("%zu", &grid[r][c]);
    }

    solveSuduko(grid);

    for(size_t r = 0; r < 9; r++){
        for(size_t c = 0; c < 9; c++)
            printf("%zu ", grid[r][c]);
        printf("\n");
    }
    return 0;
}