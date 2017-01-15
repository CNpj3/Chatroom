#include <stdio.h>

int main()
{
    int n; scanf("%d",&n);
    int in;
    int preb, cnt=1;
    for (int i=0;i<n;i++) {
        scanf("%d",&in);
        if (i==0) preb=(in>>31)&1;
        for (int j=31;j>=0;j--) {
            int b = (in>>j) & 1;
            if (b!=preb) {
                printf("\n");
                for (int k=0;k<(cnt%40);k++) printf(" ");
                preb=b;
            }
            printf("%d",b);
            cnt++;
        }
    }
    return 0;
}
