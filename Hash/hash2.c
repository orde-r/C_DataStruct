#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define size 26

typedef struct Node node;

struct Node
{
    char str[100];
    int val;
    node *next;
}*head = NULL;

unsigned int hash(const char *str){
    if (str[0] >= 'A' && str[0] <= 'Z') return (str[0] - 'A') % size;
    if (str[0] >= 'a' && str[0] <= 'z') return (str[0] - 'a') % size;
}

node *createnewnode(const char *str, int value){
    node *newnode = calloc(1, sizeof(node));

    strcpy(newnode->str,str);
    newnode->val = value;
    newnode->next = NULL;
    return newnode;
}

void insert(node *table[], const char *str, int value){
    int index = hash(str);

    node *newnode = createnewnode(str, value);

    if (table[index] == NULL) table[index] = newnode;
    else{
        newnode->next = table[index];
        table[index] = newnode;
    }    
}

void display(node *table[]){
    for (int i = 0; i < size; i++)
    {
        printf("%c -> ",i+'A');
        node *current = table[i];
        while (current)
        {
            printf("%s: %d -> ",current->str, current->val);
            current = current->next;
        }
        printf("\n");
    }
}

void search(node *table[], const char *str){
    int index = hash(str);

    node *current = table[index];
    while (current)
    {
        if (strcmp(current->str,str) == 0)
        {
            printf("%s: %d\n", current->str, current->val);
            return;
        }
        current = current->next;
    } 
}

void delete(node *table[], const char *str){
    int index = hash(str);

    node *current = table[index];
    node *prev = NULL;

    while (current)
    {
        if (strcmp(current->str,str) == 0)
        {
            if (prev) prev->next = current->next;
            else table[index] = current->next;
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    } 
}

void initialTable(node *table[]){
    for (int i = 0; i < size; i++)
    {
        table[i] = NULL;
    }
}

int main(){
    node *table[size];
    initialTable(table);

    insert(table, "jeremy", 0);
    insert(table, "jeremy2", 69);

    display(table);

    search(table, "jeremy2");
    delete(table, "jeremy");
    display(table);

    return 0;
}