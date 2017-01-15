#include <stdio.h>

#define DEBUG



void get_sum_len(int input[1001], int ml[1001], int ms[1001])
{
    int i, sum = 0, msum = 0;
    for (i = 1; i < input[0]; i++)  sum += input[i];
    for (i = 1; i < ms[0]; i++)  msum += ms[i];
    if (sum > msum)
        ms = input;
    if (input[0] > ml[0])
        ml = input;   
    return;
}

int main()
{
    /* the first one is length */
    int input[1001], ml[1001], ms[1001];
    input[0] = 0; ml[0] = 0; ms[0] = 0;
    int i = 1;
    while (scanf("%d", &input[i]) != EOF) {
        if (input[i] < 0){
            input[0] = i;
            get_sum_len(input, ml, ms);
            i = 1; continue;
        }
        i++;
    }

    /* max length, max sum */
    for (i = 1; i < ml[0]; i++) printf("%d", ml[i]);
    printf("\n");
    for (i = 1; i < ms[0]; i++) printf("%d", ms[i]);
    printf("\n");


    return 0;
}
