#include <stdio.h>

int main()
{
    int maxx,maxy,minx,miny,x,y;
    scanf("%d%d", &maxx, &maxy);
    minx = maxx;
    miny = maxy;

    while (scanf("%d%d",&x,&y)!=EOF) {
        if (x>maxx) maxx= x;
        if (y>maxy) maxy= y;
        if (x<minx) minx= x;
        if (y<miny) miny= y;
    }
    printf("%d\n", (maxx-minx)*(maxy-miny));
    return 0;
}
