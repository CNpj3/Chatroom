#include <stdio.h>
#define X 0
#define Y 1
#define FIRST 0
#define SECOND 1

int main()
{
    int m,n,max,input,rowMax=0, rowSecond=0, pos[2], allMax=0, all[2];
    scanf("%d%d",&m,&n);
    int i,j;
    for (i=1;i<=m;i++) {
        rowMax =0;
        rowSecond =0;
        for (j=1;j<=n;j++) {
            scanf("%d", &input);
            if (input>=rowMax) {
                rowSecond = rowMax;
                rowMax = input;
                pos[SECOND] = pos[FIRST];
                pos[FIRST] = j;
            } else if (input>=rowSecond) {
                rowSecond = input;
                pos[SECOND] = j;
            }
            if (rowMax >= allMax) {
                allMax=rowMax;
                all[X] = i;
                all[Y] = pos[FIRST];
            }
        }
        printf("%d %d\n", pos[FIRST], pos[SECOND]);
    }
    printf("%d %d\n", all[X], all[Y]);

    return 0;
}
