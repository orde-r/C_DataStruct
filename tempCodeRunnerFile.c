#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node node;

struct node
{
    node *left;
    node *right;
    int val;
    int height;
};

int shortest[2], longest[2];

int main(){
    node *root = NULL;

    int tc;
    scanf("%d", &tc);

    int num;
    char str[200];
    for (int i = 0; i < tc; i++)
    {
        scanf("%d %[^\n]", &num, str);

        int len = strlen(str);
        if (i == 0)
        {
            shortest[0] = num;
            shortest[1] = len;
            longest[0] = num;
            longest[1] = len;
        }

        if (len > longest[1])
        {
            longest[0] = num;
            longest[1] = len;
        }
        if (len < shortest[1])
        {
            shortest[0] = num;
            shortest[1] = len;
        }  

        insertNode(root, num);
    }
    deleteNode(root, shortest[0]);
    deleteNode(root, longest[0]);

}

