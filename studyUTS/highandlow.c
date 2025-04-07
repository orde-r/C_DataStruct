#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct Node Node;

struct Node {
	int id;
	int level;
	Node *prev;
	Node *next;
}*head, *tail;


Node *createNode(int id, int level) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	
	newNode -> id = id;
	newNode -> level = level;
	
	newNode -> prev = NULL;
	newNode -> next = NULL;
	
	return newNode;
}

int converst(const char level[]) {
	if(strcmp(level, "HIGH") == 0) {
		return 2;
	} else if(strcmp(level, "LOW") == 0) {
		return 1;
	}
}

const char* converstString(int level) {
	if(level == 2) {
		return "HIGH";
	} else if(level == 1) {
		return "LOW";
	} 
}

void insert(int id, const char level[]) {
	Node *temp = createNode(id, converst(level));
	
	if(!head) {
		head = tail = temp;
	} else if(temp -> level > head -> level) {
		temp -> next = head;
		head -> prev = temp;
		head = temp;
	} else if(temp -> level < head -> level) {
		tail -> next = temp;
		temp -> prev = tail;
		tail = temp;
	} else {
		Node *curr = head;
		while(curr -> next && temp -> level <= curr->next->level) {
			curr = curr -> next;
		}
		
		if(curr == NULL) {
			return;
		} 
		
		temp -> next = curr -> next;
		curr -> next = temp;
		temp -> prev = curr;
	}
}

void print() {
	Node *curr = head;
	int count = 1;
	printf("Task List:\n");
	while(curr) {
		printf("%d  %d  %s\n",count, curr->id, converstString(curr->level));
		curr = curr -> next;
		count++;
	}
	
	printf("\n");
}

void doo() {
	if(!head) {
		return;
	} else {
		if(head -> next == NULL) {
			printf("%d is DONE.\n", head -> id);
			printf("0 tasks remaining....\n");
			free(head);
			head = NULL;
		} else {
			Node *temp = head -> next;
			
			head -> next = NULL;
			temp -> prev = NULL;
			head = temp;
			
			printf("%d is DONE.\n", head -> id);
			
			Node *curr = head;
			int total = 0;
			while(curr) {
				curr = curr -> next;
				total++;
			}
			printf("%d tasks remaining....\n", total);
		}
	}
}

void dooall() {
	Node *curr = head;
	while(curr) {
		doo();
		curr = head;
	}
}

int main() {
	insert(1111, "HIGH");
	insert(2222, "LOW");
	insert(3333, "LOW");
	insert(4444, "HIGH");
	insert(5555, "LOW");
	
	print();
	
	doo();
	doo();
	
	printf("\n");
	
	print();
	
	dooall();
}