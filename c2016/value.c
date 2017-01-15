#include <stdio.h>
#include "value.h"
#define GOLD 0
#define SILVER 1
#define COPPER 2
#define LEAD 3
#define IRON 4
#define TITAN 5

int value(int type, int width, int height, int length)
{
    int v, t;
    int unitPrice[] = {30, 10, 4, 5, 3, 9};

    switch(type) {
        case 79:
            t=GOLD;
            break;
        case 47:
            t=SILVER;
            break;
        case 29:
            t=COPPER;
            break;
        case 82:
            t=LEAD;
            break;
        case 26:
            t=IRON;
            break;
        case 22:
            t=TITAN;
            break;
        default:
            t=-1;
            break;
    }
    if (t==-1) {
//        printf("type = %d\n", t);
        return -1;
    }

    if (width<=0 || height<=0 || length<=0) {
//        printf("(%d,%d,%d), less than zero\n", width, height, length);
        return -2;
    }

    int min = width;
    if (height < min) min = height;
    if (length < min) min = length;
    
    while (!(width%min==0 && height%min==0 && length%min==0)) {
        min--;
        if (min<0) return -3;
    }

//    printf("min = %d\n", min);
    int singlePrice = min*min*min*min*min*min*unitPrice[t];
//    printf("singlePrice = %d\n", singlePrice);
    v = singlePrice * (width/min) * (height/min) * (length/min);
    
    return v;
}
