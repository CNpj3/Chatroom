#include <stdio.h>

int isWin(int p[4][4])
{
    int correct[4][4] = {1,2,3,4,
                         5,6,7,8,
                         9,10,11,12,
                         13,14,15,0};
    for (int i=0;i<4;i++) {
        for (int j=0;j<4;j++) {
            if (correct[i][j] != p[i][j])
                return 0;
        }
    }
    return 1;
}

void printPuzzle(int p[4][4])
{
    for (int i=0;i<4;i++) {
        printf("%d", p[i][0]);
        for (int j=1;j<4;j++) {
            printf(" %d", p[i][j]);
        }
        printf("\n");
    }
    return;
}

void getValid(int puzzle[4][4], int v[4], int i, int j)
{
    v[0]=0; v[1]=0; v[2]=0; v[3]=0;
    if (i>0) v[0] = puzzle[i-1][j];
    if (j>0) v[1] = puzzle[i][j-1];
    if (i<3) v[2] = puzzle[i+1][j];
    if (j<3) v[3] = puzzle[i][j+1];
    return;
}

int main()
{
    int input, puzzle[4][4] = {0};
    int zerox, zeroy, validMove[4];
    for (int i=0;i<4;i++) {
        for (int j=0;j<4;j++) {
            scanf("%d", &puzzle[i][j]);
            if (puzzle[i][j] == 0) {
                getValid(puzzle, validMove, i, j);
                zerox=i; zeroy=j;
            }
        }
    }
    
    int dirX[4] = {-1, 0, 1, 0};
    int dirY[4] = {0, -1, 0, 1};
    scanf("%d", &input);
    int win=0;
    while (input!=0) {
        int move;
        for (int k=0;k<4;k++) {
            if (input==validMove[k]){
                 move=k; break;
            }
            if (k==3) move=-1;
        }

        if (move == -1) continue;
        else {
            puzzle[zerox][zeroy] = input;
            puzzle[zerox+dirX[move]][zeroy+dirY[move]] = 0;
            zerox += dirX[move];
            zeroy += dirY[move]; 

            getValid(puzzle, validMove, zerox, zeroy);
        //    printf("zerox=%d, zeroy=%d\n", zerox, zeroy);
        //    printf("move=%d\n", move);
//            printPuzzle(puzzle);
//            printf("\n");
        }
        win = isWin(puzzle);
        if (win) {
            break;
        }
        scanf("%d", &input);
    }
    printPuzzle(puzzle);
    if (win) {printf("%d %d\n", win, input);}
    else {printf("%d\n", win);}
    return 0;
}
