#include <stdio.h>
#include "intersection.h"

#define intersect 0
#define tjunction 1
#define turn 2
#define dead 3

void intersection(int map[100][100], int result[4]) 
{
    int n=100;
    int input[102][102];
    int i,j;
    for (i=0;i<=n+1;i++){
        for (j=0;j<=n+1;j++){
            if (i==0 || j==0 || i==n+1 || j==n+1)
                input[i][j] = -1;
            else
                input[i][j] = map[i-1][j-1];
        }
    }
    int neighbors;
    for (i=1;i<=n;i++){
        for (j=1;j<=n;j++){
            if (input[i][j] != 1) continue;
            neighbors=0;
            if (input[i-1][j] == 1) neighbors++;
            if (input[i][j+1] == 1) neighbors++;
            if (input[i+1][j] == 1) neighbors++;
            if (input[i][j-1] == 1) neighbors++;

#ifdef DEBUG
            printf("(%d,%d) = %d, neighbors = %d\n", i,j,input[i][j], neighbors);
#endif

            if (neighbors == 4) result[intersect]++;
            else if (neighbors == 3) result[tjunction]++;
            else if (neighbors == 2) {
                /* should be diagonal*/
                if ((input[i-1][j] == 1 && input[i+1][j] == 1) || (input[i][j-1] == 1 && input[i][j+1] == 1))
                    continue;
                 else result[turn]++;
            }
            else if (neighbors == 1) result[dead]++;
        }
    }
    return;
}
