#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
  int num;
  char quote[202];

  struct node *left;
  struct node *right;

  int height;
} Node;

Node *nodenew(const int num, const char *quote) {
  Node *n = (Node *)calloc(1, sizeof(Node));
  n->num = num;
  strcpy(n->quote, quote);
  n->height = 1;
  return n;
}

int max(const int a, const int b) {
  if (a > b) {
    return a;
  }
  return b;
}

int height(const Node *root) {
  if (!root) {
    return 0;
  }
  return root->height;
}

int getbf(Node *root) {
  if (!root) {
    return 0;
  }
  return height(root->left) - height(root->right);
}

/*
y
 \
  x
 / \
t2  a

  x
 / \
y   a
 \
  t2
*/
Node *leftrot(Node *y) {
  Node *x = y->right;
  Node *t2 = x->left;

  x->left = y;
  y->right = t2;

  x->height = 1 + max(height(x->left), height(x->right));
  y->height = 1 + max(height(y->left), height(y->right));

  return x;
}

Node *rightrot(Node *y) {
  Node *x = y->left;
  Node *t2 = x->right;

  x->right = y;
  y->left = t2;

  x->height = 1 + max(height(x->left), height(x->right));
  y->height = 1 + max(height(y->left), height(y->right));

  return x;
}

Node *ins(Node *root, Node *newn) {
  if (!root) {
    return newn;
  }

  if (newn->num < root->num) {
    root->left = ins(root->left, newn);
  } else if (newn->num > root->num) {
    root->right = ins(root->right, newn);
  }

  root->height = 1 + max(height(root->left), height(root->right));
  int bf = getbf(root);

  if (bf > 1 && newn->num < root->left->num) {
    // LL
    return rightrot(root);
  } else if (bf < -1 && newn->num > root->right->num) {
    // RR
    return leftrot(root);
  } else if (bf > 1 && newn->num > root->left->num) {
    // LR
    root->left = leftrot(root->left);
    return rightrot(root);
  } else if (bf < -1 && newn->num < root->right->num) {
    // RL
    root->right = rightrot(root->right);
    return leftrot(root);
  }

  return root;
}

// go right once
Node *getsuc(Node *root) {
  if (root->left) {
    return getsuc(root->left);
  }
  return root;
}

Node *del(Node *root, const int num) {
  if (!root) {
    return root;
  }

  if (num < root->num) {
    root->left = del(root->left, num);
  } else if (num > root->num) {
    root->right = del(root->right, num);
  } else {
    if (root->left == NULL || root->right == NULL) {
      Node *temp = root->left ? root->left : root->right;

      if (!temp) {
        temp = root;
        root = NULL;
      } else {
        *root = *temp;
      }
      free(temp);
    } else {
      Node *suc = getsuc(root->right);
      root->num = suc->num;
      strcpy(root->quote, suc->quote);
      root->right = del(root->right, suc->num);
    }
  }

  if (!root) {
    return root;
  }

  root->height = 1 + max(height(root->left), height(root->right));
  int bf = getbf(root);

  if (bf > 1 && getbf(root->left) >= 0) {
    // LL
    return rightrot(root);
  } else if (bf < -1 && getbf(root->right) <= 0) {
    // RR
    return leftrot(root);
  } else if (bf > 1 && getbf(root->left) < 0) {
    // LR
    root->left = leftrot(root->left);
    return rightrot(root);
  } else if (bf < -1 && getbf(root->right) > 0) {
    // RL
    root->right = rightrot(root->right);
    return leftrot(root);
  }

  return root;
}

void preorder(const Node *root) {
  if (!root) {
    return;
  }
  printf("%d ", root->num);
  preorder(root->left);
  preorder(root->right);
}

typedef struct input {
  int num;
  char quote[202];
} Input;

void solve(const Input inputs[], const int n) {
  int longest_len = 0;
  int longest_num = -1;

  int shortest_len = 999999999;
  int shortest_num = -1;

  Node *root = NULL;

  for (int i = 0; i < n; i++) {
    Input input = inputs[i];

    int len = strlen(input.quote);
    if (len > longest_len) {
      longest_len = len;
      longest_num = input.num;
    }

    if (len < shortest_len) {
      shortest_len = len;
      shortest_num = input.num;
    }

    root = ins(root, nodenew(input.num, input.quote));
  }

  printf("before delete:\n");
  preorder(root);
  printf("\n");

  root = del(root, shortest_num);
  root = del(root, longest_num);

  printf("after delete:\n");
  preorder(root);
  printf("\n");
}

void case1() {
  Input inputs[5] = {
      {1, "hello world"},
      {3, "in the first age, in the first battle..."},
      {2, "do you think friendship can last more than one lifetime?"},
      {9, "maybe the real treasure is the friends we made along the way"},
      {4, "mountain is tall, but stagnant"}};
  solve(inputs, 5);
}

int main() {
  case1();
  return 0;
}
