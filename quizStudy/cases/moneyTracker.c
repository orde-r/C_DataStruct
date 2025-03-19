#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER 256

typedef struct node node;

int balance = 0, food = 0, house = 0, entertainment = 0, other = 0;

struct node
{
    char categories[BUFFER], detail[BUFFER];
    int amount;
    node *next, *prev;
}*head,*tail;

node *createNode(char categories[], char detail[], int amount){
    node *newnode = (node*)malloc(sizeof(node));

    strcpy(newnode->categories, categories);
    strcpy(newnode->detail, detail);
    newnode->amount = amount;
    newnode->next = NULL;
    newnode->prev = NULL;

    return newnode;
}

void insertNode(char categories[], char detail[], int amount){
    node *newnode = createNode(categories, detail, amount);
    if (!head) head = tail = newnode;
    else 
    {
        tail->next = newnode;
        newnode->prev = tail;
        tail = newnode;
    }
}

void deleteNode(char detail[]){
    if (!head) return;
    else{
        node *curr = head;
        while (curr)
        {
            if (strcmp(curr->detail, detail) == 0)
            {
                balance += curr->amount;
                if (strcmp("food",curr->categories) == 0) food -= curr->amount;
                else if (strcmp("house",curr->categories) == 0) house -= curr->amount;
                else if (strcmp("entertainment",curr->categories) == 0) entertainment -= curr->amount;
                else if (strcmp("other",curr->categories) == 0) other -= curr->amount;

                if (!curr->prev) //pop head
                {
                    curr->next->prev = NULL;
                    head = curr->next;
                    free(curr);
                    curr = head;
                    continue;
                }
                else if (!curr->next) //pop tail
                {
                    curr->prev->next = NULL;
                    tail = curr->prev;
                    free(curr);
                    curr = tail;
                    continue;
                }
                else
                {
                    curr->prev->next = curr->next;
                    curr->next->prev = curr->prev;
                    node *temp = curr->prev->next;
                    free(curr);
                    curr = temp;
                    continue;
                }
            }
            curr = curr->next;
        }
    }
}

void display(){

    printf("Account Balance: %d\n",balance);
    printf("food: %d\n",food);
    printf("house: %d\n",house);
    printf("entertainment: %d\n",entertainment);
    printf("other: %d\n",other);

    node *curr = head;
    while (curr)
    {
        printf("%s (%s): %d\n", curr->detail, curr->categories, curr->amount);
        curr = curr->next;
    }
}

int main(){

    scanf("%d",&balance);

    int n;
    scanf("%d",&n);

    char categories[BUFFER], detail[BUFFER];
    int amount;
    
    for (int i = 0; i < n; i++)
    {
        scanf("%s %s %d", categories,detail,&amount);
        balance -= amount;
        
        if (strcmp("food",categories) == 0) food += amount;
        else if (strcmp("house",categories) == 0) house += amount;
        else if (strcmp("entertainment",categories) == 0) entertainment += amount;
        else if (strcmp("other",categories) == 0) other += amount;

        insertNode(categories,detail,amount);
    }
    
    char toDelete[BUFFER]; //Selalu detail
    scanf("%s",toDelete);
    deleteNode(toDelete);
    display();

    return 0;
}

/*
3500000
5
house rent 1800000
food meal 450000
other skincare 250000
entertainment ott 450000
food grocery 150000
ott
*/