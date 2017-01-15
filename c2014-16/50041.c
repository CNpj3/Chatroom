#include <stdio.h>

int main()
{
    int firstcost[] = {3,2};
    int cost[] = {4,3,3,2};
    int n, prev_t, now_t, prev, now, sum=0;
    scanf("%d%d%d", &n, &prev, &now);
    prev_t = now-prev;
    if (prev_t>0) {
        sum+= prev_t*firstcost[0];
    } else {
        sum+= (-prev_t)*firstcost[1];
    }
    prev = now;

    int i;
    for (i=2;i<n;i++) {
        scanf("%d", &now);
        now_t = now-prev;
        if (now_t>0) {
            if (prev_t>0) {
                sum+= now_t*cost[0];
            }
            else {
                sum+= now_t*cost[1];
            }
        }
        else {
            if (prev_t>0) {
                sum = (-now_t)*cost[2] + sum;
            }
            else {
                sum = (-now_t)*cost[3] + sum;
            }
        }
        prev_t = now_t;
        prev = now;
    }
    printf("%d\n", sum);
    return 0;
}
