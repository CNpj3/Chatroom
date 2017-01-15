#include <stdio.h>
#include "evaluate_f.h"

int evaluate_f(int *iptr[], int n, int *index)
{
    int max=0, tmp, maxIndex=0;
    max = 4* (iptr[0][0]) - 6*(iptr[0][1]);
    for (int i=1;i<n;i++){
        tmp = 4* (iptr[i][0]) - 6*(iptr[i][1]);
        if (tmp > max) { max=tmp; maxIndex=i;}
    }

    *index=maxIndex;
    return max;
}
