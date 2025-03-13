#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
}node;



node *createnewnode(int data){
    node *newnode = malloc(sizeof(node));

    newnode->data = data;
    newnode->right = NULL;
    newnode->left = NULL;

    return newnode;
}

//Predecessor = Left Sub Tree -> Right Most Child = The biggest value at the left sub tree
//Succesor = Right Sub Tree -> Left Mmost Child = THe smalles value at the right sub tree

node *getPredecessor(node *root){
    if (root->right)
    {
        root = getPredecessor(root->right);
    }
    return root;
}

node *getSuccesor(node *root){
    if (root->left)
    {
        root = getSuccesor(root->left);
    }
    return root;
}

node *search(node *root, int data){
    if (!root || root->data == data)
    {
        return root;
    }
    else if (data < root->data)
    {
        search(root->left, data);
    }
    else if (data > root->data)
    {
        search(root->right, data);
    }    
}

node *insert(node *root, int data){
    if (!root)
    {
        return createnewnode(data);
    }   
    
    if (data > root->data)
    {
        root->right = insert(root->right, data);
    } 
    else if (data < root->data)
    {
        root->left = insert(root->left, data);
    }
    
    return root;
}

node *delete(node *root, int data){
    if (!root)
    {
            return root;
    }
    else if (data < root->data)
    {
            root->left = delete(root->left, data);
    }
    else if (data > root->data)
    {
            root->right = delete(root->right, data);
    }
    else{
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
        node *succesor = getSuccesor(root->right);
        root->data = succesor->data;
        root->right = delete(root->right, succesor->data);
    }
    return root;
}

void inorder(node *root){
    if (root)
    {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
    
}

int main(){
    node* root = NULL;
    root = createnewnode(50);
    root = insert(root, 30);
    root = insert(root, 20);
    root = insert(root, 70);
    root = insert(root, 40);
    root = insert(root, 60);
    root = insert(root, 90);
    inorder(root);

    node *predecesor = getPredecessor(root->left);
    node *succesor = getSuccesor(root->right);
    printf("pre: %d, suc: %d\n", predecesor->data, succesor->data);

    printf("\n\nDelete\n");
    root = delete(root, 60);
    inorder(root);
}