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
    struct Node *next;
};

struct Node* createNode(int x){
    struct Node *newNode = malloc(sizeof(struct Node));
    newNode -> val = x;
    newNode -> next = NULL;
    return newNode;
}

struct Queue{
    struct Node *front;
    struct Node *rear;
};

struct Queue* createQueue(){
    struct Queue *queue = malloc(sizeof(struct Queue));
    queue -> front = queue -> rear = NULL;
    return queue; 
}

void qPush(struct Queue* queue, int val){
    struct Node *newNode = createNode(val);
    if(queue -> rear == NULL){
        queue -> front = queue -> rear = newNode;
        return;
    }
    queue -> rear -> next = newNode;
    queue -> rear = newNode;
}

bool qEmpty(struct Queue* queue){
    if(queue -> front == NULL)
        return true;
    return false;
}

void qPop(struct Queue* queue){
    if(qEmpty(queue))
        return;
    struct Node *temp = queue->front;
    queue -> front = queue -> front -> next;
    if(queue -> front == NULL)
        queue->rear = NULL;
    free(temp);
}

int qFront(struct Queue* queue){
    if(qEmpty(queue))
        return -1;
    return queue -> front -> val;
}

int main(){
    return 0;
}