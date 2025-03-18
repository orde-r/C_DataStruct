#include <stdio.h>
#include <stdlib.h>

typedef struct node node;

struct node{
    node* next;
    int val;
}*head;

node *createnewnode(int val){
    node *newnode = malloc(sizeof(node));
    newnode->val = val;
    newnode->next = NULL;
    return newnode;
}

void push(int val){
    node *newnode = createnewnode(val);
    
    if (!head)
    {
        head = newnode;
    }
    else{
        newnode->next = head;
        head = newnode;
    }
}

void pop(){
    if (!head) return;
    else{
        node* temp = head;
        head = head->next;
        free(temp);
    }   
}

void display(){
    node *curr = head;
    printf("NULL");
    while (curr)
    {
        printf(" <- %d",curr->val);
        curr = curr->next;
    }
    printf("\n");
}

int main(){
    push(6);
    push(1);
    push(7);
    push(3);
    push(2);
    push(5);
    push(4);
    display();
    pop();
    display();
    pop();
    display();
    pop();
}