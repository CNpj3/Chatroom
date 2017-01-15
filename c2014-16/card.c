#include <stdio.h>
#include "card.h"

void shuffle(int *deck[])
{
    int *tmp[10000];
    int len = sizeof(*deck)/sizeof(deck[1]);
    printf("len=%d\n", len);
    for (int i=0;i<len;i++) tmp[i] = deck[i];
    int half = len/2;
    if (len%2) half+=1;
    for (int i=0;i<=half;i++) {
        deck[i] = tmp[2*i];
    }
    for (int i=half;i<len;i++) {
        deck[i] = tmp[(i-half)*2+1];
    }
    return;
}
void print(int *deck[])
{
    int len = sizeof(*deck)/sizeof(*deck[0]);
    printf("%d", *deck[0]);
    for (int i=1;i<len;i++) {
        printf(" %d", *deck[i]);
    }
    printf("\n");
    return;
}
