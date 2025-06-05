#include <stdio.h>
#include <stdlib.h>

typedef struct node node;

struct node
{
    node *left;
    node *right;
    int value;
    int height;
};

node *createNode(int val){
    node *newnode = malloc(sizeof(node));
    newnode->height = 1;
    newnode->value = val;
    newnode->left = NULL;
    newnode->right = NULL;

    return newnode;
}

int getMax(int a, int b){
    return (a > b) ? a : b;
}

int getHeight(node *root){
    if(!root) return 0;
    return root->height;
}

int getBalanceFactor(node *root){
    if (!root) return 0;
    return getHeight(root->left) - getHeight(root->right);
}

node *leftRotate(node *y){
    node *x = y->right;
    node *t2 = x->left;

    x->left = y;
    y->right = t2;

    y->height = 1+max(getHeight(y->left), getHeight(y->right));
    x->height = 1 + max(getHeight(x->left), getHeight(x->right));
    return x;
}

node *rightRotate(node *y){
    node *x = y->left;
    node *t2 = x->right;

    x->right = y;
    y->left = t2;

    y->height = 1+max(getHeight(y->left), getHeight(y->right));
    x->height = 1 + max(getHeight(x->left), getHeight(x->right));
    return x;
}

node *balanceTree(node *root, int val){
    
}

node *findMin(node *root){
    if (!root) return NULL;
    while(root->left){
        root = root->left;
    }
    return root;
}

node *findMax(node *root){
    if (!root) return NULL;
    while(root->right){
        root = root->right;
    }
    return root;
}

node *searchNode(node *root, int val){
    if (!root) return NULL;
    if (root->value == val)
    {
        return root;
    }
    else if (root->value > val)
    {
        return searchNode(root->left, val);
    }
    else if (root->value < val)
    {
        return searchNode(root->right, val);
    }
}

node *insertNode(node *root, int val){

    if (!root)
    {
        return createNode(val);
    }
    if (root->value > val)
    {
        root->left = insertNode(root->left, val);
    }
    else if (root->value < val)
    {
        root->right = insertNode(root->right, val);
    }
    
    root->height = 1 + getMax(getHeight(root->left), getHeight(root->right));
    int balanceFactor = getBalanceFactor(root);

    //Left Left -- Berat kiri putar kanan
    if (balanceFactor > 1 && val < root->left->value)
    {
        return rightRotate(root);
    }
    //Right Right -- Berat kanan putar kiri
    if (balanceFactor < -1 && val > root->right->value)
    {
        return leftRotate(root);
    }
    //Left Right
    if (balanceFactor > 1 && val > root->left->value)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    //Right Left
    if (balanceFactor < -1 && val < root->right->value)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

node *deleteNode(node *root, int val){
    if (!root) return root;
    if (root->value > val)
    {
        root->left = deleteNode(root->left, val);
    }
    else if (root->value < val)
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
        else if (!root->right)
        {
            node *temp = root->left;
            free(root);
            return temp;
        }

        //Predecessor = Left Sub Tree -> Right Most Child = The biggest value at the left sub tree
        //Succesor = Right Sub Tree -> Left Mmost Child = THe smalles value at the right sub tree
        node *temp = findMin(root->right);
        root->value = temp->value;
        root->right = deleteNode(root->right, temp->value);
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

void inorder(node *root){
    if (root)
    {
        inorder(root->left);
        printf("%d ", root->value);
        inorder(root->right);
    }
}

int main(){

    node* root = NULL;
    root = createNode(50);
    root = insertNode(root, 30);
    root = insertNode(root, 20);
    root = insertNode(root, 70);
    root = insertNode(root, 40);
    root = insertNode(root, 60);
    root = insertNode(root, 90);
    inorder(root);

    return 0;
}

