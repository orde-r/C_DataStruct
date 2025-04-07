#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct Node {
	char nama[100];
	int status;
	Node *next;
	Node *prev;
}*head, *tail;

Node *createNode(const char nama[], int status) {
	Node *newNode = (Node*)malloc(sizeof(Node));
	
	strcpy(newNode -> nama, nama);
	newNode -> status = status;
	newNode -> next = NULL;
	newNode -> prev = NULL;
	
	return newNode;
}

int converstStringToId(char status[]) {
	if(strcmp(status, "VVIP") == 0) {
		return 4;
	} else if(strcmp(status, "VIP") == 0) {
		return 3;
	} else if(strcmp(status, "Member") == 0) {
		return 2;
	} else if(strcmp(status, "Guest") == 0) {
		return 1;
	} else {
		return 0;
	}
}

const char* converstIdToString(int id) {
	if(id == 4) {
		return "VVIP";
	} else if(id == 3) {
		return "VIP";
	} else if(id == 2) {
		return "Member";
	} else if(id == 1) {
		return "Guest";
	}
}

void add_customer(const char nama[], int status) {
	Node *temp = createNode(nama, status);
	
	if(!head) {
		head = tail = temp;
	}else if(head -> next == NULL) {
		if(head -> status >= temp -> status) {
			head -> next = temp;
			temp -> prev = head;
		} else if(head -> status < temp -> status) {
			temp -> next = head;
			head -> prev = temp;
			head = temp;
		}
	} else {
		Node *curr = head;
		while(curr -> next != NULL && temp -> status <= curr -> next -> status) {
			curr = curr->next;
		}
		
		temp -> prev = curr;
		temp -> next = curr -> next;
		curr -> next =temp;
	}
}

void display() {
	Node *curr = head;
	printf("\nWaiting Line: \n");
	if(head == NULL) {
		printf("Queue is empty\n");
	}
	
	int i = 1;
	while (curr != NULL) {
		printf("%d %s\n",i , curr -> nama, curr -> status);
		curr = curr -> next;
		i++;
	}
	printf("\n");
}

void serve_one() {
	if(!head) {
		return;
	} else {
		Node *temp = head -> next;
		printf("Attention! %s is being served at %s table\n",head -> nama, converstIdToString(head->status));
		head -> next = NULL;
		free(head);
		head = temp;
	}
}

void serve_all() {
	if(!head) {
		return;
	} else {
		Node *curr = head;
		while(curr!=NULL){
			serve_one();
			curr = head;
		}
	}
}

int main() {
	int choice;
	do {
		
		system("cls");
		printf("=============\n");
		printf("SUNIB Restaurant Resevertion\n");
		printf("=============\n");
		
		display();
		
		printf("\n1. Add customer to queue\n"); 	
		printf("2. Serve One\n");
		printf("3. Dismiss Queue\n");
		printf("4. Exit\n");
		printf("Input Menu Number: ");
		scanf("%d", &choice);
		getchar();
		
		if(choice == 1) {
			char nama[100], status[100];
			
			scanf("%s %s",status, nama);
			getchar();
			
			add_customer(nama, converstStringToId(status));
			printf("Press enter to continue...");
			getchar();
		} else if(choice == 2) {
			serve_one();
			printf("Press enter to continue...");
			getchar();
		} else if(choice == 3) {
			serve_all();
			printf("Press enter to continue...");
			getchar();
		} else if(choice == 4) {
			printf("End of the day!");
		} else {
			printf("Invalid Input\n");
			printf("Press enter to continue...");
			getchar();
		}
		
	} while (choice != 4);
	
	return 0;
}