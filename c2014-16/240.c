#include <stdio.h>
#define x 0
#define y 1

int main() 
{
    int n, coor[4][2];
    scanf("%d", &n);
    int i, j;
    for (i=0; i<n;i++) {
        for (j=0;j<4;j++) {
             scanf("%d%d", &coor[j][x], &coor[j][y]);
        }
        int k, l, line[6], nline = 0;
        for (k=0;k<4;k++) {
               if (k==3) break;
               for (l=k+1; l<4;l++) {
                   line[nline] = (coor[k][x] - coor[l][x])*(coor[k][x] - coor[l][x]) + (coor[k][y] - coor[l][y])*(coor[k][y]-coor[l][y]);
                    nline++;
               }
        }

        int tmp;
        for (k=1;k<6;k++){
            for (l=0;l<6-k;l++) {
                if (line[l]<=line[l+1])
                    continue;
                else {
                    tmp = line[l];
                    line[l] = line[l+1];
                    line[l+1] = tmp;
                }
            }
        }

        if (line[0]==line[1] && line[0]==line[2] && line[0]==line[3]) {
            if (line[4]==line[5]) {
                printf("square\n");
                continue;
            }
            else {
                printf("diamond\n");
                continue;
            }
        }
        if (line[2]==line[3] && line[3]==line[4]) {
            if (line[1]==line[2] || line[4]==line[5]) {
                printf("diamond\n");
                continue;
            }
        } 
        
        if (line[4]==line[5]) {
            if (line[1] + line[2] == line[4]) {
                printf("rectangle\n");
                continue;
            }
        }
        printf("other\n");
    }
    return 0;
}
