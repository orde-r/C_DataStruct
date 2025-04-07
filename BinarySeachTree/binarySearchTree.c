#include <stdio.h>
#include <stdlib.h>

typedef struct Node node;

struct Node
{
    int value;
    node *left;
    node *right;
};



node *createnewnode(int value){
    node *newnode = malloc(sizeof(node));

    newnode->value = value;
    newnode->right = NULL;
    newnode->left = NULL;

    return newnode;
}

node *insert(node *root, int value){    
    if (!root)
    {
        return createnewnode(value);
    }
    
    if (value > root->value)
    {
        root->right = insert(root->right, value);
    } 
    else if (value < root->value)
    {
        root->left = insert(root->left, value);
    }
    
    return root;
}

node *search(node *root, int value){
    if (!root || root->value == value)
    {
        return root;
    }

    if (value > root->value)
    {
        return search(root->right, value);
    } else {
        return search(root->left, value);
    }    
}

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

node *findMax(node *root){
    if (!root)
    {
        return NULL;
    }
    while (root->right)
    {
        root = root->right;
    }
    return root;
}

//https://claude.ai/share/8b2d08e8-296d-4442-a615-be7dcfe273dd
node *delete(node *root, int value){
    if (!root)
    {
        return root;
    }

    if (value > root->value)
    {
        root->right = delete(root->right, value);
    } 
    else if (value < root->value){
        root->left = delete(root->left, value);
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

         //Punya 2 anak    

        //Predecessor = Left Sub Tree -> Right Most Child = The biggest value at the left sub tree
        //Succesor = Right Sub Tree -> Left Mmost Child = THe smalles value at the right sub tree
         
        //Succesor 
        node *temp = findMin(root->right); //Succ
        root->value = temp->value;
        root->right = delete(root->right, temp->value); //Succ
        
        //Predecessor
        // node *temp = findMax(root->left); //Pre
        // root->value = temp->value;
        // root->left = delete(root->left, temp->value); //Pre
    }
    return root;
}

void freeTree(node *root){
    if (root)
    {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

//Traversal
void inorder(node *root){
    if (root)
    {
        inorder(root->left);
        printf("%d ", root->value);
        inorder(root->right);
    }
}

void preorder(node *root){
    if (root)
    {
        printf("%d ",root->value);
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(node *root){
    if (root)
    {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->value);
    }
    
}

int countNodes(node *root){
    if (!root) return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);   
}

int treeHeight(node *root){
    if (!root) return 0;
    int leftSub = treeHeight(root->left);
    int rightSub = treeHeight(root->right);
    return 1 + (leftSub > rightSub ? leftSub : rightSub);
}

int main(){
    node* root = NULL;

    root = insert(root, 50);
    insert(root, 30);
    insert(root, 20);
    insert(root, 40);
    insert(root, 70);
    insert(root, 60);
    insert(root, 80);
    
    printf("Total Nodes: %d\n", countNodes(root));
    printf("Tree Height: %d\n", treeHeight(root));

    // Print inorder traversal
    printf("Inorder traversal: ");
    inorder(root);
    printf("\n");
    
    // Print preorder traversal
    printf("Preorder traversal: ");
    preorder(root);
    printf("\n");
    
    // Print postorder traversal
    printf("Postorder traversal: ");
    postorder(root);
    printf("\n");
    
    // Search for a value
    int searchValue = 40;
    node* result = search(root, searchValue);
    if (result != NULL) {
        printf("Value %d found in the BST\n", searchValue);
    } else {
        printf("Value %d not found in the BST\n", searchValue);
    }
    
    // Delete a node
    int deleteValue = 30;
    root = delete(root, deleteValue);
    printf("Inorder traversal after deleting %d: ", deleteValue);
    inorder(root);
    printf("\n");
    
    // Free the memory
    freeTree(root);
    
}