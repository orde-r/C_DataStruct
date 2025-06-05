#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node node;

struct node{
    node *left;
    node *right;
    int val;
    int height;
    char skill[200];
};

node *createNode(const char skill[], int val){
    node *newnode = malloc(sizeof(node));
    newnode->right = NULL;
    newnode->left = NULL;
    newnode->val = val;
    newnode->height = 1;
    strcpy(newnode->skill, skill);
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
    if (!root) return 0;
    return getHeight(root->left) - getHeight(root->right);
}

node *getMin(node *root){
    if (!root) return NULL;
    while (root->left)
    {
        root = root->left;
    }
    return root;
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

node *rightRotate(node *y){
    node *x = y->left;
    node *t2 = x->right;

    x->right = y;
    y->left = t2;

    y->height = 1 + max(getHeight(y->left), getHeight(y->right));
    x->height = 1 + max(getHeight(x->left), getHeight(x->right));

    return x;
}

node *insertNode(node *root, const char skill[], int val){
    if (!root) return createNode(skill, val);
    if (strcmp(skill, root->skill) < 0) root->left = insertNode(root->left, skill, val);
    else 
    {
        root->right = insertNode(root->right, skill, val);
    }
    
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    
    int balance = getBalance(root);

    if (balance > 1 && strcmp(skill, root->left->skill) < 0)
    {
        return rightRotate(root);
    }
    if (balance < -1 && strcmp(skill, root->right->skill) > 0)
    {
        return leftRotate(root);
    }
    if (balance > 1 && strcmp(skill, root->left->skill) > 0)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && strcmp(skill, root->right->skill) < 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    
    return root;   
}

node *deleteNode(node *root, const char skill[]){
    if (!root) return NULL;
    if (strcmp(skill, root->skill) < 0)
    {
        root->left = deleteNode(root->left, skill);
    }
    else if (strcmp(skill, root->skill) > 0)
    {
        root->right = deleteNode(root->right, skill);
    }
    else
    {
        if (!root->left)
        {
            node *temp = root->right;
            free(root);
            return temp;
        }
        else if (!root->right)
        {
            node *temp = root->left;
            free(root);
            return temp;
        }
        node *temp = getMin(root->right);
        strcpy(root->skill, temp->skill);
        root->val = temp->val;
        root->right = deleteNode(root->right, temp->skill);
    }

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
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

node *findNode(node *root, const char str[]){
    if (!root || strcmp(str, root->skill) == 0) return root;
    if (strcmp(str, root->skill) < 0)
    {
        printf("(Left)\n");
        return findNode(root->left, str);
    }
    else if (strcmp(str, root->skill) > 0)
    {
        printf("(Right)\n");
        return findNode(root->right, str);
    }
    return root;    
}

void inorder(node *root){
    if (root)
    {
        inorder(root->left);
        printf("%s ", root->skill);
        inorder(root->right);
    }
}

int main(){
    node *root = NULL;

    // Insert skills
    root = insertNode(root, "Java", 10);
    root = insertNode(root, "C", 8);
    root = insertNode(root, "Python", 12);
    root = insertNode(root, "C++", 9);
    root = insertNode(root, "Go", 7);

    printf("Inorder traversal after insertion:\n");
    inorder(root);
    printf("\n");

    //Find
    node *find = findNode(root, "C");

    // Delete a skill
    root = deleteNode(root, "Python");
    printf("Inorder traversal after deleting 'Python':\n");
    inorder(root);
    printf("\n");

    return 0;
}