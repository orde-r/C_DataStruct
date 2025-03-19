#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 128

typedef enum type { VIP, REG } Type;

typedef struct node {
  Type type;
  int order;

  struct node *next;
  struct node *prev;
} Node;

Node *node_new(const Type type, const int order) {
  Node *n = (Node *)calloc(1, sizeof(Node));
  n->type = type;
  n->order = order;
  return n;
}

Node *enqueue_tail(Node *head, Node *n) {
  if (!head) {
    return n;
  }

  Node *curr = head;
  while (curr->next) {
    curr = curr->next;
  }
  curr->next = n;
  n->prev = curr;
  return head;
}

Node *enqueue(Node *head, Node *n) {
  if (!head) {
    return n;
  }

  Node *curr = head;
  // insert first
  if (curr->order > n->order) {
    curr->prev = n;
    n->next = curr;
    return n;
  }
  while (curr->next && curr->next->order < n->order) {
    curr = curr->next;
  }

  if (curr->next) {
    curr->next->prev = n;
  }
  n->next = curr->next; // even if null its safe.
  n->prev = curr;
  curr->next = n;
  return head;
}

Node *delete(Node *head, const int order) {
  char found = 0;
  Node *curr = head;
  while (curr) {
    if (curr->order == order) {
      found = 1;
      break;
    }
    curr = curr->next;
  }

  if (!found) {
    return head;
  }

  // del head
  if (curr == head) {
    Node *next = curr->next;
    next->prev = NULL;
    free(curr);
    return next;
  }

  // del mid-last
  if (curr->next) {
    curr->next->prev = curr->prev;
  }
  curr->prev->next = curr->next;
  free(curr);

  return head;
}

Node *dequeue(Node *head) {
  if (!head) {
    return NULL;
  }
  Node *next = head->next;
  if (next) {
    next->prev = NULL;
  }
  free(head);
  return next;
}

Node *merge_alt(Node **vip, Node **reg) {
  Node *res = NULL;

  while (*vip && *reg) {
    res = enqueue_tail(res, node_new((*vip)->type, (*vip)->order));
    *vip = dequeue(*vip);

    res = enqueue_tail(res, node_new((*reg)->type, (*reg)->order));
    *reg = dequeue(*reg);
  }

  while (*vip) {
    res = enqueue_tail(res, node_new((*vip)->type, (*vip)->order));
    *vip = dequeue(*vip);
  }


  while (*reg) {
    res = enqueue_tail(res, node_new((*reg)->type, (*reg)->order));
    *reg = dequeue(*reg);
  }

  return res;
}

void print(Node *head) {
  Node *curr = head;
  while (curr) {
    printf("%c%d ", curr->type == VIP ? 'V' : 'R', curr->order);
    curr = curr->next;
  }
  printf("\n");
}

void test() {
  Node *vip = NULL;
  Node *reg = NULL;

  vip = enqueue(vip, node_new(VIP, 1));
  vip = enqueue(vip, node_new(VIP, 5));
  vip = enqueue(vip, node_new(VIP, 3));

  reg = enqueue(reg, node_new(REG, 9));
  reg = enqueue(reg, node_new(REG, 8));
  reg = enqueue(reg, node_new(REG, 10));
  reg = enqueue(reg, node_new(REG, 18));

  delete (vip, 5);
  delete (reg, 10);

  print(vip);
  print(reg);

  Node *final = merge_alt(&vip, &reg);

  print(final);
}

int main() {
  test();
  return 0;
}