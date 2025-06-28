#include <stdio.h>

int size = 0;
int arr[100];

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapifyup(int i){
    if(!i) return;
    int parent = (i-1)/2;
    if(arr[parent] < arr[i]){
        swap(&arr[parent], &arr[i]);
        heapifyup(parent);
    }
}

void heapifydown(int i){
    int max = i, left = i*2+1, right = i*2+2;
    if(left < size && arr[left] > arr[max])max = left;
    if(right < size && arr[right] > arr[max])max = right;
    if(max != i){
        swap(&arr[max], &arr[i]);
        heapifydown(max);
    }
}

void insertHeap(int a){
    arr[size] = a;
    size++;
    heapifyup(size-1);
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