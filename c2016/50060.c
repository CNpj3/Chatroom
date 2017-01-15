#include <stdio.h>
#define MAX 14
int dist[MAX][MAX];
int went[MAX] = {0};
int N;
int route = 2147483648;

void find(int d, int now, int step)
{
    if (d >= route) return;
    if (step==N){
        d+= dist[now][0];   // go back to 0
        if (d < route) route = d;
        return;
    }
    for (int i=1;i<N;i++) {
        if (!went[i]) {
            went[i]=1;
            find(d+dist[now][i], i, step+1);
            went[i]=0;
        }
    }
}
int main() {
    scanf("%d",&N);
    for (int i=0;i<N;i++)
        for (int j=0;j<N;j++) scanf("%d",&dist[i][j]);
    find(0,0,1);
    printf("%d", route);
    return 0;
}
