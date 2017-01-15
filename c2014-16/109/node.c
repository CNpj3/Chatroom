#include "node.h"
#include <stdio.h>
#include <stdlib.h>
#define MAX 1000

/* node: left, right, data */
void print_path(int path[MAX], int num)
{
    for (int i=0;i<num;i++) {
        if (i==0) printf("%d",path[i]);
        else printf(" %d",path[i]);
    }
    printf("\n");
}
void find_leaf(struct node *cur, int path[MAX], int num)
{
    path[num++]=cur->data;
    if (cur->left==NULL && cur->right==NULL) {
        print_path(path, num);
        return;
    }
    find_leaf(cur->left, path, num);
    find_leaf(cur->right, path, num);
}
void print_all_paths(struct node *root)
{
    int path[MAX]={0};
    find_leaf(root, path,0);
}
