#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 128

typedef struct node node;

struct node{
    char id[BUF_SIZE];
    int val;
    node *next, *prev;
};

int getVal(char id[]){
    int val;
    sscanf(id+1,"%d",&val);
    return val;
}

node *createNode(char id[], int val){
    node *newnode = (node*)malloc(sizeof(node));

    strcpy(newnode->id, id);
    newnode->val =val;
    newnode->next = NULL;
    newnode->prev = NULL;

    return newnode;
}

node *insert(node *head, node *tail, char id[]){
    int val = getVal(id);
    node *newnode = createNode(id, val);

    if (!head) 
    {
        head = tail = newnode;
    }
    else if (head->val > val)
    {
        head->prev = newnode;
        newnode->next = head;
        head = newnode;

    }
    else if (tail->val < val)
    {
        tail->next = newnode;
        newnode->prev = tail;
        tail = newnode;
    }
    else{
        node *curr = head;
        while (curr && curr->val < val)
        {
            curr = curr->next;
        }
        newnode->next = curr;
        newnode->prev = curr->prev;
    
        curr->prev->next = newnode;
        curr->prev = newnode;
    }    
    return head;
}

void display(node *vipHead, node *regHead){
    node *vipCurr = vipHead, *regCurr = regHead;
    while (vipCurr || regCurr)
    {
        if (vipCurr)
        {
            printf("%s ", vipCurr->id);
        }
        if (regCurr)
        {
            printf("%s ", regCurr->id);
        }
        vipCurr = vipCurr->next;
        regCurr = regCurr->next;
    }
    
}

int main(){
    node *vipHead, *vipTail;
    node *regHead , *regTail;

    int n, m; //vip, reg
    scanf("%d %d",&n,&m);

    char x[BUF_SIZE];
    for (int i = 0; i < n; i++)
    {
        scanf("%s", x);
        vipHead = insert(vipHead, vipTail, x);
    }
    for (int i = 0; i < m; i++)
    {
        scanf("%s", x);
        regHead = insert(regHead, regTail, x);
    }

    return 0;
}

