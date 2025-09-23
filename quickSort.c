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

void swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

int lomutoPartition(int* arr, int l, int h){
    int key = arr[h];
    int i = l;
    for(int j = l; j < h; j++){
        if(arr[j] < key){
            swap(&arr[i], &arr[j]);
            i++;
        }
    }
    swap(&arr[i], &arr[h]);
    return i;
}

void quickSort(int* arr, int l, int h){
    if(l < h){
        int pi = lomutoPartition(arr, l, h);
        quickSort(arr, l, pi-1);
        quickSort(arr, pi+1, h);
    }
}

int main(){
    int n = 6;
    int arr[] = { 5 , 4 , 9 , 3 , 2 , 6 };
    quickSort(arr, 0, n-1);
    for(int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}