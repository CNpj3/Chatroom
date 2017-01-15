#include <stdio.h>
#define remain 0
#define sum 1
#define max 2
#define min 3

int main()
{
    int n,m,input[10000],remainder[1000][4]={0};
    scanf("%d%d",&n,&m);
    int i;
    for (i=0;i<m;i++) {
        remainder[i][min] = 10000; 
    }
    for (i=0;i<n;i++) {
        scanf("%d",&input[i]);
        int th=input[i]%m;
        remainder[th][sum] += input[i];
        if (remainder[th][max] < input[i]) {
            remainder[th][max] = input[i];
        }
        if (remainder[th][min] > input[i]) {
            remainder[th][min] = input[i];
        }
    }
    for (i=0;i<m;i++) {
        printf("%d %d %d\n", remainder[i][sum], remainder[i][max], remainder[i][min]);
    }
    return 0;
}
