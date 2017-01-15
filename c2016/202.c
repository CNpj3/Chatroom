#include <stdio.h>

int main()
{
    int a,b,c,d,e,f,g;
    scanf("%d%d%d%d%d%d%d", &a,&b,&c,&d,&e,&f,&g);
    int A, E;
    if (a< 0) {
        A = -((-a)*c+b);
    }else {
        A = a*c+b;
    }
    if (e< 0) {
        E = -((-e)*g+f);
    }else {
        E = a*g+f;
    }

    int outU, outD;
    switch(d) {
        case 0:
        if (c != g) {
            outU = A*g+E*c;
            outD = c*g;
        }
        else {
            outU = A+E;
            outD = c;
        }
        break;
        case 1:
        if (c != g) {
            outU = A*g-E*c;
            outD = c*g;
        }
        else {
            outU = A-E;
            outD = c;
        }
        break;
        case 2:
            outU = A*E;
            outD = c*g;
        break;
        case 3:
            outU = A*g;
            outD = c*E;
        break;
    }
    
    int outF = outU/outD;
    outU %= outD;
    if (outU == 0)  outD = 1;
    printf("%d\n%d\n%d\n", outF, outU, outD);
    return 0;
}
