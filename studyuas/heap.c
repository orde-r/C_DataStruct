#include <stdio.h>
#include <string.h>

// int largest = i; //root
// int leftChild = 2 * i + 1;
// int rightChild = 2 * i + 2;
// int parent = (curr - 1) / 2;

#define MAX 100
typedef struct heap heap;
struct heap
{
    char str[64];
    int val;
};

heap data[MAX];
int size = 0;

void swap (int a, int b){
    heap temp = data[b];
    data[b] = data[a];
    data[a] = temp;
}

void heapifyup(int i){
    if(!i) return;
    int parent = (i - 1) / 2;
    if (data[parent].val < data[i].val)
    {
        swap(parent, i);
        heapifyup(parent);
    }
    
}

void insert(char str[], int value){
    data[size].val = value;
    strcpy(data[size].str, str);
    size++;
    heapifyup(size-1);
}

void heapifydown(int i){
    int left = 2*i+1;
    int right = 2*i+2;
    int max = i;
    if(left < size && data[left].val > data[max].val) max = left;
    if(right < size && data[right].val > data[max].val) max = right;

    if(max!=i){
        swap(max, i);
        heapifydown(max);
    }
}

void deleteMax(){
    if(!size) return;
    data[0] = data[size-1];
    size--;
    heapifydown(0);
}

void display(){
    for (int i = 0; i < size; i++) {
        printf("%s %d\n", data[i].str, data[i].val);
    }
    printf("\n");
}

int main() {
    insert("A", 30);
    insert("B", 20);
    insert("C", 50);
    insert("D", 40);

    // display();

    deleteMax();
    // display();
    
    deleteMax();
    display(); 

    return 0;
}

