#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 128

typedef struct node {
  int deadline;
  char name[BUF_SIZE];
  int id;

  struct node *next;
  struct node *prev;
} Node;

int idx = 0;

Node *node_new(const int deadline, const char *name) {
  Node *n = (Node *)calloc(1, sizeof(Node));
  n->deadline = deadline;
  strcpy(n->name, name);
  n->id = idx++;
  return n;
}

Node *enqueue(Node *head, Node *n) {
  if (head == NULL) {
    return n;
  }

  Node *curr = head;
  // first
  if (curr->deadline > n->deadline) {
    n->next = curr;
    curr->prev = n;
    return n;
  }
  curr = curr->next;

  while (curr->next != NULL && curr->next->deadline < n->deadline) {
    curr = curr->next;
  }

  if (curr->next) {
    curr->next->prev = n;
  }
  n->next = curr->next;
  n->prev = curr;
  curr->next = n;
  return head;
}

Node *dequeue(Node *head, const int task_id) {
  char found = 0;
  Node *curr = head;
  while (curr) {
    if (curr->id == task_id) {
      found = 1;
      break;
    }
    curr = curr->next;
  }

  if (!found) {
    printf("Id %d doesn't exist!\n", task_id);
    return head;
  }

  if (curr == head) {
    Node *next = head->next;
    next->prev = NULL;
    free(head);
    return next;
  }

  curr->prev->next = curr->next;
  if (curr->next) {
    curr->next->prev = curr->prev;
  }
  free(curr);
  return head;
}

void print(Node *head) {
  Node *curr = head;
  while (curr) {
    printf("[%d] %s D%d\n", curr->id, curr->name, curr->deadline);
    curr = curr->next;
  }
}

void test() {
  Node *head = NULL;
  head = enqueue(head, node_new(100, "Jeremy"));
  head = enqueue(head, node_new(1, "AAA"));
  head = enqueue(head, node_new(101, "Amogus"));
  head = enqueue(head, node_new(2, "Xd"));
  print(head);
  head = dequeue(head, 6969);
  head = dequeue(head, 1);
  print(head);
}

int main() {
  test();
  return 0;
}
