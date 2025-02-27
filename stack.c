#include <stdio.h>
#include <stdlib.h>

typedef struct List list;

struct List
{
    int value;
    struct List *next;
}*top;

void displayStack(){
    list *curr = top;
    while(curr){
        printf("%d ",curr->value);
        curr = curr->next;
    }
    printf("\n");
}

void peek(){
    printf("%d\n",top->value);
}

list *createNewNode(int value){
    list *newnode = calloc(1,sizeof(list));

    newnode->value = value;
    newnode->next = NULL;
    return newnode;
}

void pushHead(int value){
    list *newnode = createNewNode(value);
    if (!top) top = newnode;
    else{
        newnode->next = top;
        top = newnode;
    }
}

void popHead(){
    list *temp = top;
    top = top->next;
    free(temp);
    displayStack();
}



int main(){
    pushHead(3);
    pushHead(1);
    pushHead(2);
    pushHead(4);
    pushHead(6);
    pushHead(5);
    pushHead(7);
    displayStack();
    popHead();
    popHead();
    popHead();
    popHead();
    popHead();
    popHead();
    peek();

    return 0;
}