#include <stdio.h>
#define MAXN 100

char foodTable[MAXN][64];
char ingreTable[MAXN][64];
int foodIngre[MAXN][10];
int foodIngreNum[MAXN];

int main()
{
    int n,m;
    scanf("%d",&n);
    for (int i=0;i<n;i++) {
        scanf("%s",foodTable[i]);
        scanf("%d",foodIngreNum[i]);

        for (int j=0;j<foodIngreNum[i];j++) {
            foodIngre[i][j]=

    return 0;
}
