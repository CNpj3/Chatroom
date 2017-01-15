#include <stdio.h>

int main()
{
    int a, b, c, d, e, f;
    scanf("%d%d%d", &a, &b, &c);
    
    /* a = d+e+f, b = de+ef+df, c = def */
    /* 1 1 1
       1 1 2
       1 1 3
       1 2 2
       1 2 3
       1 3 3
       2 2 2
       2 2 3
       2 3 3
       3 3 3
    */

    for (d = 1; d < c; d++) {
        for (e = 1; e < c; e++) {
            for (f = 1; f < c; f++){

    return 0;
}
