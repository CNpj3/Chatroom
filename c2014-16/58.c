#include <stdio.h>
#define LEFT 0
#define UP 1
#define RIGHT 2
#define DOWN 3

int N,M;
int map[400][400];

int notDead(int i,int j)
{
    if ((i>0) && (map[i-1][j]==1)) return 1;
    if ((i<N-1) && (map[i+1][j]==1)) return 1;
    if ((j>0) && (map[i][j-1]==1)) return 1;
    if ((j<M-1) && (map[i][j+1]==1)) return 1;
    return 0;
}

int lake(int i, int j)
{
//    printf("(%d,%d)\n", i,j);
    if (i<0 || i==N || j<0 || j==N) return 0;
    if (map[i][j]!=1) return 0;

    map[i][j]=2;
    int road = notDead(i,j);
    
    if (road==0) {
//        printf("Deadlock!\n");
        return 1;
    }
    else {
//        printf("Continue!\n");
        return 1
           + lake(i, j+1) 
           + lake(i, j-1)
           + lake(i-1, j)
           + lake(i+1, j);
    }
    return 0;
}

void print()
{
    for (int i=0;i<N;i++){
        for (int j=0;j<M;j++)
            printf("%d ",map[i][j]);
        printf("\n");
    }
    printf("\n");
    return;
}

int main()
{
    scanf("%d%d",&N,&M);
    for (int i=0;i<N;i++)
        for (int j=0;j<M;j++)
            scanf("%d",&map[i][j]);

    for (int i=0;i<N;i++) {
        for (int j=0;j<M;j++) {
    //        printf("(%d,%d) start!\n",i,j);
            if (map[i][j] != 1) continue;
            else {
//                printf("Lake(%d,%d) Start!\n",i,j);
                int lakeSize = lake(i,j);
//                print();
                if (lakeSize>1) printf("%d\n", lakeSize);
//                printf("lake size = %d\n", lakeSize);
            }
        }
    }
    return 0;
}
