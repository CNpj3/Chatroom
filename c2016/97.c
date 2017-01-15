#include <stdio.h>
#include <stdlib.h>
#define x 0
#define y 1
#define capacity 2
#define number 3

int main() 
{
    int n, lot[10][4], m, inx, iny;
    scanf("%d",&n);
    int i,j;
    for(i=0;i<n;i++) {
        scanf("%d%d%d",&lot[i][x],&lot[i][y],&lot[i][capacity]);
        lot[i][number] = 0;
    }
/*    
    for(i=0;i<n;i++) {
        printf("%d %d %d\n",lot[i][x],lot[i][y],lot[i][capacity]);
    }
    */
    scanf("%d",&m);

    for (j=0;j<m;j++) {
        scanf("%d%d",&inx,&iny);
        int min, min_i, distance;
        for (i=0;i<n;i++) {
            if (lot[i][number] >= lot[i][capacity]) {
                continue;
            }
            else {
                min = abs(inx-lot[i][x])+abs(iny-lot[i][y]);
                min_i=i;
                break;
            }
        }
        for (i=min_i+1;i<n;i++) {
   //         printf("lot[%d][number]=%d, lot[%d][capacity]=%d\n", i,lot[i][number],i,lot[i][capacity]);
            if (lot[i][number] >= lot[i][capacity]) {
                //printf("if, number=%d, capacity=%d\n",lot[i][number], lot[i][capacity]);
                continue;
            }
            distance = abs(inx-lot[i][x])+abs(iny-lot[i][y]);
//            printf("i= %d,distance= %d, min= %d\n", i,distance,min);
            if (distance < min) {
                min_i=i;
                min = distance;
            }
        }
        lot[min_i][number]++;
    }
    for(i=0;i<n;i++) {
        printf("%d\n",lot[i][number]);
    }
    return 0;
}

