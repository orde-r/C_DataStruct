#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER 256

typedef struct node node;

struct node{
    char genre[BUFFER], code[BUFFER], name[BUFFER], deleteBy[BUFFER];
    node *next;
}*head, *tail;

node *createNewNode(char genre[], char code[], char name[], int index){
    node *newnode = (node*)malloc(sizeof(node));
    strcpy(newnode->genre, genre);
    strcpy(newnode->code, code);
    strcpy(newnode->name, name);
    newnode->next = NULL;

    switch(index){
        case 1:
            strcpy(newnode->deleteBy, genre);
            break;
        case 2:
            strcpy(newnode->deleteBy, code);
            break;
        case 3:
            strcpy(newnode->deleteBy, name);
            break;
    }
    
    return newnode;
}

void insertNode(char genre[], char code[], char name[], int index){
    node *newnode = createNewNode(genre, code , name, index);
    
    if(!head) head = tail = newnode;
    else if (strcmp(newnode->name, head->name) < 0)
    {
        newnode->next  = head;
        head = newnode;
    }
    else if (strcmp(newnode->name, tail->name) > 0)
    {
        tail->next  = newnode;
        tail = newnode;
    }
    else{
        node *curr= head, *prev = NULL;
        while (curr && strcmp(newnode->name, curr->name) > 0)
        {
            prev = curr;
            curr = curr->next;
        }
        prev->next = newnode;
        newnode->next = curr;
    }
    return;
}

void deleteNode(char toDelete[]){
    if (!head) return;   
    node *curr = head, *prev = NULL;
    while (curr)
    {
        if (strcmp(curr->deleteBy, toDelete) == 0)
        {
            if (!prev)
            {
                head = curr->next;
                free(curr);
                curr = head;
                continue;
            }
            else
            {
                prev->next = curr->next;
                free(curr);
                curr = prev->next;
                continue;
            }
        }
        prev = curr;
        curr = curr->next;
    }
    tail = prev;
}

void printList(){
    node *curr= head;
        while (curr)
        {
            printf("%s %s %s\n", curr->genre, curr->code, curr->name);
            curr = curr->next;
        }
}

int initIndex(char deleteBy[]){
    if (strcmp(deleteBy, "Genre") == 0) return 1;
    else if (strcmp(deleteBy, "Code") == 0) return 2;
    else if (strcmp(deleteBy, "Name") == 0) return 3;
}

int main(){
    int n;
    scanf("%d", &n); getchar();
    // printf("%d", n);

    char deleteBy[BUFFER];
    scanf("%s", deleteBy); getchar();
    int index = initIndex(deleteBy);
    // printf("%s", deleteBy);

    char genre[BUFFER], code[BUFFER], name[BUFFER];
    for (int i = 0; i < n; i++)
    {
        scanf("%s %s %[^\n]", genre, code, name); getchar();
        insertNode(genre, code, name, index);
    }
    printf("\n\n");
    printList();
    printf("\n\n");

    char toDelete[BUFFER];
    scanf("%[^\n]", toDelete); getchar();

    deleteNode(toDelete);

    printList();

     return 0;
}

/*
3
Name
Fiction B001 The Lord of the Rings
Fiction B002 Harry Potter and the Philosopher's Stone
NonFiction B003 Sapiens: A Brief History of Humankind
The Lord of the Rings

5
Genre
NonFiction B001 A Brief History of Time
Fiction B002 The Catcher in the Rye
Fiction B003 The Great Gatsby
NonFiction B004 Sapiens: A Brief History of Humankind
Fiction B005 The Hobbit
NonFiction
*/