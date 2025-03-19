#include <stdio.h>
#include <stdlib.h>

typedef struct node node;

struct node{
    node* next;
    int val;
}*head, *tail;

node *createnewnode(int val){
    node *newnode = malloc(sizeof(node));
    newnode->val = val;
    newnode->next = NULL;
    return newnode;
}

void pushHead(int val){
    node *newnode = createnewnode(val);
    
    if (!head)
    {
        head = tail = newnode;
    }
    else{
        newnode->next = head;
        head = newnode;
    }
}

void pushTail(int val){
    node *newnode = createnewnode(val);
    
    if (!head)
    {
        head = tail = newnode;
    }
    else{
        tail->next = newnode;
        tail = newnode;
    }
}

void pushMid(int val){
    if (!head || head->val > val){
        pushHead(val);
        return;
    }
    else if (tail->val < val)
    {
        pushTail(val);
        return;
    }
    node *newnode = createnewnode(val); 
    node *curr = head, *prev = NULL;
    while (curr && curr->val < val) //Henti di node yang lbh besar
    {
        prev = curr;
        curr = curr->next;
    }
    prev->next = newnode;
    newnode->next = curr; 
}

void popMid(int val){
    if (!head) return;
    if (head == tail) 
    {
        free(head);
        head = tail = NULL;
        return;
    }
    node *curr = head, *prev = NULL;
    while (curr && curr->val != val)
    {
        prev = curr;
        curr = curr->next;
    }
    if (!curr) return;
    if (curr == head)
    {
        head = head->next;
    }
    else if (curr == tail)
    {
        prev->next = NULL;
        tail = prev;
    }
    else
    {
        prev->next = curr->next;
    }
    free(curr);
}

void display(){
    node *curr = head;
    while (curr)
    {
        printf("%d -> ",curr->val);
        curr = curr->next;
    }
    printf("NULL\n");
}

int main(){
    pushMid(6);
    pushMid(1);
    pushMid(7);
    pushMid(3);
    pushMid(2);
    pushMid(5);
    pushMid(4);
    popMid(1);
    popMid(7);
    popMid(4);
    display();
}