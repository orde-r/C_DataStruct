#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 128

typedef struct node node;

int id = 1;

struct node{
    int deadline;
    char task[BUF_SIZE];
    int id;
    node *next, *prev;
}*head, *tail;

node *createNode(int deadline, char task[]){
    node *newnode = (node*)malloc(sizeof(node));

    newnode->deadline = deadline;
    strcpy(newnode->task, task);
    newnode->id = id++;
    newnode->next = NULL;
    newnode->prev = NULL;
    
    return newnode;
}

void insert(int deadline, char task[]){
    node *newnode = createNode(deadline, task);

    if (!head) 
    {
        head = tail = newnode;
        return;
    }
    else if (head->deadline > deadline)
    {
        head->prev = newnode;
        newnode->next = head;
        head = newnode;
        return;
    }
    else if (tail->deadline < deadline)
    {
        tail->next = newnode;
        newnode->prev = tail;
        tail = newnode;
        return;
    }
    else{
        node *curr = head;
        while (curr && curr->deadline < deadline)
        {
            curr = curr->next;
        }
        newnode->next = curr;
        newnode->prev = curr->prev;
    
        curr->prev->next = newnode;
        curr->prev = newnode;
    }    
}

void dequeue(){
    if (!head) return;

    node *temp = head;
    head->next->prev = NULL;
    head = head->next;
    free(temp);
}

void searchDel(int id){
    if (!head) return;
    else if (head->id == id) 
    {
        node *temp = head;
        head->next->prev = NULL;
        head = head->next;
        free(temp);
    }
    else if (tail->id == id) 
    {
        node *temp = tail;
        tail->prev->next = NULL;
        tail = tail->prev;
        free(temp);
    }
    else{
        node *curr = head;
        while (curr && curr->id != id)
        {
            curr = curr->next;
        }
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
    }
}

void display(){
    node *curr = head;
    while (curr)
    {
        printf("%d: %s %d\n", curr->id, curr->task, curr->deadline);
        curr = curr->next;
    }
    
}

void test(){
    insert(5,"asd1");
    insert(10,"asd2");
    insert(3,"asd3");
    insert(8,"asd4");
    insert(2,"asd5");
    display();

    printf("\n\n");
    dequeue();
    display();

    printf("\n\n");
    searchDel(4);
    display();

    printf("\n\n");
    searchDel(1);
    display();
}

int main(){
    test();
    return 0;
}