#include <stdio.h>
#include <stdlib.h>

typedef struct node node;

struct node{
    node* next;
    node* prev;
    int val;
}*head, *tail;

node *createnewnode(int val){
    node *newnode = malloc(sizeof(node));
    newnode->val = val;
    newnode->next = NULL;
    newnode->prev = NULL;
    return newnode;
}

void pushHead(int val){
    node *newnode = createnewnode(val);
    
    if (!head)
    {
        head = tail = newnode;
    }
    else{
        head->prev = newnode;
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
        newnode->prev = tail;
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
    node *curr = head;
    while (curr && curr->val < val) //Henti di node yang lebih besar
    {
        curr = curr->next;
    }
    newnode->prev = curr->prev;
    newnode->next = curr; 
    
    curr->prev->next = newnode;
    curr->prev = newnode;

}

void popMid(int val){
    if (!head) return;
    if (head == tail) 
    {
        free(head);
        head = tail = NULL;
        return;
    }
    node *curr = head;
    while (curr && curr->val != val)
    {
        curr = curr->next;
    }
    if (!curr) return;
    if (curr == head)
    {
        head = head->next;
        head->prev = NULL;
    }
    else if (curr == tail)
    {
        tail = tail->prev;
        tail->next = NULL;
    }
    else
    {
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
    }
    free(curr);
}

void displayNext(){
    node *curr = head;
    while (curr)
    {
        printf("%d -> ",curr->val);
        curr = curr->next;
    }
    printf("NULL\n");
}
void displayPrev(){
    node *curr = tail;
    while (curr)
    {
        printf("%d -> ",curr->val);
        curr = curr->prev;
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
    displayNext();
    displayPrev();
}