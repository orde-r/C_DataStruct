#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 9

typedef struct node node;

struct node
{
    char* str;
    int val;
    node* next;
};

node* hashtable[SIZE];

node *createnode(const char *str, int val){
    node *newnode = malloc(sizeof(node));
    newnode->val = val;
    newnode->str = strdup(str);
    newnode->next = NULL;
}

unsigned int hash(const char* str){
    unsigned int key = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        key += str[i];
    }
    return key % SIZE;
}

void insert(const char* str, int val){
    node *newnode = createnode(str, val);
    int key = hash(str);
    if (!hashtable[key])
    {
        hashtable[key] = newnode;
    }
    else
    {
        newnode->next = hashtable[key];
        hashtable[key] = newnode;
    }
}

void removeNode(const char*str){
    int key = hash(str);
    if (!hashtable[key]) return;
    else
    {
        node *curr = hashtable[key], *prev = NULL;
        while (curr && strcmp(curr->str, str) != 0)
        {
            prev = curr;
            curr = curr->next;
        }
        if (curr == hashtable[key])
        {
            hashtable[key] = hashtable[key]->next;
        }
        else
        {
            prev->next = curr->next;
        }
        free(curr);
    }
}

void display(){
    for (int i = 0; i < SIZE; i++)
    {
        node *curr = hashtable[i];
        printf("Index : %d: ",i);
        while (curr)
        {
            printf("(%s, %d) -> ", curr->str, curr->val);
            curr = curr->next;
        }
        printf("NULL\n");
    }
    
}

int main(){
    insert("Andy",0);
    insert("Bndy",11);
    insert("Candy",21);
    insert("Dandy",31);
    insert("Endy",41);
    insert("Fandy",51);
    insert("JeremyNigga",69);

    display();
    printf("\n\n");
    removeNode("JeremyNigga");
    display();
}