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

bool check_win(char board[][5], int n, int m, char player){
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (board[i][j] != player) continue;
            // Horizontal
            if (j + 3 < m &&
                board[i][j+1] == player &&
                board[i][j+2] == player &&
                board[i][j+3] == player)
                return true;
            // Vertical
            if (i + 3 < n &&
                board[i+1][j] == player &&
                board[i+2][j] == player &&
                board[i+3][j] == player)
                return true;
            // Diagonal down-right
            if (i + 3 < n && j + 3 < m &&
                board[i+1][j+1] == player &&
                board[i+2][j+2] == player &&
                board[i+3][j+3] == player)
                return true;
            // Diagonal up-right
            if (i - 3 >= 0 && j + 3 < m &&
                board[i-1][j+1] == player &&
                board[i-2][j+2] == player &&
                board[i-3][j+3] == player)
                return true;
        }
    }
    return false;
}

bool check_full(int* used, int m){
    for(int i = 0; i < m; i++){
        if(used[i] < 5) return false;
    }
    return true;
}

int computer_move(){
    
}

void connect4(char* board[][5], int* used, int n, int m, char first, char second){
    char player[2] = {first, second};
    int turn = 0;
    while(1){
        if(check_win(board, n, m, player[0])){ 
            printf("Computer Wins");
            break;
        }
        if(check_full(used, m)){
            printf("Draw");
            break;
        }
        if(turn == 0){
            // Computer's Move
            int r = computer_move();
            board[r][used[r]] = player[0];
            used[r]++;
        }
        else{
            // Player's Move 
            char temp;
            int r;
            scanf("%c %d", &temp, &r);
            board[r][used[r]] = player[1];
            used[r]++;
        }
    }

}
int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    char board[n][m];
    int used[5] = {0, 0, 0, 0, 0};
    memset(board, '.', sizeof(board));
    char first, second = 'Y';
    scanf("%c ", &first);
    if(first == 'Y') second = 'R';
    connect4(board, used, n, m, first, second);
}