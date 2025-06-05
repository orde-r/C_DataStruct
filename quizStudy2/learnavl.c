#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node node;

struct node{
    node *left;
    node *right;
    int val;
    int height;
};

node *createNode(int val){
    node *newnode = malloc(sizeof(node));
    newnode->right = NULL;
    newnode->left = NULL;
    newnode->val = val;
    newnode->height = 1;
    return newnode;
}

int getMax(int a, int b){
    return a > b ? a : b;
}

int getHeight(node *root){
    if (!root) return 0;
    return root->height;
}

int getBalanceFactor(node *root){
    if (!root) return 0;
    return getHeight(root->left) - getHeight(root->right);
}

node *rightRotate(node *y){
    node *x = y->left;
    node *t2 = x->right;

    x->right = y;
    y->left = t2;

    y->height = 1 + getMax(getHeight(y->left), getHeight(y->right));
    x->height = 1 + getMax(getHeight(x->left), getHeight(x->right));

    return x;
}

node *leftRotate(node *y){
    node *x = y->right;
    node *t2 = x->left;

    x->left = y;
    y->right = t2;

    y->height = 1 + getMax(getHeight(y->left), getHeight(y->right));
    x->height = 1 + getMax(getHeight(x->left), getHeight(x->right));

    return x;
}

node *insertNode(node *root, int val){
    if(!root) return createNode(val);
    if (val > root->val) root->right = insertNode(root->right, val);
    else if (val < root->val) root->left = insertNode(root->left, val);
    
    root->height = 1 + getMax(getHeight(root->left), getHeight(root->right));

    int balance = getBalanceFactor(root);

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

node *findMin(node *root){
    if (!root) return root;
    while (root->left)
    {
        root = root->left;
    }
    return root;
}

node *deleteNode(node *root, int val){
    if (!root) return root;
    if (val > root->val) root->right = deleteNode(root->right, val);
    else if (val < root->val) root->left = deleteNode(root->left, val);
    else
    {
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
        
        node *temp = findMin(root->right);
        root->val = temp->val;
        root->right = deleteNode(root->right, temp->val);
    }

    root->height = 1 + getMax(getHeight(root->left), getHeight(root->right));
    int balance = getBalanceFactor(root);

    if (balance > 1 && getBalanceFactor(root->left) >= 0)
    {
        return rightRotate(root);
    }
    if (balance < -1 && getBalanceFactor(root->right) <= 0)
    {
        return leftRotate(root);
    }
    if (balance > 1 && getBalanceFactor(root->left) < 0)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && getBalanceFactor(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    
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

void preorder(node *root){
    if (root){
        printf("%d ", root->val);
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(node *root){
    if (root){
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->val);
    }
}

int main(){

    node *root = NULL;
//	10, 15, 20, 9, 5, 16, 17, 8, 6

	root = createNode(10);
	root = insertNode(root, 15);
	root = insertNode(root, 20);//single rotation Case 2 RR Rotation
	root = insertNode(root, 9);
	root = insertNode(root, 5);//violation rotation case 1 LL Rotation
	root = insertNode(root, 16);
	root = insertNode(root, 17);//violation double rotation case 3 LR
	root = insertNode(root, 8);
	root = insertNode(root, 6); //violation double rotation case 4 RL
	
	inorder(root);
	
	printf("\n\nDeletion\n\n");
	
	root = deleteNode(root, 8);
	root = deleteNode(root, 10);
	root = deleteNode(root, 15);
	inorder(root);

    return 0;
}