#include <stdio.h>

int main()
{
    int a,b,c,d,e,f;
    scanf("%d%d%d",&a,&b,&c);

    int i,j,k,c1;
    for(i=1;i<c;i++) {
        if (c%i != 0)   continue;
        else {
            d=i;
            c1=c/i;
            for (j=i;j<c1;j++) {
                if (c1%j != 0)    continue;
                else {
                    e=j;
                    f=c1/j;
                    if ((d+e+f == a) && (d*e+e*f+d*f == b)) {
                        printf("%d %d %d\n", d,e,f);
                        return 0;
                    }
                }
            }
        }
    }
    return 0;
}
