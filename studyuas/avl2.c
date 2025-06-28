#include <stdio.h>
#include <stdlib.h>

typedef struct node node;
struct node
{
    node *left;
    node *right;
    int val;
    int height;
};

node *createNode(int val){
    node *newnode = malloc(sizeof(node));
    newnode->left = NULL;
    newnode->right = NULL;
    newnode->val = val;
    newnode->height = 1;
    return newnode;
}

int getMax(int a, int b){
    return a > b ? a : b;
}

int getHeight(node *root){
    if(!root) return 0;
    return root->height;
}

int setHeight(node *root){
    return 1 + getMax(getHeight(root->left), getHeight(root->right));
}

int getBalance(node *root){
    if(!root) return 0;
    return getHeight(root->left) - getHeight(root->right);
}

node *getMin(node *root){
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
    y->height = setHeight(y);
    x->height = setHeight(x);
    return x;
}

node *rightRotate(node *y){
    node *x = y->left;
    node *t2 = x->right;

    x->right = y;
    y->left = t2;
    y->height = setHeight(y);
    x->height = setHeight(x);
    return x;
}

node *balancing(node *root){
    if(!root) return NULL;
    int balance = getBalance(root);
    int leftBalance = getBalance(root->left);
    int rightBalance = getBalance(root->right);
    if (balance > 1 && leftBalance >= 0)
    {
        return rightRotate(root);
    }
    else if (balance < -1 && rightBalance <= 0)
    {
        return leftRotate(root);
    }
    else if (balance < -1 && rightBalance > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    else if (balance > 1 && leftBalance < 0)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    return root;
}

node *insertNode(node *root, int val){
    if(!root) return createNode(val);
    if (val > root->val) root->right = insertNode(root->right, val);
    else if (val < root->val) root->left = insertNode(root->left, val);
    root->height = setHeight(root);
    root = balancing(root);
    return root;
}

node *deleteNode(node *root, int val){
    if(!root) return NULL;
    if (val > root->val) root->right = deleteNode(root->right, val);
    else if (val < root->val) root->left = deleteNode(root->left, val);
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
        root->val = temp->val;
        root->right = deleteNode(root->right, temp->val);
    }
    root->height = setHeight(root);
    root = balancing(root);
    return root;
}

void inorder(node *root){
    if (root)
    {
        inorder(root->left);
        printf("%d ", root->val);
        inorder(root->right);
    }
}

int main(){
    node* root = NULL;
    root = createNode(100);
    root = insertNode(root, 20);
    root = insertNode(root, 30);
    root = insertNode(root, 400);
    root = insertNode(root, 300);
    root = insertNode(root, 215);
    root = insertNode(root, 90);
    root = insertNode(root, 9);
    root = insertNode(root, 10);
    inorder(root);

    root = deleteNode(root, 40);
    root = deleteNode(root, 20);
    root = deleteNode(root, 10);
    root = deleteNode(root, 215);
    printf("\n");
    inorder(root);
    return 0;
}