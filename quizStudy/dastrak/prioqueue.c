#include <stdio.h>
#include <stdlib.h>

typedef struct node node;

struct node{
    node* next;
    int val;
    int prio;
}*front, *rear;

node *createnewnode(int val, int prio){
    node *newnode = malloc(sizeof(node));
    newnode->val = val;
    newnode->next = NULL;
    newnode->prio = prio;
    return newnode;
}

void push(int val, int prio){
    node *newnode = createnewnode(val, prio);
    if (!front)
    {
        front = rear = newnode;
    }
    else if (prio > front->prio)
    {
        newnode->next = front;
        front = newnode;
    }
    
    else{
        node *curr = front;
        while(curr->next && curr->next->prio >= prio){ //Henti di node yang node selanjutnya lebih kecil
            curr = curr->next;
        }
        newnode->next = curr->next;
        curr->next = newnode;
        if(newnode->next == NULL) rear = newnode; //Update rear 
    }
}

void pop(){
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
    push(6, 0); //6
    display();

    push(2, 2); // 2 6
    display();

    push(1, 1); // 2 1 6
    display();

    push(7, 1); // 2 1 7 6 
    display();

    push(5, 2);
    display();

    push(3, 0);
    display();
    push(4, 1);

    // 2 5 1 7 4 6 3
    display();
    pop();
    display();
    pop();
    display();
    pop();
}