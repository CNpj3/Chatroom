#include <stdio.h>
int r,c;

int re(int x, int y)
{
    if (x==c-1 && y==r-1) return 1;
    else if (x==c-1 && y!=r-1) return re(x, y+1);
    else if (x!=c-1 && y==r-1) return re(x+1, y);

    return re(x+1, y) + re(x, y+1);
}

int main()
{
    scanf("%d%d",&r,&c);
    printf("%d\n", re(0,0));
    return 0;
}
