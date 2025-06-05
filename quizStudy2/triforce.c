#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node node;

int wisdom, power, courage;

struct node
{
    node *left;
    node *right;
    int height;
    char str[100];
    int val;
};

node *createNode(int val, const char str[]){
    node *newnode = malloc(sizeof(node));
    newnode->left = NULL;
    newnode->right = NULL;
    newnode->val = val;
    newnode->height = 1;
    strcpy(newnode->str, str);

    if (strcmp(str, "Power") == 0) power++;
    if (strcmp(str, "Wisdom") == 0) wisdom++;
    if (strcmp(str, "Courage") == 0) courage++;

    return newnode;
}

int max(int a, int b){
    return a > b ? a : b;
}

int getHeight(node *root){
    if(!root) return 0;
    return root->height;
}

int getBalance(node *root){
    if (!root) return 0;
    return getHeight(root->left) - getHeight(root->right);    
}

node *getMin(node *root){
    if (!root) return root;
    while (root->left)
    {
        root = root->left;
    }
    return root;
}

node *rightRotate(node *y){
    node *x = y->left;
    node *t2 = x->right;

    x->right = y;
    y->left = t2;

    y->height = 1 + max(getHeight(y->left), getHeight(y->right));
    x->height = 1 + max(getHeight(x->left), getHeight(x->right));

    return x;
}

node *leftRotate(node *y){
    node *x = y->right;
    node *t2 = x->left;

    x->left = y;
    y->right = t2;

    y->height = 1 + max(getHeight(y->left), getHeight(y->right));
    x->height = 1 + max(getHeight(x->left), getHeight(x->right));

    return x;
}

node *insertNode(node *root, int val, const char str[]){
    if (!root) return createNode(val, str);
    if (val > root->val) root->right = insertNode(root->right, val, str);
    else if (val < root->val) root->left = insertNode(root->left, val, str);
    else if (val == root->val) return root;
    
    
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    int balance = getBalance(root);

    if (balance > 1 && val < root->left->val) return rightRotate(root);
    if (balance < -1 && val > root->right->val) return leftRotate(root);
    if (balance > 1 && val > root->left->val) 
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && val < root->right->val)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }  
    return root;
}

node *deleteNode(node *root, int val){
    if (!root) return root;
    if (val > root->val) root->right = deleteNode(root->right, val);
    else if (val < root->val) root->left = deleteNode(root->left, val);
    else {
        if (strcmp(root->str, "Power") == 0) power--;
        if (strcmp(root->str, "Wisdom") == 0) wisdom--;
        if (strcmp(root->str, "Courage") == 0) courage--;
        if (!root->right)
        {
            node *temp = root->left;
            free(root);
            return temp;
        }
        else if (!root->left)
        {
            node *temp = root->right;
            free(root);
            return temp;
        }
        node *temp = getMin(root->right);
        root->val = temp->val;
        strcpy(root->str, temp->str);
        root->right = deleteNode(root->right, temp->val);
    }
    
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0) return rightRotate(root);
    if (balance < -1 && getBalance(root->right) <= 0) return leftRotate(root);
    if (balance > 1 && getBalance(root->left) < 0) 
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }  
    return root;
}

void findTriforce(node *root){
    if (!root) return;
    if (
        strcmp("Power", root->str) == 0 &&
        strcmp("Wisdom", root->left->str) == 0 &&
        strcmp("Courage", root->right->str) == 0
    ) {
        printf("Jawa Jawa Jawa\n");
        return;
    }
    findTriforce(root->left);
    findTriforce(root->right);
}

void printStats(){
    printf("%d %d %d\n", power, wisdom, courage);
}

int main(){
    node *root;
    root = NULL;
    root = insertNode(root,89,"Courage");
    printStats();

    root = insertNode(root,57,"Power");
    printStats();

    root = insertNode(root,34,"Wisdom");
    printStats();

    root = insertNode(root,34,"Courage");
    printStats();

    findTriforce(root);

    root = insertNode(root,26,"Power");
    printStats();

    root = insertNode(root,13,"Courage");
    printStats();

    findTriforce(root);

    root = deleteNode(root,89);
    printf("%d\n", power+wisdom+courage);

    root = insertNode(root,77,"Courage");
    printStats();

    root = deleteNode(root,78);
    printf("%d\n", power+wisdom+courage);

    findTriforce(root);
    // inorder(root);
}

