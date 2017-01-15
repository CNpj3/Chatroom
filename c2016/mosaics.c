#include <stdio.h>

int main()
{
    int x[3], y[3];
    int minx, maxx, miny, maxy;
    int cx, cy; // left of point
    int n = 0; // number of squares inside
    for (int i=0;i<3;i++) {
        scanf("%d%d", &x[i], &y[i]);
    }
    minx=x[0]; miny=y[0]; maxx=x[0]; maxy=y[0];
    for (int i=0;i<3;i++) {
        if (x[i] < minx)    minx=x[i];
        if (x[i] > maxx)    maxx=x[i];
        if (y[i] < miny)    miny=y[i];
        if (y[i] > maxy)    maxy=y[i];
    }
#ifdef DEBUG
    printf("%d %d %d %d\n", minx, maxx, miny, maxy);
#endif


    for (int i=minx; i<=maxx; i++) {
        for (int j=miny; j<=maxy; j++) {
#ifdef DEBUG
            printf("(%d,%d)\n", i,j);
#endif
            for (int k=0;k<4;k++) {
                if (k==0){ // left bot
                    cx = i;
                    cy =j;
                }
                else if (k==1){ // left top
                    cx = i;
                    cy =j+1;
                }
                else if (k==2){ // right bot
                    cx = i+1;
                    cy =j;
                }
                else if (k==3){ // right topt
                    cx = i+1; cy =j+1;
                }
                int p1 = (x[0]-cx)*(y[1]-cy) - (y[0]-cy)*(x[1]-cx);
                int p2 = (x[1]-cx)*(y[2]-cy) - (y[1]-cy)*(x[2]-cx);
                int p3 = (x[2]-cx)*(y[0]-cy) - (y[2]-cy)*(x[0]-cx);
                
                if (!(p1>=0 && p2>=0 && p3>=0) || (p1<=0 && p2<=0 && p3<=0)) {
                    break;
                }
                if (k==3) {
#ifdef DEBUG
                    printf("(%d,%d) inside\n",i,j);
#endif
                    n++;
                }
            }
        }
    }
    printf("%d\n", n);
    return 0;
}
