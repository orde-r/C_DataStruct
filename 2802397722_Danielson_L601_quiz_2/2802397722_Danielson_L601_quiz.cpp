#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER 100

typedef struct node node;

struct node{
    char id;
    int val;
    node* next;
    node *prev;
};

int getVal(char id[]){
    int val = 0;
    sscanf(id+1, "%d", &val);
    return val;
}

node *createNode(char id, int val){
    node *newnode = (node*)malloc(sizeof(node));
    newnode->next = NULL;
    newnode->prev = NULL;
    newnode->id = id;
    newnode->val = val;

    return newnode;
}

node *insert(node *head, char id, int val){
    node *newnode = createNode(id, val);
    if (!head)
    {
        head = newnode;
        return head;
    }
    else if (head->val > val)
    {
        newnode->next = head;
        head->prev = newnode;
        head = newnode;
        return head;
    }

    node *curr = head;
    while (curr->next && curr->next->val < val) //Stop tepat sebelum lebih besar
    {
        curr = curr->next;
    }
    newnode->next = curr->next;
    newnode->prev = curr;

    if (curr->next) //ditail
    {
        curr->next->prev = newnode;    }
    
    curr->next= newnode;
    
    return head;
}

node *pop(node *head, char id, int val){
    if (!head) return NULL;
    else if (head->val == val && head->id == id)
    {
        node *temp = head;
        head->next->prev = NULL;
        head = head->next;
        free(temp);
        return head;
    }

    node *curr = head;
    while (curr && (curr->val != val || curr->id != id)) //Stop tepat sebelum sama
    {
        curr = curr->next;
    }
    
    node *temp = curr;
    curr->prev->next = curr->next;
    if (curr->next)
    {
        curr->next->prev = curr->prev;
    }
    
    free(temp);
    
    return head;    
}

node *merge(node *result, node *vip, node *reg){
    node *vipCurr = vip, *regCurr = reg;

    if (vipCurr)
    {
        result = vipCurr;
        vipCurr = vipCurr->next;
    }else{ //Jika tidak ada vip
        result = regCurr;
        regCurr = regCurr->next;
    }

    node *finalCurr = result;

    while (vipCurr || regCurr)
    {
        if (regCurr && (finalCurr->id == 'V' || !vipCurr))
        {
            finalCurr->next = regCurr;
            regCurr->prev = finalCurr;

            regCurr = regCurr->next;
        }
        else if (vipCurr && (finalCurr->id == 'R' || !regCurr))
        {
            finalCurr->next = vipCurr;
            vipCurr->prev = finalCurr;

            vipCurr = vipCurr->next;
        }
        finalCurr = finalCurr->next;
    }

    return result;
}

node *repairQueue(node *result){
    node *vipTemp = NULL, *regTemp = NULL, *curr = result, *prev = NULL;

    while (curr)
    {
        if (curr->id == 'V')
        {
            vipTemp = insert(vipTemp, 'V', curr->val);

        }
        else if (curr->id == 'R')
        {
            regTemp = insert(regTemp, 'R', curr->val);
        }
        prev = curr;
        curr = curr->next;
        free(prev);
    }
    result = merge(result, vipTemp, regTemp);
    return result;
}

void display(node *head){
    node *curr = head;
    while(curr){
        printf("%c%d ",curr->id, curr->val);
        curr = curr->next;
    }
    printf("\n");
}

void test1(){
    node* vip = NULL;
    node* reg = NULL;
    node* result = NULL;

    vip = insert(vip, 'V', 1);
    vip = insert(vip, 'V', 2);

    reg = insert(reg, 'R', 1);
    reg = insert(reg, 'R', 2);

    result = merge(result, vip, reg);
    display(result);
}

void test2(){
    node* vip = NULL;
    node* reg = NULL;
    node* result = NULL;

    vip = insert(vip, 'V', 1);
    vip = insert(vip, 'V', 5);
    vip = insert(vip, 'V', 3);

    reg = insert(reg, 'R', 9);
    reg = insert(reg, 'R', 8);
    reg = insert(reg, 'R', 10);
    reg = insert(reg, 'R', 18);

    //pop before merge
    vip = pop(vip, 'V', 5);
    reg = pop(reg, 'R', 10);

    result = merge(result, vip, reg);
    display(result);
}

void test2X(){
    node* vip = NULL;
    node* reg = NULL;
    node* result = NULL;

    vip = insert(vip, 'V', 1);
    vip = insert(vip, 'V', 5);
    vip = insert(vip, 'V', 3);

    reg = insert(reg, 'R', 9);
    reg = insert(reg, 'R', 8);
    reg = insert(reg, 'R', 10);
    reg = insert(reg, 'R', 18);

    result = merge(result, vip, reg);

    //Pop after merge
    result = pop(result, 'V', 5);
    result = pop(result, 'R', 10);
    result = repairQueue(result);
    display(result);
}

void test3(){
    node* vip = NULL;
    node* reg = NULL;
    node* result = NULL;

    vip = insert(vip, 'V', 10);
    vip = insert(vip, 'V', 8);
    vip = insert(vip, 'V', 9);
    vip = insert(vip, 'V', 20);
    vip = insert(vip, 'V', 19);
    vip = insert(vip, 'V', 16);

    reg = insert(reg, 'R', 34);
    reg = insert(reg, 'R', 27);
    reg = insert(reg, 'R', 11);

    //pop before merge
    vip = pop(vip, 'V', 10);
    vip = pop(vip, 'V', 16);
    reg = pop(reg, 'R', 11);

    result = merge(result, vip, reg);
    display(result);
}

void test3X(){
    node* vip = NULL;
    node* reg = NULL;
    node* result = NULL;

    vip = insert(vip, 'V', 10);
    vip = insert(vip, 'V', 8);
    vip = insert(vip, 'V', 9);
    vip = insert(vip, 'V', 20);
    vip = insert(vip, 'V', 19);
    vip = insert(vip, 'V', 16);

    reg = insert(reg, 'R', 34);
    reg = insert(reg, 'R', 27);
    reg = insert(reg, 'R', 11);

    result = merge(result, vip, reg);

    //Pop after merge
    result = pop(result, 'V', 10);
    result = pop(result, 'V', 16);
    result = pop(result, 'R', 11);
    result = repairQueue(result);
    display(result);
}


/*
Scan String
Ambil huruf pertama simpan di char
Ambil angka pakai func getVal
insert atau pop
*/

int main() {

    printf("Case 1 :\n");
    test1();

    printf("\nCase 2 (Pop Before Merge):\n");
    test2();
    printf("Case 2 (Pop After Merge):\n");
    test2X();

    printf("\nCase 3 (Pop Before Merge):\n");
    test3();
    printf("Case 3 (Pop After Merge):\n");
    test3X();

    return 0;
}

//g++ .\2802397722_Danielson_L601_quiz.cpp
//.\a.exe