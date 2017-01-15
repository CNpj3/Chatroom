#include <stdio.h>

int main()
{
    int n;
    double mar[16][16]={0}, x[16]={0}, y[16]={0};
    scanf("%d", &n);
    for (int i=0;i<n;i++) 
        for (int j=0;j<n;j++) {
            scanf("%lf", &mar[i][j]);
        }
    for (int i=0;i<n;i++) scanf("%lf", &y[i]);

    for (int i=n-1;i>=0;i--) {
        x[i] = y[i];
        for (int j=n-1;j>=i;j--) {
            if (i==j) x[i]=x[i]/mar[i][j];
            else {
                x[i] -= x[j]*mar[i][j];
            }
        }
    }
    for (int i=0;i<n;i++) printf("%lf\n", x[i]);
    return 0;
}
