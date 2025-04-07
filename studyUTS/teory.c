#include<string.h>
#include<stdio.h>
#include<stdlib.h>

typedef struct Node Node;

struct Node {
	int type;
	char nama[100];
	Node *prev;
	Node *next;	
}*head, *tail;

Node *createnode(int type, char nama[]) {
	Node *newNode = (Node*)malloc(sizeof(Node));
	
	strcpy(newNode -> nama, nama);
	
	newNode -> type = type;
	newNode -> next = NULL;
	newNode -> prev = NULL;
}

int converst(char type[]) {
	if(strcmp(type, "Critical") == 0){ 
		return 4;
	} else if(strcmp(type, "Serious") == 0){ 
		return 3;
	} else if(strcmp(type, "Fair") == 0){ 
		return 2;
	} else if(strcmp(type, "Good") == 0){ 
		return 1;
	} 
}

void insert(char nama[], char type[]) {
	Node *temp = createnode(converst(type), nama);
	
	if(!head) {
		head = tail = temp;
	} else if(temp -> type > head -> type) {
		temp -> next = head;
		head -> prev = temp;
		head = temp;
	} else if(temp -> type < tail -> type) {
		tail -> next = temp;
		temp -> prev = tail;
		tail = temp;
	} else {
		Node *curr = head;
		while(curr -> next && temp -> type <= curr -> next -> type) {
			curr  = curr -> next;
		}
		
		if(curr == NULL) {
			return;
		}
		
		temp->next = curr->next;
		curr->next = temp;
		temp->prev = curr;
	}
}

void pop() {
	if(!head) {
		return;
	} else {
		if(head -> type == 4) {
			printf("%s is in the Emergency Room\n", head -> nama);	
		} else if(head -> type == 3) {
			printf("%s is in the Examination Room\n", head -> nama);	
		} else {
			printf("%s is in the Consultation Room\n", head -> nama);	
		}
		
		if(head -> next == NULL) {
			free(head);
			head = NULL;
		} else {
			Node *temp = head -> next;
			head -> next = NULL;
			free(head);
			head = temp;
			temp -> prev = NULL;	
		}
	}
}

void print() {
	Node *curr = head;
	while(curr) {
		printf("%s ",curr->nama);
		curr = curr->next;
	}
}

int main() {
	int choice;
	scanf("%d", &choice);
	
	for(int i = 0;i < choice;i++) {
		char nama[100], type[100], con[100];
		
		scanf("%s",type);
		
		if(strcmp(type, "ADD") == 0) {
			scanf("%s %s", nama, con);
			insert(nama, con);
		} else if(strcmp(type, "CALL") == 0) {
			pop();
		}
	}
	
	printf("Waiting Room: ");
	print();
}