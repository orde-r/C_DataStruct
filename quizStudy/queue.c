#include <stdio.h>
#include <stdlib.h>

typedef struct node node;

struct node{
    node* next;
    int val;
}*front, *rear;

node *createnewnode(int val){
    node *newnode = malloc(sizeof(node));
    newnode->val = val;
    newnode->next = NULL;
    return newnode;
}

void push(int val){ //Pushtail
    node *newnode = createnewnode(val);
    if (!front)
    {
        front = rear = newnode;
    }
    else{
        rear->next = newnode;
        rear = newnode;
    }
}

void pop(){ //Pophead
    if (!front) return;
    else{
        node *temp = front;
        front = front->next;
        free(temp);
    }
    
}

void display(){
    node *curr = front;
    while (curr)
    {
        printf("%d -> ",curr->val);
        curr = curr->next;
    }
    printf("NULL\n");
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