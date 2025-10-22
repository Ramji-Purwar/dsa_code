#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
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

typedef struct Stack{
    node* top;
} stack;

stack* cstack(){
    stack* st = malloc(sizeof(stack));
    st-> top = NULL;
    return st;
}

bool sEmp(stack* st){
    return st-> top == NULL;
}

void sPush(stack* st, int x){
    node* new = cnode(x);
    new-> next = st-> top;
    st-> top = new;
}

void sPop(stack* st){
    if(sEmp(st)) return;
    st-> top = st-> top-> next;
}

int sTop(stack* st){
    if(sEmp(st)) return -1;
    return st-> top-> val;
}

int main(){
    
    return 0;
}