#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#define int long long
#define REP(i, a, b) for(int i = a; i < b; i++)

typedef struct Node{
    int val;
    struct Node* next;
} node;

node* cnode(int x){
    node* new = malloc(sizeof(node));
    new-> val = x;
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

void qPush(qu* q, int x){
    node* new = cnode(x);
    if(qEmp(q)){
        q-> f = q-> r = new;
        return;
    }
    q-> r-> next = new;
    q-> r = new;
}

void qPop(qu* q){
    if(qEmp(q)) return;
    q-> f = q-> f -> next;
    if(qEmp(q)) q-> r = NULL;
}

int qF(qu* q){
    if(qEmp(q)) return -1;
    return q-> f-> val;
}

int main(){
    
}