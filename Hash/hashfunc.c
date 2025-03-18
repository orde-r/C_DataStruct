#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define size 9

int hashFunction(const char name[]){
    int key = 0;
    for (int i = 0; i < strlen(name); i++)
    {
        key += name[i];
    }
    return key % size;
}

int main(){
    char name[] = "gusion";
    printf("Hash Value: %d\n",hashFunction(name));
    return 0;
}