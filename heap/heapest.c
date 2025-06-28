#include <stdio.h>

int size = 0;

void swap(int *a, int *b){
  int temp = *a;
  *a = *b;
  *b = temp;
}
void heapify(int arr[], int i){
  int smallest = i;
  int left = 2*i+1;
  int right = 2*i+2;

  if(left<size && arr[left]<arr[smallest])smallest = left;
  if(right<size && arr[right]<arr[smallest])smallest = right;
  if(smallest != i){
    swap(&arr[smallest],&arr[i]);
    heapify(arr,smallest);
  }
}

void buildheap(int arr[]){
  for (int i=size/2-1; i>=0; i--){
    heapify(arr,i);
  }
}

void insert(int arr[], int data){
  arr[size] = data;
  size++;
  buildheap(arr);
}

void delete(int arr[]){
  swap(&arr[0],&arr[size-1]);
  size--;
  heapify(arr,0);
}