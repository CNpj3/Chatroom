#include <stdio.h>
#define N 3
#define BLACK 0
#define WHITE 1

int main()
{
    int table[N][N];
    int n, turn=BLACK;
    int k,m;
    for (k=0;k<N;k++) {
        for (m=0;m<N;m++) table[k][m]=-1;
    }
#ifdef DEBUG
    for (k=0;k<N;k++) {
        for (m=0;m<N;m++) {
            printf("%d ", table[k][m]);
        }
        printf("\n");
    }
#endif
    scanf("%d", &n);
    int i, x, y;
    if (n==0) {
        printf("There is a draw.\n");
        return 0;
    }
    for (i=0;i<n;i++) {
#ifdef DEBUG
        printf("i=%d, %d's turn\n", i, turn);
#endif
        scanf("%d%d", &x, &y);
        if ((x<N && y<N) && (table[x][y] == -1)) {
            table[x][y] = turn;
#ifdef DEBUG
            for (k=0;k<N;k++) {
                for (m=0;m<N;m++) {
                    printf("%d ", table[k][m]);
                }
                printf("\n");
            }
#endif
            if (x==y || x+y == N-1) {
                if (table[1][1] != -1) {
                    if (table[0][0]==table[1][1] && table[1][1]==table[2][2]) {
                        if (turn == BLACK) printf("Black wins.\n");
                        else printf("White wins.\n");
                        break;
                    }
                    else if (table[0][2]==table[1][1] && table[1][1]==table[2][0]) {
                        if (turn == BLACK) printf("Black wins.\n");
                        else printf("White wins.\n");
                        break;
                    }
                }
            }
            if (table[0][y]==table[1][y] && table[1][y]==table[2][y]) {
                if (turn == BLACK) printf("Black wins.\n");
                else printf("White wins.\n");
                break;
            }
            else if (table[x][0]==table[x][1] && table[x][1]==table[x][2]) {
                if (turn == BLACK) printf("Black wins.\n");
                else printf("White wins.\n");
                break;
            }
            turn ^= 1;
        }
        if (i==n-1) printf("There is a draw.\n");
    }
    return 0;
}
