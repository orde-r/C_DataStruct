#include <stdio.h>

#define MAX 100
int size = 0;
int arr[MAX];

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapifyup(int i){
    if(!i) return;
    int parent = (i - 1) / 2;
    if (arr[i] > arr[parent])
    {
        swap(&arr[i], &arr[parent]);
        heapifyup(parent);
    }
}

void insertHeap(int val){
    arr[size] = val;
    size++;
    heapifyup(size-1);
}

void heapifydown(int i){
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int max  = i;
    if(left < size && arr[max] < arr[left]) max = left;
    if(right < size && arr[max] < arr[right]) max = right;
    if(max != i){
        swap(&arr[max], &arr[i]);
        heapifydown(max);
    }
}

void deleteMax(){
    swap(&arr[0], &arr[size-1]);
    size--;
    heapifydown(0);
}

void display(){
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}


int main(){
    insertHeap(30);
    insertHeap(50);
    insertHeap(40);
    insertHeap(90);
    insertHeap(20);
    insertHeap(10);
    display();

    deleteMax();
    deleteMax();
    display();

    return 0;
}