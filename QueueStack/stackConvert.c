#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct List list;

struct List
{
    char value;
    struct List *next;
};

void displayStack(list *top){
    list *curr = top;
    while(curr){
        printf("%c ",curr->value);
        curr = curr->next;
    }
    printf("\n");
}

void peek(list *top){
    if (!top)
    {
        printf("Stack is empty!");
        return;
    }
    
    printf("%c\n",top->value);
}

list *createNewNode(char value){
    list *newnode = calloc(1,sizeof(list));

    newnode->value = value;
    newnode->next = NULL;
    return newnode;
}

list *pushHead(list *top, char value){
    list *newnode = createNewNode(value);
    if (!top) top = newnode;
    else{
        newnode->next = top;
        top = newnode;
    }
    return top;
}

list *popHead(list *top){
    if(!top) return top;
    list *temp = top;
    top = top->next;
    free(temp);
    //displayStack();
    return top;
}

int precedence(char op) {
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

void prefix(const char str[]){
    list *top = NULL;

    int size = strlen(str);
    char preStr[size];
    int index = size-1;
    
    for (int i = size-1; i >= 0; i--)
    {
        if (str[i] >= '0' && str[i] <= '9')
        {
            preStr[index] = str[i];
            index--;
        }else if (str[i] == ')')
        {
            top = pushHead(top, str[i]);
        }else if (str[i] == '(')
        {
            while (top->value != ')')
            {
                preStr[index] = top->value;
                index--;
                top = popHead(top);
            }
            top = popHead(top);
        }else if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/')
        {
            while (top && precedence(top->value) >= precedence(str[i]))
            {
                preStr[index] = top->value;
                index--;
                top = popHead(top);
            }
            top = pushHead(top, str[i]);
        }     
    }
    
    while (top)
    {
        preStr[index] = top->value;
        index--;
        top = popHead(top);
    }    

    //Move to beginnign
    for (int i = 0; i <= size - index - 2; i++) {
        preStr[i] = preStr[index + 1 + i];
    }
    preStr[size - index - 1] = '\0';

    preStr[size] = '\0';
    printf("Prefix: %s\n",preStr);
}


void postfix(const char str[]){
    list *top = NULL;

    int size = strlen(str);
    char postStr[size];
    int index = 0;

    for (int i = 0; i < size; i++)
    {
        if (str[i] >= '0' && str[i] <= '9')
        {
            postStr[index] = str[i];
            index++;
        }else if (str[i] == '(')
        {
            top = pushHead(top, str[i]);
        }else if (str[i] == ')')
        {
            while (top->value != '(')
            {
                postStr[index] = top->value;
                index++;
                top = popHead(top);
            }
            top = popHead(top);
        }else if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/')
        {
            while (top && precedence(top->value) >= precedence(str[i]))
            {
                postStr[index] = top->value;
                index++;
                top = popHead(top);
            }
            top = pushHead(top, str[i]);
        }     
    }

    while (top)
    {
        postStr[index] = top->value;
        index++;
        top = popHead(top);
    }
    postStr[index] = '\0';
    printf("Postfix: %s\n",postStr);
}

int main(){
    char str[] = "(a+b)*(c/(d-e))+f^g";
    int size = strlen(str);

    prefix(str);
    postfix(str);

    return 0;
}