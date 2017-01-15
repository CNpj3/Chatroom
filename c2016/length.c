#include <stdio.h>
#include "length.h"

void init(int length[3]) {
    for (int i=0;i<3;i++) length[i]=0;
    return;
}
void add(int length[3], int i) {
    length[2]+=i;
    if (length[2] > 12) {
        length[1] += (length[2]/12);
        length[2]%=12;
    }
    if (length[1] < 3) {
        length[0] += (length[1]/3);
        length[1]%=3;
    }
    return;
}
void sum(int lengtha[3], int lengthb[3], int lengthc[3]) {
    for (int i=0;i<3;i++) lengthc[i]=lengtha[i]+lengthb[i];
    if (lengthc[2] > 12) {
        lengthc[1] += (lengthc[2]/12);
        lengthc[2] %= 12;
    }
    if (lengthc[1] > 3) {
        lengthc[0] += (lengthc[1]/3);
        lengthc[1] %= 3;
    }
}
void diff(int lengtha[3], int lengthb[3], int lengthc[3]) {
    int tempa=0, tempb=0, tempc=0;
    tempa += lengtha[0]*3*12 + lengtha[1]*12 + lengtha[2];
    tempb += lengthb[0]*3*12 + lengthb[1]*12 + lengthb[2];
    tempc = tempa-tempb;
    lengthc[2] = tempc;

    lengthc[0] = lengthc[2]/36;
    lengthc[2] %= 36;
    lengthc[1] = lengthc[1]/12;
    lengthc[2] %= 12;
/*
    if (lengthc[2] > 12) {
        lengthc[1] += (lengthc[2]/12);
        lengthc[2] %= 12;
    }
    if (lengthc[1] > 3) {
        lengthc[0] += (lengthc[1]/3);
        lengthc[1] %= 3;
    }
*/
}
