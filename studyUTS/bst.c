#include <stdio.h>
#include <stdlib.h>

typedef struct node node;

struct node
{
	int value;
	node *left;
	node *right;
};

node *createNode(int value){
	node *newnode = (node *)malloc(sizeof(node));
	
	newnode->value = value;
	newnode->right = NULL;
	newnode->left = NULL;	
	
	return newnode;	
}

node *insert(node *root, int value){
	if(!root) return createNode(value);
	if(value > root->value)
	{
		root->right = insert(root->right, value);
	}
	else if(value < root->value)
	{
		root->left = insert(root->left, value);
	}
	return root;
}

node *search(node *root, int value){
	if(!root || root->value == value) return root;
	if(value > root->value)
	{
		root->right = search(root->right, value);
	}
	else if(value < root->value)
	{
		root->left = search(root->left, value);
	}
	return root;
}

node *findMax(node *root){
	if(!root) return root;
	while(root->right){
		root = root->right;
	}
	return root;
}

node *findMin(node *root){
	if(!root) return root;
	while(root->left){
		root = root->left;
	}
	return root;
}

node *delete(node *root, int value){
	if(!root) return root;
	if(value > root->value)
	{
		root->right = delete(root->right, value);
	}
	else if(value < root->value)
	{
		root->left = delete(root->left, value);
	}
	else{
		if(!root->left)
		{
			node *temp = root->right;
			free(root);
			return temp;
		}
		else if(!root->right)
		{
			node *temp = root->left;
			free(root);
			return temp;
		}
		
		node *temp = findMin(root->right);
		root->value = temp->value;
		root->right = delete(root->right, temp->value);
	}
	return root;
}

void inorder(node *root){
	if(root)
	{
		inorder(root->left);
		printf("%d ", root->value);
		inorder(root->right);
	}
}

int totalNodes(node *root){
	if(!root) return 0;
	return 1 + totalNodes(root->left) + totalNodes(root->right);
}

int treeHeight(node *root){
	if(!root) return 0;
	int left = treeHeight(root->left);
	int right = treeHeight(root->right);
	return 1 + (left > right ? left : right);
}

int main(){

    node *root = NULL;
	root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 20);
    root = insert(root, 70);
    root = insert(root, 40);
    root = insert(root, 60);
    root = insert(root, 90);
    inorder(root);

    printf("\n");
    printf("Total Nodes: %d\n", totalNodes(root));
    printf("Tree Height: %d\n", treeHeight(root));
    
    // Search for a value
    int searchValue = 40;
    node* result = search(root, searchValue);
    if (result != NULL) {
        printf("Value %d found in the BST\n", searchValue);
    } else {
        printf("Value %d not found in the BST\n", searchValue);
    }
    
    result = findMax(root);
    printf("Max Value: %d\n", result->value);
    
    result = findMin(root);
    printf("Min Value: %d\n", result->value);
    
    
    // Delete a node
    int deleteValue = 30;
    root = delete(root, deleteValue);
    printf("Inorder traversal after deleting %d: ", deleteValue);
    inorder(root);
    printf("\n");
    
    return 0;
}
