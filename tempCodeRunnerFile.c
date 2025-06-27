#include<stdio.h>
#include<stdlib.h>

struct Node {
	int val;
	int height;
	struct Node *left;
	struct Node *right;
};

int max (int a, int b){
	if (a > b){
		return a;
	}
	else {
		return b;
	}
}

struct Node *getMin (struct Node *root){
	while (root->left!=NULL){
		root=root->left;
	}
	return root;
}

int height (struct Node *root){
	if (root==NULL){
		return 0;
	}
	else {
		return root->height;
	}
}

int balance (struct Node *root){
	if (root==NULL){
		return 0;
	}
	else {
		return height(root->left)-height(root->right);
	}
}

struct Node *createNode (int val){
	struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
	
	newNode->val=val;
	newNode->height=1;
	newNode->left=NULL;
	newNode->right=NULL;
	
	return newNode;
}

struct Node *rightRotate (struct Node *y){
	struct Node *x = y->left;
	struct Node *T2 = x->right;
	
	x->right = y;
	y->left = T2;
	
	y->height = 1+max(height(y->left),height(y->right));
	x->height = 1+max(height(x->left),height(x->right));
	
	return x;
}

struct Node *leftRotate (struct Node *x){
	struct Node *y = x->right;
	struct Node *T2 = y->left;
	
	y->left=x;
	x->right=T2;
	
	x->height = 1+max(height(x->left),height(x->right));
	y->height = 1+max(height(y->left),height(y->right));
	
	return y;
}

struct Node *insertNode (struct Node *root, int val){
	if (root==NULL){
		return createNode (val);
	}
	else if (val < root->val){
		root->left=insertNode (root->left,val);
	}
	else if (val > root->val){
		root->right=insertNode (root->right,val);
	}
	
	root->height= 1+max(height(root->left),height(root->right));
	int bf = balance (root);
	
	if (bf > 1 && val < root->left->val){
		return rightRotate (root);
	}
	if (bf > 1 && val > root->left->val){
		root->left=leftRotate(root->left);
		return rightRotate (root);
	}
	if (bf < -1 && val > root->right->val){
		return leftRotate (root);
	}
	if (bf < -1 && val < root->right->val){
		root->right=rightRotate(root->right);
		return leftRotate(root);
	}
	return root;
}

struct Node *removes (struct Node *root, int val){
	if (root==NULL){
		return NULL;
	}
	else if (val < root->val){
		root->left=removes (root->left,val);
	}
	else if (val > root->val){
		root->right=removes (root->right,val);
	}
	else {
		if (root->left==NULL || root->right == NULL){
			struct Node *temp = NULL;
			if (root->left==NULL){
				temp=root->right;
			}
			else {
				temp=root->left;
			}
			free (root);
			return temp;
		}
		else {
			struct Node *temp = getMin (root->right);
			root->val=temp->val;
			root->right=removes(root->right,temp->val);
		}
	}
	
	if (root==NULL){
		return NULL;
	}
	
	root->height= 1+max(height(root->left),height(root->right));
	int bf = balance (root);
	
	if (bf > 1 && balance (root->left) < 0){
		root->left=leftRotate(root->left);
		return rightRotate(root);
	}
	if (bf > 1 && balance (root->left) >= 0){
		return rightRotate(root);
	}
	if (bf < -1 && balance (root->right) > 0){
		root->right=rightRotate(root->right);
		return leftRotate (root);
	}
	if (bf < -1 && balance (root->right) <= 0){
		return leftRotate (root);
	}
	return root;
}

void print (struct Node *root){
	if (root!=NULL){
		printf ("[%d]",root->val);
        print (root->left);
		print (root->right);
	}
}

int main (){
	struct Node *root=NULL;
	
	root=insertNode(root,7);
	root=insertNode(root,8);
	root=insertNode(root,6);
	root=insertNode(root,5);
	root=insertNode(root,4);
	root=insertNode(root,2);
	
	print (root);
	printf ("\n");
	
	root = removes(root, 5);
	print(root);
	printf("\n");
	root = removes(root, 7);
	print(root);
	printf("\n");
	
	return 0;
}
