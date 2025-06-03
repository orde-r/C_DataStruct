#include <stdio.h>
#include <stdlib.h>

typedef struct Node node;

struct Node{
    int val;
    int height;
    node *left;
    node *right;
};

node *createNode(int val){
    node *newnode = malloc(sizeof(node));
    newnode->val = val;
    newnode->height = 1;
    newnode->left = NULL;
    newnode->right = NULL;

    return newnode;
}

int max(int a, int b){
    return a > b ? a : b;
}

int getHeight(node *root){
    if(!root) return 0;
    return root->height;
}

int getBalanceFactor(node *root){
    if (!root) return 0;
    return getHeight(root->left) - getHeight(root->right);
}

node *rightRotate(node *y){
    node *x = y->left;
    node *T2 = x->right;

    //Rotate
    x->right = y;
    y->left = T2;

    //Update height
    y->height = 1+max(getHeight(y->left), getHeight(y->right));
    return x;
}

node *leftRotate(node *x){
    node *y = x->right;
    node *T2 = y->left;

    //Rotate
    y->left = x;
    x->right = T2;

    //Update height
    x->height = 1+max(getHeight(x->left), getHeight(x->right));

    return y;
}

node *balancing(node *root, int val){
    root->height = 1 + max(getHeight(root->left),getHeight(root->right));

    int balanceFactor = getBalanceFactor(root);

    //Left Left
    if (balanceFactor > 1 && val < root->left->val)
    {
        return rightRotate(root);
    }
    //Right Right
    if (balanceFactor < -1 && val > root->right->val)
    {
        return leftRotate(root);
    }
    //Left Right
    if (balanceFactor > 1 && val > root->left->val)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    //Right left
    if (balanceFactor < -1 && val < root->right->val)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }  
    return root;
}

node *insert(node *root, int val){
    if (!root) return createNode(val);;
    if (val > root->val) root->right = insert(root->right,val);
    else if (val < root->val) root->left = insert(root->left,val);
    
    return balancing(root, val);
}

//Succesor = Right Sub Tree -> Left Mmost Child = THe smalles value at the right sub tree
node *findMin(node *root){
    if (!root)
    {
        return NULL;
    }
    while (root->left)
    {
        root = root->left;
    }
    return root;
}

node *deleteNode(node *root, int val){
    if (!root)
    {
        return root;
    }
    else if (val < root->val)
    {
        root->left = deleteNode(root->left, val);
    }
    else if (val > root->val)
    {
        root->right = deleteNode(root->right, val);
    }
    else
    {
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
        //Succesor 
        node *temp = findMin(root->right); //Succ
        root->val = temp->val;
        root->right = deleteNode(root->right, temp->val); //Succ
    }
    return balancing(root, val);
}

void inOrder(node *root) {
    if (!root) return;
    inOrder(root->left);
    printf("%d ", root->val);
    inOrder(root->right);
}

int main(){
    node *root = NULL;

    // Insert nodes
    int values[] = {10, 20, 30, 40, 50, 25};
    int n = sizeof(values) / sizeof(values[0]);
    printf("Inserting values: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", values[i]);
        root = insert(root, values[i]);
    }
    printf("\nIn-order after insertions: ");
    inOrder(root);
    printf("\n");

    // Delete a leaf node
    printf("\nDeleting leaf node 25...\n");
    root = deleteNode(root, 25);
    printf("In-order after deleting 25: ");
    inOrder(root);
    printf("\n");

    // Delete a node with one child
    printf("\nDeleting node with one child (50)...\n");
    root = deleteNode(root, 50);
    printf("In-order after deleting 50: ");
    inOrder(root);
    printf("\n");

    // Delete a node with two children
    printf("\nDeleting node with two children (30)...\n");
    root = deleteNode(root, 30);
    printf("In-order after deleting 30: ");
    inOrder(root);
    printf("\n");

    return 0;
}
