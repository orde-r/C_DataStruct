#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define size 10

typedef struct Node node;

struct Node{
    char name[100];
    int value;
    node *next;
};

node *hashTable[size]; //The first node of the array is the head
int count = 0;

node *createNode(const char name[], int value){
    node *newnode = (node*)malloc(sizeof(node));
    strcpy(newnode->name, name);
    newnode->value = value;
    newnode->next = NULL;

    return newnode;
}

int hashFunction(const char name[]){
    int key = 0;
    for (int i = 0; i < strlen(name); i++)
    {
        key += name[i];
    }
    return key % size;
}

void insertNode(const char name[], int value){
    node *newnode = createNode(name, value);
    int key = hashFunction(name);

    if (!hashTable[key]) hashTable[key] = newnode;
    else{
        newnode->next = hashTable[key];
        hashTable[key] = newnode;
    }
}

void removeNode(const char name[]){
    int key = hashFunction(name);
    node *curr = hashTable[key], *prev;

    while (curr && strcmp(curr->name, name) != 0)
    {
        prev = curr;
        curr = curr->next;
    }
    if (prev)
    {
        prev->next = curr->next;
    }
    else
    {
        hashTable[key] = curr->next;
    }
    free(curr);
    return;
}

void displayTable(){
    for (int i = 0; i < size; i++)
    {
        printf("Index %d: ", i);
        node *current = hashTable[i];
        while (current)
        {
            printf("(%s, %d) -> ", current->name, current->value);
            current = current->next;
        }
        printf("NULL\n");
    }
}

int searching(const char name[]){
    int key = hashFunction(name);
    node *curr = hashTable[key];

    while (curr)
    {
        if (strcmp(curr->name, name) == 0)
        {
            // printf("%s : %d\n", curr->name, curr->value);
            return curr->value;
        }
        curr = curr->next;
    }
    return -1;
}

int main(){
    insertNode("Andy",0);
    insertNode("Bndy",11);
    insertNode("Candy",21);
    insertNode("Dandy",31);
    insertNode("Endy",41);
    insertNode("Fandy",51);
    insertNode("JeremyNigga",69);

    displayTable();
    printf("\n\n");
    removeNode("JeremyNigga");
    displayTable();
    
}