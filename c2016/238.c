#include <stdio.h>

int n, set[16];
int subset(int idx, int sum)
{
    if (sum==0) return 1;
    if (idx==n-1) {
        if (set[idx]==sum) return 1;
        else return 0;
    }
    return subset(idx+1, sum-set[idx]) + subset(idx+1, sum);
}

int main()
{
    scanf("%d", &n);
    for (int i=0;i<n;i++) scanf("%d", &set[i]);

    int input;
    while (scanf("%d",&input)!=EOF) {
        printf("%d\n", subset(0, input));
    }
    return 0;
}
