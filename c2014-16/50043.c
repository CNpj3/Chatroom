#include <stdio.h>
#define X 0
#define Y 1
#define A 0
#define B 1
#define C 2
#define POSITIVE 3

int main()
{
    int input[3][2], line[3][4];
    int i,j;
    for (i=0;i<3;i++) {
        scanf("%d%d", &input[i][X], &input[i][Y]);
    }
#ifdef DEBUG
    for (i=0;i<3;i++) {
        printf("%d %d ", input[i][X], input[i][Y]);
    }
    printf("\n");
#endif
    
    int nline=0, todo, temp;
    for (i=0;i<3;i++) {
        if (i==2) continue;
        for (j=i+1;j<3;j++) {
            line[nline][A] = input[j][Y] - input[i][Y];
            line[nline][B] = input[i][X] - input[j][X];
            line[nline][C] = input[i][Y]*input[j][X] - input[j][Y]*input[i][X];
            
            if (i==0 && j==1) todo=2;
            else if (i==0 && j==2) todo=1;
            else if (i==1 && j==2) todo=0;
            else {todo=-1; printf("i=%d, j=%d, error\n",i,j); return -1;}
        
            temp = input[todo][X]*line[nline][A] + input[todo][Y]*line[nline][B] + line[nline][C];
            if (temp > 0){
                line[nline][POSITIVE] = 1;
            }
            else {
                line[nline][POSITIVE] = 0;
            }
            nline++;
        }
    }

#ifdef DEBUG
    for (i=0;i<3;i++) {
        printf("%d *x+ %d *y+ %d=0, %d\n", line[i][A], line[i][B], line[i][C], line[i][POSITIVE]);
    }
#endif

    
    /* find boundary */
    int maxx=input[0][X], maxy=input[0][Y], minx=input[0][X], miny=input[0][Y];
    for(i=1;i<3;i++) {
        if (input[i][X] > maxx) maxx = input[i][X];
        else if (input[i][X] < minx) minx = input[i][X];
        if (input[i][Y] > maxy) maxy = input[i][Y];
        else if (input[i][Y] < miny) miny = input[i][Y];
    }
#ifdef DEBUG
    printf("boundary: minx=%d, maxx=%d, miny=%d, maxy=%d\n", minx, maxx, miny, maxy);
#endif

    int point=0;
    for (i=minx; i<=maxx;i++) {
        for (j=miny; j<=maxy;j++) {
            for (nline=0; nline<3; nline++) {
                temp = i*line[nline][A] + j*line[nline][B] + line[nline][C];
                if (line[nline][POSITIVE]>0) {
                    if (temp < 0) break;
                } else {
                    if (temp > 0) break;
                }
                if (nline == 2) {
#ifdef DEBUG
                    printf("i=%d, j=%d, is in\n",i,j);
                    point++;
#endif
                }
            }
        }
    }

    printf("%d\n", point);
    
    return 0;
}
