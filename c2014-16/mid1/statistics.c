#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//#define DEBUG

int main()
{
    int n, grade[100], m, separator[100], interval[101];
    int sum = 0;
    scanf("%d", &n);
    int i, j, k;
    for (i = 0; i < n; i++) { scanf("%d", &grade[i]); sum += grade[i]; };
    scanf("%d", &m);
    for (i = 0; i < m; i++)    scanf("%d", &separator[i]);
    for (i = 0; i < m+1; i++)   interval[i] = 0;


#ifdef DEBUG
    for (i = 0; i < n; i++)    printf("%d ", grade[i]);
    printf("\n");
    for (i = 0; i < m; i++)    printf("%d ", separator[i]);
    printf("\n");
#endif

    /* interval */
    for (i = 0; i < n; i++) {
        j = 0;
        while (j <= m) {
            if (j == m) {
                interval[j]++;
                break;
            }
            if (grade[i] >= separator[j]) {
                 interval[j]++;
                 break;
            }
            else j++;
        }
    }
    /* the mean, the variance, the standard derivation */
    double mean, sum_var = 0, var, std; 
    mean = (double)sum / (double)n;
    for (i = 0; i < n; i++) {
        sum_var += (grade[i] - mean) * (grade[i] - mean);
    }
    var = sum_var / (double)n;
    std = sqrt(var);

    for (i = 0; i <= m; i++)    printf("%d ", interval[i]);
    printf("\n%f %f %f\n", mean, var, std);
    
    return 0;
}
