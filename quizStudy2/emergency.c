#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node node;

struct node
{
    node *left;
    node *right;
    int height;
    char str[100];
    float fuel;
    int dist;
};

node *createNode(const char str[], float fuel, int dist){
    node *newnode = malloc(sizeof(node));
    newnode->left = NULL;
    newnode->right = NULL;
    newnode->height = 1;
    newnode->fuel = fuel;
    newnode->dist = dist;
    strcpy(newnode->str, str);
    return newnode;
}

int max(int a, int b){
    return a > b ? a : b;
}

int getHeight(node *root){
    if (!root) return 0;
    return root->height;
}

int getBalance(node *root){
    if(!root) return 0;
    return getHeight(root->left) - getHeight(root->right);
}

int inputHeight(node *root){
    return 1 + max(getHeight(root->left), getHeight(root->right));
}

node *getMin(node *root){
    while (root && root->left) {
        root = root->left;
    }
    return root;
}

node *leftRotate(node *y){
    node *x = y->right;
    node *t2 = x->left;

    x->left = y;
    y->right = t2;

    y->height = inputHeight(y);
    x->height = inputHeight(x);
    
    return x;
}

node *rightRotate(node *y){
    node *x = y->left;
    node *t2 = x->right;

    x->right = y;
    y->left = t2;

    y->height = inputHeight(y);
    x->height = inputHeight(x);

    return x;
}


node *insertNode(node* root, const char str[], float fuel , int dist){
    if (!root) return createNode(str,fuel,dist);
    if (fuel > root->fuel || (fuel == root->fuel && dist < root->dist)) root->right = insertNode(root->right, str, fuel, dist);
    else if (fuel < root->fuel || (fuel == root->fuel && dist > root->dist)) root->left = insertNode(root->left, str, fuel, dist);
    
    root->height = inputHeight(root);

    int balance = getBalance(root);
    if (balance > 1 && (fuel < root->left->fuel || (fuel == root->left->fuel && dist > root->left->dist)))
    {
        return rightRotate(root);
    }
    if (balance < -1 && (fuel > root->right->fuel || (fuel == root->right->fuel && dist < root->right->dist)))
    {
        return leftRotate(root);
    }
    if (balance > 1 && (fuel > root->left->fuel || (fuel == root->left->fuel && dist < root->left->dist)))
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && (fuel < root->right->fuel || (fuel == root->right->fuel && dist > root->right->dist)))
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    
    return root;
}

node *deleteNode(node* root, const char str[], float fuel , int dist){
    if (!root) return root;
    if (fuel > root->fuel || (fuel == root->fuel && dist < root->dist)) root->right = deleteNode(root->right, str, fuel, dist);
    else if (fuel < root->fuel || (fuel == root->fuel && dist > root->dist)) root->left = deleteNode(root->left, str, fuel, dist);
    else {
        if (!root->left)
        {
            node *temp = root->right;
            free(root);
            return temp;
        }
        if (!root->right)
        {
            node *temp = root->left;
            free(root);
            return temp;
        }
        node *temp = getMin(root->right);
        root->dist = temp->dist;
        root->fuel = temp->fuel;
        strcpy(root->str, temp->str);
        root->right = deleteNode(root->right, temp->str, temp->fuel, temp->dist);
    }
    root->height = inputHeight(root);

    int balance = getBalance(root);
    if (balance > 1 && getBalance(root->left) >= 0)
    {
        return rightRotate(root);
    }
    if (balance < -1 && getBalance(root->right) <= 0)
    {
        return leftRotate(root);
    }
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

void inorder(node *root){
    if (!root) return;
    inorder(root->left);
    printf("%s ", root->str);
    inorder(root->right);    
}

int main(){

    node *root = NULL;
    root = insertNode(root, "XZ5", 0.5, 50);
    root = insertNode(root, "XZ66", 0.5, 45);
    root = insertNode(root, "XZ12", 0.5, 30);
    root = insertNode(root, "XZ45", 0.6, 20);
    root = insertNode(root, "XZ56", 0.55, 30);
    root = insertNode(root, "XZ98", 0.53, 60);
    inorder(root);

    node *todelete = getMin(root);
    root = deleteNode(root, todelete->str, todelete->fuel, todelete->dist);
    todelete = getMin(root);
    root = deleteNode(root, todelete->str, todelete->fuel, todelete->dist);
    printf("\n");
    inorder(root);

    return 0;
}
