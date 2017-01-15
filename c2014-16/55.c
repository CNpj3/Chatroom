#include <stdio.h>
#define X 0
#define Y 1
#define E 0
#define N 1

int main ()
{
    int m,n,pos[2][2],forward[2][2],step[2][2]={0},fuel[2],time=0;
    scanf("%d%d",&m,&n);
    int i;
    for (i=0;i<2;i++) {
        scanf("%d%d", &pos[i][X], &pos[i][Y]);
        scanf("%d%d", &forward[i][E], &forward[i][N]);
        if (i==1) step[i][E] = forward[i][E];
        if (i==0) step[i][N] = forward[i][N];
        scanf("%d", &fuel[i]);
    }
    while (1) {
        time++;
        for (i=0;i<2;i++) {
            if (fuel[i]<=0) {
#ifdef DEBUG
                printf("robot %d is at (%d,%d), fuel= %d\n",i,pos[i][X],pos[i][Y],fuel[i]); 
#endif
                continue;
            }
            else {
                if (step[i][E] != 0) {
                    pos[i][X]++;
                    if (pos[i][X] >= m) {
                        pos[i][X] %= m;
                    }
                    fuel[i]--;
#ifdef DEBUG
                    printf("robot %d is at (%d,%d), fuel= %d\n",i,pos[i][X],pos[i][Y],fuel[i]); 
#endif
                    step[i][E]--;
                    if (step[i][E] == 0) step[i][N] = forward[i][N];
                }
                else {
                    pos[i][Y]++;
                    if (pos[i][Y] >= n) {
                        pos[i][Y] %= n;
                    }
                    fuel[i]--;
#ifdef DEBUG
                    printf("robot %d is at (%d,%d), fuel= %d\n",i,pos[i][X],pos[i][Y],fuel[i]); 
#endif
                    step[i][N]--;
                    if (step[i][N] == 0) step[i][E] = forward[i][E];
                }
            }
        }
        if ((pos[0][X]==pos[1][X]) && (pos[0][Y]==pos[1][Y])) {
            printf("robots explode at time %d\n",time);
            break;
        }
        else if (fuel[0]<=0 && fuel[1]<=0) {
            printf("robots will not explode\n");
            break;
        }
    }
    
    return 0;
}
