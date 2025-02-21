#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node node;

struct Node
{
    char str[100];
    int value;
    node *next;
}*head = NULL, *tail = NULL;

node* createnewnode(int value, char str[]){
    node *newnode = calloc(1, sizeof(node));

    strcpy(newnode->str, str);
    newnode->value = value;
    newnode->next = NULL;

    return newnode;
}

void pushHead(int value, char str[]){
    node *newnode = createnewnode(value, str);
    if (!head) head = tail = newnode;
    else{
        newnode->next = head;
        head = newnode;
    } 
}

void pushTail(int value, char str[]){
    node *newnode = createnewnode(value, str);
    if (!head) head = tail = newnode;
    else{
        tail->next = newnode;
        tail = newnode;
    } 
}

void pushMid(int value, char str[]){
    node *newnode = createnewnode(value, str);

    if (!head) head = tail = newnode;
    else if (head->value > value) pushHead(value,str);
    else if (tail->value < value) pushTail(value,str);
    else {
        node *current = head;
        while (current && current->next)
        {
            if (current->next->value >= value)
            {
                newnode->next = current->next;
                current->next = newnode;
                return;
            }
            current = current->next;
        }
    }
}

void pop(int value){

    node *current = head;
    node *prev = current;
    while (current != NULL && current->value != value)
    {
        prev = current;
        current = current->next;
    }

    if (current==NULL)return;

    if(current == head){
        head = current->next;
    }
    else if(current == tail){
        tail = prev;
    }
    else{
        prev->next = current->next;
    }
    free(current);
    
}


void display(){
    node *current = head;
    while(current){
        printf("%d. %s\n",current->value, current->str);
        current = current->next;
    }
}

int main(){

    pushMid(3, "Zhang");
    pushMid(1, "Jeremy");
    pushMid(2, "Auriel");
    pushMid(4, "is");
    pushMid(6, "N");
    pushMid(5, "G");
    pop(5);
    display();

    return 0;
}