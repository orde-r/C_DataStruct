#include <stdio.h>
#include <stdlib.h>

typedef struct List list;

struct List
{
    int value;
    struct List *next;
}*front, *rear;

void displayQueue(){
    list *curr = front;
    while(curr){
        printf("%d ",curr->value);
        curr = curr->next;
    }
    printf("\n");
}

list *createNewNode(int value){
    list *newnode = calloc(1,sizeof(list));

    newnode->value = value;
    newnode->next = NULL;
    return newnode;
}

void push(int value){ //pushTail
    list *newnode = createNewNode(value);
    if (!front) front = rear = newnode;
    else{
        rear->next = newnode;
        rear = newnode;
    }
}

void popHead(){
    list *temp = front;
    front = front->next;
    free(temp);
    displayQueue();
}



int main(){
    push(3);
    push(1);
    push(2);
    push(4);
    push(6);
    push(5);
    push(7);
    displayQueue();
    popHead();
    popHead();
    popHead();
    popHead();
    popHead();
    popHead();

    return 0;
}