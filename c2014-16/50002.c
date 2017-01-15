#include <stdio.h>

int main()
{
    int n,k,cell[102][102]={0}, alive[102][102]={0};
    scanf("%d%d",&n,&k);
    
    for (int i=1;i<=n;i++){
        for (int j=1;j<=n;j++) {
            scanf("%d", &cell[i][j]);
            alive[i][j] = cell[i][j];
        }
    }

    int change[2][9] = {0,0,0, 1,0,0, 0,0,0,
                        0,0,1, 1,0,0, 0,0,0};

    for (int r=0;r<k;r++) {
        int numAlive[102][102]={0};
        for (int i=1;i<=n;i++){
            for (int j=1;j<=n;j++) {
                numAlive[i][j] += cell[i+1][j+1];
                numAlive[i][j] += cell[i+1][j];
                numAlive[i][j] += cell[i+1][j-1];
                numAlive[i][j] += cell[i][j+1];
                numAlive[i][j] += cell[i][j-1];
                numAlive[i][j] += cell[i-1][j+1];
                numAlive[i][j] += cell[i-1][j];
                numAlive[i][j] += cell[i-1][j-1];
            }
        }
        for (int i=1;i<=n;i++){
            for (int j=1;j<=n;j++) {
                cell[i][j] = change[cell[i][j]][numAlive[i][j]];
                if (cell[i][j] == 1)
                    alive[i][j]++;
            }
        }

    }

    int maxAlive=0, maxx, maxy;
    for (int i=1;i<=n;i++){
        printf("%d", cell[i][1]);
        for (int j=2;j<=n;j++) {
            printf(" %d", cell[i][j]);
            if (alive[i][j] >= maxAlive) {
                maxx=i;
                maxy=j;
                maxAlive = alive[i][j];
            }
        }
        printf("\n");
    }
    printf("%d %d\n", maxx,maxy);
    
    return 0;
}
