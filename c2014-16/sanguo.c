#include <stdio.h>


int main()
{
    int s, pos[3][2], one, two, three;
    scanf("%d", &s);

    /* read */    
    int i;
    for (i = 0; i < 3; i++) {
        scanf("%d", &pos[i][0]);
        scanf("%d", &pos[i][1]);
    }

    /* every dot has mininum dis */
    int j, k, dis, min = 2*s*s, minpos[2];
    for (k = 0; k < s; k++) {
        for (j = 0; i < s; j++) {
            minpos[0] = k; minpos[1] = j;
            for (i = 0; i < 3; i++) {
                dis = (k - pos[i][0]) * (k - pos[i][0]) + (j - pos[i][1]) * (j - pos[i][1]);
                if (dis <= min) {
                    if (pos[0]


//    int s, x1, y1, x2, y2, x3, y3, one, two, three;
//    scanf("%d", &s, &x1, &x2, &x3);
    return 0;
}
