#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <limits.h>
#include <float.h>
#include <math.h>
#include <ctype.h>

struct node{
    size_t n;
    size_t *queens;
    size_t k;
    int last;
};

void root(size_t n, struct node *p){
    p -> n = n;
    p -> queens = malloc(n * sizeof(size_t));
    assert(p -> queens);
    p -> k = 0;
    p -> last = -1;
}

bool leaf(struct node *p){
    return p -> k == p -> n;
}

bool ok(struct node *p){
    for(size_t i = 0; i < p -> k; i++){
        for(size_t j = i + 1; j < p -> k; j++){
            size_t d = abs(p -> queens[i] - (int)p -> queens[j]);
            if(d == j - i)
                return false;
        }
    }
    return true;
}


bool up(struct node *p){
    if(p -> k == 0)
        return false;
    p -> last = p -> queens[p -> k - 1];
    --(p -> k);
    return true;
}

bool down(struct node *p){
    bool *used = malloc(p -> n * sizeof(bool));
    assert(used);

    for(size_t i = 0; i < p -> n; i++)
        used[i] = false;
    
    for(size_t i = 0; i < p -> k; i++)
        used[p -> queens[i]] = true;

    for(size_t i = p-> last + 1; i < p -> n; i++){
        if(!used[i]){
            p -> queens[p -> k] = i;
            p -> last = -1;
            ++(p -> k);
            free(used);
            return true;
        }
    }
    free(used);
    return false;
}

size_t nqueens(size_t n){
    struct node p;
    root(n, &p);
    size_t ct = 0;
    while(true){
        if(leaf(&p)){
            if(ok(&p))
                ct++;
            if(!up(&p))
                break;
        }
        else{
            if(!ok(&p)){
                if(!up(&p))
                    break;
            }
            else{
                if(!down(&p)){
                    if(!up(&p))
                        break;
                }
            }
        }
    }
    return ct;
}   

int main(){
    size_t n = 4;
    int ans = nqueens(n);
    printf("Number of solutions for %zu-queens problem: %d\n", n, ans);
    return 0;
}