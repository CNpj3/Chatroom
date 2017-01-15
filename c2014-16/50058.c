#include <stdio.h>
#include <string.h>

int N, cost[22], len[26], min=2147483647;
char _string[22][52];

void dfs(int idx, int _cost, int appear[128], int t)
{
    if (_cost > min) return;
    if (idx == N) { // run last
        int valid = 1;
        for (int i='a'; i<='z' && valid; i++) {
            valid &= (appear[i]==1); // check if there contains all char
        }
        if (valid && (_cost < min)) {
            min = _cost;
        }
        return;
    }

    int tmp[128];
    for (int i='a'; i<'z';i++) tmp[i] = appear[i];
    dfs(idx+1, _cost, tmp, t+1);                // not include
    for (int i=0;i<len[idx]; i++)   appear[_string[idx][i]] = 1;
    dfs(idx+1, _cost+cost[idx], appear, t+1);   // include
    return;
}

int main()
{
    scanf("%d",&N);
    for (int i=0;i<N;i++) {
        scanf("%s %d", _string[i], &cost[i]);
        len[i] = strlen(_string[i]);
    }

    int appear[128];
    dfs(0,0,appear,0); // contain 0 or not ?
    printf("%d\n",min);
    return 0;
}
