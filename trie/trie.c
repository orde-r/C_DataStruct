#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABETS 26

typedef struct trieNode
{
    struct trieNode *children[ALPHABETS];
    int isEnd;
}trieNode;

trieNode *createNode(){
    trieNode *newnode = malloc(sizeof(trieNode));
    newnode->isEnd = 0;
    for (int i = 0; i < ALPHABETS; i++)
    {
        newnode->children[i] = NULL;
    }
    return newnode;    
}

void insertNode(trieNode *root ,const char *word){
    trieNode *current = root;

    for (int i = 0; word[i] != '\0'; i++)
    {
        int index = towlower(word[i]) - 'a';
        if (index >= 0 && index < ALPHABETS)
        {
            if (!current->children[index])
            {
                current->children[index] = createNode();
            }
            current = current->children[index];     
        }
    }
    current->isEnd = 1;
}

int searchNode(trieNode *root, const char* word){
    trieNode *current = root;
    for (int i = 0; word[i] != '\0'; i++)
    {
        int index = tolower(word[i]) - 'a';
        if (!current->children)
        {
            return 0;
        }
        current = current->children[index];
    }
    return (current) ? 1 : 0;
}

void collectWords(trieNode *root, char *prefix, int length, char **words, int *count){
    if (!root) return;
    if (root->isEnd)
    {
        words[*count] = strdup(prefix);
        (*count)++;
    }
    for (int i = 0; i < ALPHABETS; i++)
    {
        if (root->children[i])
        {
            prefix[length] = i + 'a';
            prefix[length + 1] = '\0';
            collectWords(root->children[i], prefix, length+1, words, count);
        }
    }
}

void getStartWith(trieNode *root, const char* prefix){
    trieNode *current = root;
    for (int i = 0; prefix[i] != '\0'; i++)
    {
        int index = tolower(prefix[i]) - 'a';
        if ((index >= 0 && index < ALPHABETS) || !current->children[index])
        {
            printf("There is no words start with \"%s\"\n", prefix);
            return;
        }
        current = current->children[index];
    }
    char **words =  malloc(100 * sizeof(char*)); //Simpan kata kata yang memenuhi
    int count = 0; //Simpan ada berapa kata yang ketemu
    char buffer[100];
    strcpy(buffer, prefix);
    collectWords(current, buffer, strlen(prefix), words, &count);
    if (count == 0)
    {
        printf("There is no words start with \"%s\"\n", prefix);
    }
    else
    {
        printf("Words start with \"%s\":\n", prefix);
        for (int i = 0; i < count; i++)
        {
            printf("%d. %s\n", i+1, words[1]);
            free(words[i]);
        }
    }
    free(words);
}

void getAllWords(trieNode *root){
    trieNode *current = root;
    char **words = malloc(100*sizeof(char*));
    int count = 0;
    char buffer[100];
    buffer[0] = '\0';
    collectWords(root, buffer, 0, words, &count);
    
    if (count == 0)
    {
        printf("No Words Yet!\n");
    }
    else
    {
        printf("Words List:\n");
        for (int i = 0; i < ALPHABETS; i++)
        {
            printf("%d. %s\n", i+1, words[i]);
            free(words[i]);
        }
    }   
    free(words);
}

int main(){

    return 0;
}