#include <stdio.h>
#include <string.h>

#define MAX 100

typedef struct {
    char name[50];
    int value; // Heap will sort based on this
} Data;

Data heap[MAX];
int heapSize = 0;

// Swap function
void swap(int a, int b) {
    Data temp = heap[a];
    heap[a] = heap[b];
    heap[b] = temp;
}

// Heapify Up (Insert Fix)
void heapifyUp(int index) {
    if (index == 0) return; // Root node

    int parent = (index - 1) / 2;

    if (heap[parent].value < heap[index].value) {
        swap(parent, index);
        heapifyUp(parent);
    }
}

// Heapify Down (Delete Fix)
void heapifyDown(int index) {
    int left = index * 2 + 1;
    int right = index * 2 + 2;
    int largest = index;

    if (left < heapSize && heap[left].value > heap[largest].value)
        largest = left;
    if (right < heapSize && heap[right].value > heap[largest].value)
        largest = right;

    if (largest != index) {
        swap(largest, index);
        heapifyDown(largest);
    }
}

// Insert function
void insert(char name[], int value) {
    if (heapSize >= MAX) {
        printf("Heap is full!\n");
        return;
    }

    heapSize++;
    strcpy(heap[heapSize - 1].name, name);
    heap[heapSize - 1].value = value;

    heapifyUp(heapSize - 1);
}


// Delete max (root)
void deleteMax() {
    if (heapSize == 0) {
        printf("Heap is empty!\n");
        return;
    }

    printf("Deleted: %s %d\n", heap[0].name, heap[0].value);

    heap[0] = heap[heapSize - 1];
    heapSize--;

    heapifyDown(0);
}

// Print heap
void printHeap() {
    printf("Current Heap:\n");
    for (int i = 0; i < heapSize; i++) {
        printf("%s %d\n", heap[i].name, heap[i].value);
    }
    printf("\n");
}

// Main program
int main() {
    insert("A", 30);
    insert("B", 20);
    insert("C", 50);
    insert("D", 40);

    printHeap();

    deleteMax();
    printHeap();

    deleteMax();
    printHeap();

    return 0;
}