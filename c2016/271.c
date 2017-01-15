#include <stdio.h>

int main()
{
    int n,m, a[100], b[100], out[10000];
    int i,j;
    for (i=0;i<10000;i++) out[i]=0;

    scanf("%d", &n);
    for (i=n-1;i>=0;i--) {
        scanf("%d", &a[i]);
    }
    scanf("%d", &m);
    for (j=m-1;j>=0;j--) {
        scanf("%d", &b[j]);
    }
    for (i=0;i<n;i++) {
        for (j=0;j<m;j++) {
            out[i+j] += a[i]*b[j];
        }
    }
    printf("%d", out[m+n-2]);
    for (i=m+n-3;i>=0;i--) {
        printf(" %d", out[i]);
    }
    printf("\n");

    return 0;
}
