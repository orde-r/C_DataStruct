#include <stdio.h>
#include <stdlib.h>

typedef struct node node;

struct node{
	node *left;
	node *right;
	int value;
};

node *createNode(int value){
	node *newnode = (node*)malloc(sizeof(node));
	newnode->left = NULL;
	newnode->right = NULL;
	newnode->value = value;
	
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

node *findMax(node *root){
	if(!root) return root;
	while(root->right)
	{
		root = root->right;
	}
	return root;
}

node *findMin(node *root){
	if(!root) return root;
	while(root->left)
	{
		root = root->left;
	}
	return root;
}

node *search(node *root, int value){
	if(!root || root->value == value) return root;
	if(value > root->value)
	{
		return search(root->right, value);
	}
	else if(value < root->value)
	{
		return search(root->left, value);
	}
	return root;
}

node *deletes(node *root, int value){
	if(!root) return root;
	if(value > root->value)
	{
		root->right = deletes(root->right, value);
	}
	else if(value < root->value)
	{
		root->left = deletes(root->left, value);
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
		
		node *temp = findMin(root->right);
		root->value = temp->value;
		root->right = deletes(root->right, temp->value);
	}
	return root;
}

void inorder(node *root){
	if(!root)return;
	
	inorder(root->left);
	printf("%d ", root->value);
	inorder(root->right);
}
void preorder(node *root){
	if(!root)return;
	
	printf("%d ", root->value);
	preorder(root->left);
	preorder(root->right);
}
void postorder(node *root){
	if(!root)return;
	
	postorder(root->left);
	postorder(root->right);
	printf("%d ", root->value);
}

int countNodes(node *root){
	if(!root) return 0;
	return 1 + countNodes(root->left) + countNodes(root->right);
}

int treeHeight(node *root){
	if(!root)return 0;
	int left = treeHeight(root->left);
	int right = treeHeight(root->right);
	
	return 1 + ( left > right ? left : right);
}

int main(){
	
	node *root = NULL;
	root = insert(root, 50);
	root = insert(root, 30);
	root = insert(root, 60);
	root = insert(root, 20);
	root = insert(root, 40);
	root = insert(root, 80);
	root = insert(root, 35);
	root = insert(root, 10);
	root = insert(root, 38);
	root = insert(root, 42);
	root = insert(root, 70);
	root = insert(root, 90);
	
	inorder(root);
	printf("\n");
	preorder(root);
	printf("\n");
	postorder(root);
	printf("\n");
	
	node *max = findMax(root);
	node *min = findMin(root);
	printf("\nMax Value %d\nMin Value: %d\n", max->value, min->value);
	
	printf("Total Nodes in BSTL %d\n", countNodes(root));
	printf("Tree Height: %d\n", treeHeight(root));
	
	int toSearch = 88;
	node *searchVal = search(root, toSearch);
	if(!searchVal) printf("%d isn't in BST\n", toSearch);
	else printf("%d is found in BST\n", toSearch);
	
	int deleteValue = 30;
    root = deletes(root, deleteValue);
    printf("Inorder traversal after deleting %d: ", deleteValue);
    inorder(root);
    printf("\n");

	return 0;
}
