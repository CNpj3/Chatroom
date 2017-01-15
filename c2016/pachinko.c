#include<stdio.h>
#define MAX 128
#define LEFT 0
#define RIGHT 1
#define UP 0
#define DOWN 1

int main()
{
    int n, table[MAX][2][2][2];
    scanf("%d", &n);
    int i,j,k;
    int left,right;
    for (i=0;i<n;i++) {
        for (j=0;j<=i;j++) {
            scanf("%d %d", &left, &right);
            table[i][j][LEFT][UP] = left;
            table[i][j][RIGHT][UP] = right;
            table[i][j][LEFT][DOWN] = left+right;
            table[i][j][RIGHT][DOWN] = left+right;
        }
    }

#ifdef DEBUG
    printf("n = %d\n", n);
    for (i=0;i<n;i++) {
        for (j=0;j<=i;j++) {
            for (k=0;k<2;k++) {
                printf("%d/%d ", table[i][j][k][UP], table[i][j][k][DOWN]);
            }
        }
        printf("\n");
    }
#endif
    return 0;
}
