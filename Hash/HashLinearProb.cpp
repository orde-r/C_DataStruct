#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define size 10

typedef struct Node node;

struct Node{
    char name[100];
    int value;
};

node *hashTable[size];
int count = 0;

node *createNode(const char name[], int value){
    node *newnode = (node*)malloc(sizeof(node));
    strcpy(newnode->name, name);
    newnode->value = value;

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
    if (count == size)
    {
        printf("HashTable is Full\n");
        return;
    }
    node *newnode = createNode(name,value);
    int key = hashFunction(name);

    if (!hashTable[key])
    {
        hashTable[key] = newnode;
        count++;
    } else {
        while (hashTable[key])
        {
            key = (key + 1) % size;
        }
        hashTable[key] = newnode;
        count++;
    }    
}

void removeNode(const char name[]){
    int key = hashFunction(name);
    int temp = key;

    do
    {
        if (hashTable[temp] && strcmp(hashTable[temp]->name,name) == 0)
        {
            free(hashTable[temp]);
            hashTable[temp] = NULL;
            count--;
        }
        temp = (temp + 1) % size;
    } while (temp != key);
    
}

void displayTable(){
    for (int i = 0; i < size; i++)
    {
        printf("%d: ", i);
        if (!hashTable[i])
        {
            printf("NULL\n");
        } else {
            printf("%s %d\n", hashTable[i]->name, hashTable[i]->value);
        }
    }
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