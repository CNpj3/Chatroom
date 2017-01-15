#include <stdio.h>
#define PERSONMAX 10
#define MMAX 256
#define NAMEMAX 64
#define X 0
#define Y 1

int main()
{
    int bingo[PERSONMAX][MMAX][MMAX];
    int posTable[PERSONMAX][MMAX*MMAX][2];
    char name[PERSONMAX][NAMEMAX];
    int m, n, k, i, j, input;
    scanf("%d%d", &n, &m);
    for (k=0;k<n;k++) { /* person */
        scanf("%s", name[k]);
#ifdef DEBUG
        printf("name = %s\n", name[k]);
#endif
        
        for (i=0;i<m;i++) {
            for (j=0;j<m;j++) {
                scanf("%d", &input);
                bingo[k][i][j] = input;
                posTable[k][input][X] = i;
                posTable[k][input][Y] = j;
            }
        }

#ifdef DEBUG
        for (i=0;i<m;i++) {
            for (j=0;j<m;j++) {
                printf("%d ", bingo[k][i][j]);
            }
            printf("\n");
        }
#endif
    }
    int index, BINGO=0, hasBingo=0;
#ifdef DEBUG
    printf("start to read\n");
#endif
    while (scanf("%d", &input) != EOF) {
        for (k=0;k<n;k++) { /* persons */
            BINGO = 0;
            i = posTable[k][input][X];
            j = posTable[k][input][Y];
            bingo[k][i][j] = 0;

            /* column */
            for (index=0; index<m; index++) {
                if (bingo[k][i][index] != 0) break;
                if (index == m-1)   BINGO=1;
            }
            if (BINGO ==1) {
                if (hasBingo == 0) {
                    hasBingo=1;
                    printf("%d", input);
                }
                printf(" %s", name[k]);
                continue;
            }
            /* row */
            for (index=0; index<m; index++) {
                if (bingo[k][index][j] != 0) break;
                if (index == m-1) BINGO=1;
            }
            if (BINGO ==1) {
                if (hasBingo == 0) {
                    hasBingo=1;
                    printf("%d", input);
                }
                printf(" %s", name[k]);
                continue;
            }
            /* diagonal */
            if (i==j || i+j == m-1) {
                for (index=0; index<m; index++) {
                    if (bingo[k][index][index] != 0) break;
                    if (index == m-1) BINGO=1;
                }
                if (BINGO ==1) {
                    if (hasBingo == 0) {
                       hasBingo=1;
                       printf("%d", input);
                    }
                    printf(" %s", name[k]);
                    continue;
                }
                for (index=0; index<m; index++) {
                    if (bingo[k][index][m-1-index] != 0) break;
                    if (index == m-1) BINGO=1;
                }
                if (BINGO ==1) {
                    if (hasBingo == 0) {
                        hasBingo=1;
                        printf("%d", input);
                    }
                    printf(" %s", name[k]);
                    continue;
                }
            }
        }
        if (hasBingo == 1) break;
    }
    return 0;
}
