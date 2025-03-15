#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define table_size 10

typedef struct Node
{
    char key[100];
    int val;
    struct Node *next
} node;

node *HashTable[table_size];

// typedef struct hashmap
// {
//     node* node_arr[table_size];
//     /* data */
// } HashMap;

// void insert(HashMap* map, char* key, int value) {

// }

unsigned int hashfunc(const char *key)
{
    unsigned int hash = 0;
    while (*key)
    {
        hash += *key++;
    }
    return hash % table_size;
}

void insert(const char *key, int val)
{
    unsigned int index = hashfunc(key);

    node *newnode = malloc(sizeof(node));
    strcpy(newnode->key, key);
    newnode->val = val;
    newnode->next = NULL;

    if (!HashTable[index])
    {
        HashTable[index] = newnode;
    }
    else
    {
        newnode->next = HashTable[index];
        HashTable[index] = newnode;
    }
}

int searching(const char *key)
{
    unsigned int index = hashfunc(key);
    node *current = HashTable[index];

    while (current)
    {
        if (strcmp(key, current->key) == 0)
        {
            return current->val;
        }

        current = current->next;
    }
    return -1;
}

void delete(const char *key)
{
    unsigned int index = hashfunc(key);
    node *current = HashTable[index];
    node *prev;

    while (current)
    {
        if (strcmp(key, current->key) == 0)
        {
            if (prev)
            {
                prev->next = current->next;
            }
            else
            {
                HashTable[index] = current->next;
            }
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

void display()
{
    for (int i = 0; i < table_size; i++)
    {
        printf("Index %d: ", i);
        node *current = HashTable[i];
        while (current)
        {
            printf("(%s, %d) -> ", current->key, current->val);
            current = current->next;
        }
        printf("NULL\n");
    }
}

int main()
{
    insert("Alice", 69);
    insert("Amogus", 420);
    insert("SKIbidi", 12);
    insert("Charlie", 45);
    insert("Iyan", 6969);
    insert("jeremy", 55);

    printf("HashTable: ");
    display();

    printf("Searching for jeremy, %d\n", searching("jeremy"));
    printf("Searching for Iyan, %d\n", searching("Iyan"));
    printf("Searching for Iyan_Neko, %d\n", searching("nekopara"));

    delete ("Iyan");
    printf("Searching for Iyan, %d\n", searching("Iyan"));

    return 0;
}