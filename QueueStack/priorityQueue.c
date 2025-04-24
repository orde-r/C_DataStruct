#include <stdio.h>
#include <stdlib.h>

typedef struct List list;

struct List
{
    int priority;
    int value;
    struct List *next;
}*front, *rear;         //Front = First, Rear = Last

void displayQueue() {
    list *curr = front;
    if (!curr) {
        printf("Queue is empty!\n");
        return;
    }
    while (curr) {
        printf("[%d,%d] -> ", curr->priority, curr->value);
        curr = curr->next;
    }
    printf("NULL\n");
}

list *createNewNode(int priority,int value){
    list *newnode = calloc(1,sizeof(list));
    
    newnode->priority = priority;
    newnode->value = value;
    newnode->next = NULL;
    return newnode;
}

void push(int priority,int value){ //pushTail
    list *newnode = createNewNode(priority, value);
    if (!front) front = rear = newnode;
    else if (priority < front->priority)
    {
        newnode->next = front;
        front = newnode;
    }
    else{
        list *curr = front;
        while(curr->next && priority >= curr->next->priority){
            curr = curr->next;
        }
        newnode->next = curr->next;
        curr->next = newnode;
        if(newnode->next == NULL) rear = newnode;
    }
}

void popHead(){
    if (!front) return;
    
    list *temp = front;
    front = front->next;
    free(temp);
    if (!front) rear = NULL;
    displayQueue();
}



int main(){
    //Lower Priority number means higher priority level
    push(1,3);
    push(2,1);
    push(3,2);
    push(3,4);
    push(1,6);
    push(2,5);
    push(2,7);
    displayQueue();
    popHead();
    // popHead();
    // popHead();
    // popHead();
    // popHead();
    // popHead();

    return 0;
}