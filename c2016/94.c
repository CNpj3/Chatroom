#include <stdio.h>
#include <string.h>

typedef struct node{
    int value;
    struct node *parnet;
    struct node *leftChild;
    struct node *rightChild;
}Node;

typedef struct tree {
    int height;
    int n;
    Node *root;
}Tree;

void *pop(Node *root, char tmp[4000], int start, int end)
{

}

Tree toTree(char tmp[4000])
{
    Tree tree = {0, 0, NULL};
    int len = strlen(tmp);
    int startTag=0;
    char stack[4000];
    for (int i=0;i<len;i++) {
        if (tmp[i]=='(') startTag=i;
        if (tmp[i]==',') {
            Node *root = (Node*)malloc(sizeof(Node));
        }
        if (tmp[i]==')') pop(root, tmp, startTag, i);
        if 
    }
    return tree;
}

int main()
{
    char tmp[4000];
    scanf("%s", tmp);
    Tree tree = toTree(tmp);
    return 0;
}
