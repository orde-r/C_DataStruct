#include <stdio.h>
#include <stdlib.h>

struct Data{
	int number;
	struct Data *left;
	struct Data *right;
	int height; //height of node;
};

struct Data *createNode(int number){
	struct Data *newNode = (struct Data*)malloc(sizeof(struct Data));
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->number = number;
	newNode->height = 1;
	
	return newNode;
}

//get max value
int max(int a, int b){
	if (a > b){
		return a;
	}
	return b;
}

int height(struct Data *root){
	if(root == NULL){
		return 0;
	}
	return root->height;
}

int getBalanceFactor(struct Data *root){
	if (root == NULL){
		return 0;
	}
	return height(root->left) - height(root->right);
}

struct Data *rightRotate(struct Data *y){
	struct Data *x = y->left;
	struct Data *T2 = x->right;
	
	//rotate here
	x->right = y;
	y->left = T2;
	
	//update height of node
	y->height = 1 + max(height(y->left), height(y->right));
	x->height = 1 + max(height(x->left), height(x->right));
	
	//x is the new parent
	return x;
}

struct Data *leftRotate(struct Data *x){
	struct Data *y = x->right;
	struct Data *T2 = y->left;
	
	//rotate here
	y->left = x;
	x->right = T2;
	
	//update height of node
	x->height = 1 + max(height(x->left), height(x->right));
	y->height = 1 + max(height(y->left), height(y->right));
	
	//y is the new parent
	return y;
}

//get Successor of Right Subtree / get MinValue 
struct Data *getSuccessor(struct Data *root){
	if (root->left != NULL){
		root = getSuccessor(root->left);
	}
	return root;
}

struct Data *insertNode(struct Data *root, int number){
	//find position
	if (root == NULL){
		return createNode(number);
	}
	else if(number < root->number){
		root->left = insertNode(root->left, number);
	}
	else if(number > root->number){
		root->right = insertNode(root->right, number);
	}
	
	//update height of node
	root->height = 1 + max(height(root->left), height(root->right));
	
	//get balance factor
	int balanceFactor = getBalanceFactor(root);
	
	//case 1: LL Rotation
	if(balanceFactor > 1 && number < root->left->number){
		//do single right rotation
		return rightRotate(root);
	}
	//case 2: RR Rotation
	if(balanceFactor < -1 && number > root->right->number){
		//do single left rotation
		return leftRotate(root);
	}
	//case 3: LR Rotation
	if (balanceFactor > 1 && number > root->left->number){
		//do double rotation
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}
	//case 4: Rl rotation
	if (balanceFactor < -1 && number < root->right->number){
		//do double rotation
		root->right = rightRotate(root->right);
		return leftRotate(root);
	}
	return root;
}

struct Data *deleteNode(struct Data *root, int number){
	//find node
	if(root == NULL){
		return root;
	} 
	else if (number < root->number){
		root->left = deleteNode(root->left, number);
	}
	else if (number > root->number){
		root->right = deleteNode(root->right, number);
	}
	//node were found
	else {
		if ((root->left == NULL) || (root->right == NULL)){
			struct Data *temp = root->left ? root->left : root->right;
			
			if (temp == NULL){
				temp = root;
				root = NULL;
			}
			else{
				*root = *temp;
			}
			free(temp);
		}
		// case deletion punya 2 children
		// solved dengan predecessor atau successor
		else{
			struct Data *temp = getSuccessor(root->right);
			root->number = temp->number;
			
			root->right = deleteNode(root->right, temp->number);
		}
	}
	
	if (root == NULL){
		return root;
	}
	
	// update height 
	root->height = 1 + max(height(root->left), height(root->right));
	
	// balance factor
	int balanceFactor = getBalanceFactor(root);
	
	// case 1: LL
	if (balanceFactor > 1 && getBalanceFactor(root->left) >= 0){
		return rightRotate(root);
	}
	// case 2: RR
	if (balanceFactor < -1 && getBalanceFactor(root->right) <= 0){
		return leftRotate(root);
	}
	// case 3: LR
	if (balanceFactor > 1 && getBalanceFactor(root->left) < 0){
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}
	// case 4: RL
	if (balanceFactor < -1 && getBalanceFactor(root->right) > 0){
		root->right = rightRotate(root->right);
		return leftRotate(root);
	}
	
	return root;
}

void inorder(struct Data *root){
	if (root != NULL){
		inorder(root->left);
		printf("%d ", root->number);
		inorder(root->right);
	}
}

int main(){
	struct Data *root = NULL;
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
