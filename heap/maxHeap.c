#include <stdio.h>

int size = 0;

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(int arr[],int i){
    //Indexeesss !!!
    int largest = i; //root
    int leftChild = 2 * i + 1;
    int rightChild = 2 * i + 2;

    if (leftChild < size && arr[leftChild] > arr[largest])
    {
        largest = leftChild;
    }
    if (rightChild < size && arr[rightChild] > arr[largest])
    {
        largest = rightChild;
    }

    if (largest != i)
    {
        swap(&arr[i], &arr[largest]);
        heapify(arr, largest);
    }
}

void insert(int n, int arr[]){
    arr[size] = n;
    size++;

    int curr = size - 1;

    while (curr)
    {
        int parent = (curr - 1) / 2;
        if (arr[curr] > arr[parent])
        {
            swap(&arr[curr], &arr[parent]);
            curr = parent;
        }
        else{
            break;
        }
    }
}

void deleteMax(int arr[]){
    int root = 0;
    swap(&arr[root], &arr[size-1]);
    size--;
    
    heapify(arr,root);
}

void printArray(int arr[]){
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    
}

int main() {
    int arr[10];
    
    insert(3, arr);
    insert(4, arr);
    insert(9, arr);
    insert(5, arr);
    insert(2, arr);
    insert(10, arr);
    insert(12, arr);
    insert(11, arr);
    printArray(arr);
    printf("\n");
    deleteMax(arr);
    printArray(arr);

    return 0;
}