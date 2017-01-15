/* the Knapsack */
#include <stdio.h>
#define MAX 20
int N;
int W;
int price[MAX];
int weight[MAX];
int priceMax = 0;

void knapsack(int pr, int we, int now)
{
    if (we > W) return;
    if (now==N) {
        if (pr > priceMax) priceMax=pr;
        return;
    }
    knapsack(pr+price[now], we+weight[now], now+1);
    knapsack(pr, we, now+1);
}

int main()
{
    scanf("%d%d",&N,&W);
    for (int i=0;i<N;i++) scanf("%d%d",&weight[i],&price[i]);
    knapsack(0, 0, 1);
    knapsack(price[0], weight[0], 1);
    printf("%d\n", priceMax);
    return 0;
}
