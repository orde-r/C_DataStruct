#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  int key;
  struct node *left;
  struct node *right;
  int height;
} node;

typedef struct AVL_tree {
  node *root;
} AVL;

AVL *newAVL() {
  AVL *tree = (AVL *)malloc(sizeof(AVL));
  tree->root = NULL;
  return tree;
}

node *newNode(int key) {
  node *n = (node *)malloc(sizeof(node));
  n->key = key;
  n->left = NULL;
  n->right = NULL;
  n->height = 1; // default height
  return n;
}

int get_height(node *n) {
  if(n == NULL) return 0;
  return n->height;
}

int max(int a, int b) {
  return (a > b) ? a : b;
}

node *rightRotate(node *y) {
  node *x = y->left;
  node *T2 = x->right;
  // perform rotation
  x->right = y;
  y->left = T2;
  // update height
  y->height = max(get_height(y->left), get_height(y->right)) + 1;
  x->height = max(get_height(x->left), get_height(x->right)) + 1;
  // return new root
  return x;
}

node *leftRotate(node *x) {
  node *y = x->right;
  node *T2 = y->left;
  // perform rotation
  y->left = x;
  x->right = T2;
  // update height
  x->height = max(get_height(x->left), get_height(x->right)) + 1;
  y->height = max(get_height(y->left), get_height(y->right)) + 1;
  // return new root
  return y;
}

int get_balance(node *n) {
  if (n == NULL) return 0;
  return get_height(n->left) - get_height(n->right);
}

node *insertNode(node *root, int key) {
  // bst insertion
  if(root == NULL) {
    return newNode(key);
  } else if(key < root->key) {
    root->left = insertNode(root->left, key);
  } else if(key > root->key) {
    root->right = insertNode(root->right, key);
  } else {
    return root; // equal key case
  }
  // update root height
  root->height = 1 + max(get_height(root->left), get_height((root->right)));
  // get balance factor from root
  int balance = get_balance(root);
  // perform rotation when balance factor isn't balanced.
  // LEFT LEFT rotation
  if(balance > 1 && key < root->left->key) return rightRotate(root);
  // RIGHT RIGHT rotation
  if(balance < -1 && key > root->right->key) return leftRotate(root);
  // LEFT RIGHT rotation
  if(balance > 1 && key > root->left->key) {
    root->left = leftRotate(root->left);
    return rightRotate(root);
  }
  // RIGHT LEFT rotation
  if(balance < -1 && key < root->right->key) {
    root->right = rightRotate(root->right);
    return leftRotate(root);
  }
  return root;
}

void insert(AVL *tree, int key) {
    if (tree != NULL) {
        tree->root = insertNode(tree->root, key);
    }
}

node *successor(node *root) {
  node *curr = root->right;
  while(curr->left != NULL) {
    curr = curr->left;
  }
  return curr;
}

node* removeNode(node *root, int key) {
  if(root == NULL) {
    return root;
  } else if(key < root->key) {
    root->left = removeNode(root->left, key);
  } else if(key > root->key) {
    root->right = removeNode(root->right, key);
  } else {
    if(root->left == NULL && root->right == NULL) {
      free(root);
      root = NULL;
    } else if(root->left == NULL || root->right == NULL) {
      node *temp;
      if(root->left == NULL) {
        temp = root->right;
      } else {
        temp = root->left;
      }
      *root = *temp;
      free(temp);
    } else {
      node *temp = successor(root);
      root->key = temp->key;
      root->right = removeNode(root->right, temp->key);
    }
  }
  // early return after deletion
  if(root == NULL) return root;
  // update root height
  root->height = 1 + max(get_height(root->left), get_height((root->right)));
  // get balance factor from root
  int balance = get_balance(root);
  // perform rotation when balance factor isn't balanced.
  // LEFT LEFT rotation
  if(balance > 1 && get_balance(root->left) >= 0) return rightRotate(root);
  // RIGHT RIGHT rotation
  if(balance < -1 && get_balance(root->right) <= 0) return leftRotate(root);
  // LEFT RIGHT rotation
  if(balance > 1 && get_balance(root->left) < 0) {
    root->left = leftRotate(root->left);
    return rightRotate(root);
  }
  // RIGHT LEFT rotation
  if(balance < -1 && get_balance(root->right) > 0) {
    root->right = rightRotate(root->right);
    return leftRotate(root);
  }
  return root;
}

void remove(AVL *tree, int key) {
    if (tree != NULL) {
        tree->root = removeNode(tree->root, key);
    }
}

void infix(node* root) {
    if (root != NULL) {
        infix(root->left);
        printf("key: %d\n", root->key);
        infix(root->right);
    }
}

int main() {
  AVL *tree = newAVL();
  insert(tree, 1);
  insert(tree, 2);
  insert(tree, 3);
  insert(tree, 4);
  remove(tree, 3);
  infix(tree->root);
  return 0;
}
