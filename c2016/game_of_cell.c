#include <stdio.h>
#include "game_of_cell.h"

void game_of_cell(int grid[50][50],int outcome[50][50],int N)
{
    int boundArray[52][52]={0};
    int change[3][9] = {{0,0,0, 2,0,0, 0,0,0},
                        {1,1,2, 1,1,1, 1,1,1},
                        {0,0,2, 2,1,1, 1,1,1}};
    for (int i=0;i<50;i++) {
        for (int j=0;j<50;j++) {
            boundArray[i+1][j+1]=grid[i][j];
        }
    }
    for (int n=0;n<N;n++) {
        int numAlive[52][52]={0};
        for (int i=1;i<51;i++) {
            for (int j=1;j<51;j++) {
            numAlive[i][j] += (boundArray[i+1][j+1]/2);
            numAlive[i][j] += (boundArray[i+1][j]/2);
            numAlive[i][j] += (boundArray[i+1][j-1]/2);
            numAlive[i][j] += (boundArray[i][j+1]/2);
            numAlive[i][j] += (boundArray[i][j-1]/2);
            numAlive[i][j] += (boundArray[i-1][j+1]/2);
            numAlive[i][j] += (boundArray[i-1][j]/2);
            numAlive[i][j] += (boundArray[i-1][j-1]/2);
            }
        }

        for (int i=1;i<51;i++) {
            for (int j=1;j<51;j++) {
                boundArray[i][j] = change[boundArray[i][j]][numAlive[i][j]];
            }
        }
    }
    for (int i=0;i<50;i++) {
        for (int j=0;j<50;j++) {
            outcome[i][j]=boundArray[i+1][j+1];
        }
    }


    return;
}
