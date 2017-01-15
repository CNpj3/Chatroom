#include <stdio.h>
#define intersect 0
#define tjunction 1
#define turn 2
#define dead 3

int main() 
{
    int n,input[102][102],class[4]={0};
    scanf("%d", &n);
    int i,j;
    for (i=0;i<=n+1;i++){
        for (j=0;j<=n+1;j++){
            if (i==0 || j==0 || i==n+1 || j==n+1)
                input[i][j] = -1;
            else    scanf("%d",&input[i][j]);
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

            if (neighbors == 4) class[intersect]++;
            else if (neighbors == 3) class[tjunction]++;
            else if (neighbors == 2) {
                /* should be diagonal*/
                if ((input[i-1][j] == 1 && input[i+1][j] == 1) || (input[i][j-1] == 1 && input[i][j+1] == 1))
                    continue;
                 else class[turn]++;
            }
            else if (neighbors == 1) class[dead]++;
        }
    }
    for (i=0;i<4;i++) {
        printf("%d\n", class[i]);
    }
    return 0;
}
