#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct trie{
	char chr;
	int word;
	char desc[100];
	trie *edge[128];
}; 
struct trie *root = NULL;

char word[100];
int count;

struct trie *newNode(char x){
	trie *node = (trie*)malloc(sizeof(trie));
	node->chr = x;
	node->word = 0;
	node->desc[0] = '\0';
	
	for(int i = 0; i<128; i++){
		node->edge[i] = 0;
	}
	
	return node;
}

void insert(trie *curr, char *c, char *desc){
	if(curr->edge[*c] == 0){
		curr->edge[*c] = newNode(*c);
	}
	
	if(*c == 0){
		curr->word = 1;
		strcpy(curr->desc, desc);
	}
	else {
		insert(curr->edge[*c], c+1, desc);
	}
}

int find (struct trie *curr, char *c){
	if(curr->edge[*c] == 0){
		return 0;
	}
	if(*c == 0){
		return 1;
	}
	else{
		return find(curr->edge[*c], c+1);
	}
}

trie *search(trie *curr, char *c){
	if(*c == 0){
		return curr;
	}
	if(curr->edge[*c] == NULL){
		return NULL;
	}
	return search(curr->edge[*c], c+1);
}

void updateDesc(struct trie *curr, char *c, char *desc){
	if(*c == 0){
		strcpy(curr->desc, desc);
		return;
	}
	updateDesc(curr->edge[*c], c+1, desc);
}

void findPrefix(struct trie *curr, int x){
	if(curr->word == 1){
		word[x] = 0;
		count ++;
		printf("%d. %s\n", count, word);
	}
	for(int i = 0; i<120; i++){
		if(curr->edge[i] != 0){
			word[x] = i;
			findPrefix(curr->edge[i], x+1);
		}
	}
}

void menu1(){
	
	char desc[300];
	
	while(true){
		printf("Input a new slang word [Must be more than 1 characters and contains no space]:");
		scanf("%[^\n]", word); getchar();
		
		int len = strlen(word);
		int space = 0;
		
		for(int i=0; i<len; i++){
			if(word[i] == ' '){
				space = 1;
				break;
			}
		}
		
		if(len <=1 || space == 1){
			continue;
		}
		
		break;
	}
	
	while(true){
		printf("Input a new slang word description [Must be more than 2 words]:");
		scanf(" %[^\n]", desc);
		
		int lenDesc = strlen(desc);
		
		int countSpace = 0;
		for(int i=0; i<lenDesc; i++){
			if(desc[i] == ' '){
				countSpace ++;
			}
		}
		
		if(countSpace < 2 ){
			continue;
		}
		
		break;
	}
	
	int sama = find(root, word);
		
	if(sama == 1){
		updateDesc(root, word, desc);
		printf("Successfully updated the slang word.\n");
	}
	else {
		insert(root, word, desc);
		printf("Successfully released new slang word.\n");
	}
	
	printf("Press enter to continue...\n");
	getchar();
}

void menu2(){

	char word[100];
	while(true){
		printf("Input a slang word to be searched [Must be more than 1 characters and contains no space]:\n");
		scanf("%[^\n]", word); getchar();
		
		int len = strlen(word);
		int space = 0;
		
		for(int i=0; i<len; i++){
			if(word[i] == ' '){
				space = 1;
				break;
			}
		}
		
		if(len <=1 || space == 1){
			continue;
		}
		
		break;
	}
	
	trie *result = search(root, word);
	
	if(result != NULL && result->word == 1){
		printf("Slang word : %s\n", word);
		printf("Description : %s\n", result->desc);
	}
	else {
		printf("There is no word \"%s\" in the dictionary.\n", word);
	}
	
	printf("Press enter to continue...");
	getchar();	
}

void menu3(){
	char prefix[100];
	printf("Input a prefix to be searched: ");
	scanf("%s", prefix); getchar();
	
	int isLastIndex = 1;
	trie *curr = root;
	
	int n = strlen(prefix);
	isLastIndex = 1;
	curr = root;
	
	for(int i=0; i<n; i++){
		if(curr->edge[prefix[i]] == NULL){
			isLastIndex = 0;
			break;
		}
		else {
			curr = curr->edge[prefix[i]];
		}
	}
	
	if(!isLastIndex){
		printf("\nThere is no prefix \"%s\" in the dictionary.\n", prefix);
	}
	else {
		printf("Words starts with \"%s\": \n", prefix);
		strcpy(word, prefix);
		count = 0;
		findPrefix(curr, strlen(prefix));
	}
	
	printf("Press enter to continue...");
	getchar();
}

void menu4(){
	if(root == NULL){
		printf("There is no slang word yet in the dictionary.\n");
	}
	else {
		printf("List of all slang words in the dictionary:\n");
		count = 0;
		word[0] = '\0';
		findPrefix(root, 0);	
	}
	
	printf("Press enter to continue...\n");
	getchar();
}

int main(){
	
	root = newNode(0);
	
	int menu;
	while(true){
		printf("Choose: \n");
		printf("1. Release a new slang word\n");
		printf("2. Search a slang word\n");
		printf("3. View all slang words starting with a certain prefix word\n");
		printf("4. View all slang words\n");
		printf("5. Exit\n");
		
		scanf("%d", &menu); getchar();
		
		if(menu == 1){
			menu1();
		}
		else if(menu == 2){
			menu2();
		}
		else if(menu == 3){
			menu3();
		}
		else if(menu == 4){
			menu4();
		}
		else if(menu == 5){
			printf("Thank you... Have a nice day :)\n");
			break;
		}
	}
	
	return 0;
}
