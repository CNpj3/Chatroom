#include <stdio.h>

int main()
{
    int n; scanf("%d",&n);
    int cnt=0, preb, m;
    for (int i=0;i<n;i++) {
        scanf("%d", &m);
        if (i==0) preb = (m>>31) & 1;   // first bitm initial
        for (int j=31;j>=0;j--){
            int b = (m>>j) & 1;         // get j-th
            if (b!= preb) {
                printf("\n");
                for (int k=0;k<cnt%40; k++) printf(" ");
            }
            printf("%d", b);
            preb=b, cnt++;
        }
    }
    printf("\n");
    return 0;
}
