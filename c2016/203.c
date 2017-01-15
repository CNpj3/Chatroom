#include <stdio.h>
int main() 
{
    int n, X, Y, pos[2][2], move[2][2], temp[2];
    scanf("%d%d", &X, &Y);
    for(int i=0;i<2;i++) {
        scanf("%d%d", &pos[i][0], &pos[i][1]);
    }
    for(int i=0;i<2;i++) {
        scanf("%d%d", &move[i][0], &move[i][1]);
    }
    scanf("%d", &n);

#ifdef DEBUG
    printf("ball 1= (%d,%d), ball 2= (%d,%d)\n", pos[0][0], pos[0][1], pos[1][0], pos[1][1]);
#endif

    for (int i=0;i<n;i++) {
        for (int j=0;j<2;j++) {
#ifdef DEBUG
            printf("ball %d= (%d,%d)\n", j+1,pos[j][0], pos[j][1]);
#endif
            if (pos[j][0]+move[j][0] < 1 || pos[j][0]+move[j][0] > X) {
                move[j][0] = -move[j][0];
            }
            if (pos[j][1]+move[j][1] < 1 || pos[j][1]+move[j][1] > Y) {
                move[j][1] = -move[j][1];
            }
            pos[j][0] += move[j][0];
            pos[j][1] += move[j][1];
        }
        if (pos[0][0]==pos[1][0] && pos[0][1]==pos[1][1]) {
            temp[0] = move[0][0];
            temp[1] = move[0][1];
            move[0][0] = move[1][0];
            move[0][1] = move[1][1];
            move[1][0] = temp[0];
            move[1][1] = temp[1];
        }
    }
    printf("%d\n%d\n%d\n%d\n", pos[0][0], pos[0][1], pos[1][0], pos[1][1]);
    return 0;
}
