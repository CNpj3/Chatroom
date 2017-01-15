#include <stdio.h>
#include "intersection.h"

int main()
{
    int map[100][100]={0}, result[4]={0};
    for (int i=0;i<100;i++) {
        for (int j=0;j<100;j++) {
            scanf("%d", &map[i][j]);
        }
    }
    intersection(map, result);
    printf("%d %d %d %d\n", result[0], result[1], result[2], result[3]);
    return 0;
}
