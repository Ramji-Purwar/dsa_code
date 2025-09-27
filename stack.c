#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <ctype.h>
#include <assert.h>
#include <time.h>
#include <math.h>
#include <limits.h>
#include <float.h>

struct Node{
    int val;
    struct Node* next;
};

struct Node* createNode(int val){
    struct Node *newNode = malloc(sizeof(struct Node));
    newNode -> val = val;
    newNode -> next = NULL;
    return newNode;
}

struct Stack{
    struct Node* top;
};

struct Stack* createStack(){
    struct Stack* st = malloc(sizeof(struct Stack));
    st -> top = NULL;
    return st;
}

void sPush(struct Stack* st, int x){
    struct Node* newNode = createNode(x);
    newNode -> next = st -> top;
    st -> top = newNode;
}

bool sEmpty(struct Stack* st){
    return st -> top == NULL;
}

void sPop(struct Stack* st){
    if(sEmpty(st))
        return;
    struct Node* temp = st -> top;
    st -> top = temp -> next;
    free(temp);
}

int sTop(struct Stack* st){
    if(sEmpty(st))
        return -1;
    return st -> top -> val;
}

int main(){
    
    return 0;
}