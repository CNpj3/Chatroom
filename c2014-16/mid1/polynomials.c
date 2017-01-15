#include <stdio.h>

int main()
{
    int a[100], b[100], m, n;
    scanf("%d", &m);
    int i, j, k;
    for (i = m-1; i >= 0; i--) {
        scanf("%d", &a[i]);
    }
    scanf("%d", &n);
    for (i = n-1; i >= 0; i--) {
        scanf("%d", &b[i]);
    }
 
    int coff = 0;
    for (k = m+n-2; k >= 0; k--) {
        for (i = m-1; i >= 0; i--) {
            for (j = n-1; j >= 0; j--) {
                if (i + j == k)
                    coff += (a[i] *b[j]);
            }
        }
        printf("%d ", coff);
        coff = 0;
    }
    printf("\n");
    
    return 0;
}
