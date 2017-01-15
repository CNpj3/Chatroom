#include <stdio.h>
#define MAX 9
int N;
int num[MAX];
int choose[MAX] = {0};

void permutation(int now, int line[MAX])
{
    if (now==N) {
        printf("%d",line[0]);
        for (int i=1;i<N;i++) 
            printf(" %d",line[i]);
        printf("\n");
        return;
    }
    for (int i=0;i<N;i++) {
        if (!choose[i]) {
            choose[i]=1;
            line[now]=num[i];
            permutation(now+1,line);
            choose[i]=0;
            // permutation(now,line);
        }
    }
}
void sort()
{
    
    return;
}
int main(){
    scanf("%d",&N);
    for (int i=0;i<N;i++) scanf("%d",&num[i]);
    sort();
    int line[MAX];
    permutation(0,line);
    return 0;
}
