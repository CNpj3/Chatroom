#include <stdio.h>
#define MAX 1024

int main()
{
    int m,n,board[MAX][MAX];
    int i,j;
    for (i=0;i<MAX;i++) {
        for (j=0;j<MAX;j++) board[i][j]=0;
    }
    scanf("%d%d", &m,&n);
#ifdef DEBUG
    for (i=0;i<m;i++) {
        for (j=0;j<n;j++) {
            printf("%d",board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
#endif
    int x[2],y[2];
    scanf("%d%d%d%d", &x[0],&y[0],&x[1],&y[1]);
    if (x[0]==x[1]) {
        if (y[0]<y[1]) {
            for (i=y[0];i<=y[1];i++) {
                board[x[0]][i]=1;
            }
        } else {
            for (i=y[1];i<=y[0];i++) {
                board[x[0]][i]=1;
            }
        }
    }
    else {
        if (x[0]<x[1]) {
            for (i=x[0];i<=x[1];i++) {
                board[i][y[0]]=1;
            }
        } else {
            for (i=x[1];i<=x[0];i++) {
                board[i][y[0]]=1;
            }
        }
    }

#ifdef DEBUG
    for (i=0;i<m;i++) {
        for (j=0;j<n;j++) {
            printf("%d",board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
#endif

    int Q,D,k;
    scanf("%d",&Q);
    for (k=0;k<Q;k++) {
        scanf("%d",&D);
        switch(D) {
            case 0:

                break;
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
        }
    }

    return 0;
}
