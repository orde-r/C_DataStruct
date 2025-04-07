#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// linear probing jadi tidak di linked list
#define SIZE 10

typedef struct node node;

struct node
{
    char *str;
    int value;
    int key;
};

node *Hashtable[SIZE];

unsigned int hashing(const char *str){
	unsigned int key = 0;
	
	while(*str != '\0')
	{
		key += *str;
		*str++;
	}
	return key % SIZE;
}

node *createNode(const char *str, int value){
	node *newnode = (node*)malloc(sizeof(node));
	newnode->value = value;
	newnode->key = hashing(str);
	newnode->str = (char*)malloc(strlen(str) + 1); // +1 buat '\0'
	strcpy(newnode->str, str);

	return newnode;
}



node *insert(const char *str, int value){
	node *newnode = createNode(str, value);
	int key = newnode->key;
	if(!Hashtable[key])
	{
		Hashtable[key] = newnode;
	}
	else{
		while(Hashtable[key])
		{
			key = (key + 1) % SIZE;
		}
		Hashtable[key] = newnode;
	}
} 

void displayTable(){
	int i;
    for (i = 0; i < SIZE; i++)
    {
        printf("%d: ", i);
        if (!Hashtable[i])
        {
            printf("NULL\n");
        } else {
            printf("%s %d\n", Hashtable[i]->str, Hashtable[i]->value);
        }
    }
}

void delete(const char *str){
	int key = hashing(str);
	int i;
	for(i = 0; i < SIZE; i++){
		int index = (key + i) % SIZE;
		if(Hashtable[index] && strcmp(Hashtable[index]->str, str) == 0)
		{
			node *temp = Hashtable[index];
			Hashtable[index] = NULL;
			free(temp->str);
			free(str);
			return;
		}	
	}
}

int main(){
	insert("AndrianAsu",6969);
    insert("Bndy",11);
    insert("Candy",21);
    insert("Dandy",31);
    insert("Endy",41);
    insert("Fandy",51);
    insert("JeremyNigga",69);
    
    displayTable();
    printf("\n\n");
    
    delete("AndrianAsus");
    displayTable();
}
