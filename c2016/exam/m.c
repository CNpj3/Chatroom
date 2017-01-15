#include "attraction.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX 2147483637
#define MAXM 65536
int N,M;

typedef struct point{
    int x,y;
    struct point* next;
}Point;

void insert(Point* order, int circle), int x, int y
{
    
}
void findOrder(int x, int y, Point* order)
{
    insert(order[find_cycle(x,y)], x,y);

}

int main(int argc, char* argv[])
{
    Point order[MAX];
    int m;
    Attraction *a = (Attraction*)malloc(sizeof(Attraction));
    scanf("%d%d",&N,&M);
    m=M;

    FILE *fp = fopen(argv[1], "rb");
    while (m--){
        fread(a,sizeof(a),1,fp);
        printf("%d %d\n",a->x,a->y);
        findOrder(x,y,order);
    }
    return 0;
}
