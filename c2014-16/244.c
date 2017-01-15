#include<stdio.h>

int main()
{
    int special[3], first[3], input, sum=0;
    int i;
    for(i=0;i<3;i++) {
        scanf("%d", &special[i]);
    }
    for(i=0;i<3;i++) {
        scanf("%d", &first[i]);
    }
    int rank=8;
    int money[]={0,2000000,200000,40000,10000,4000,1000,200,0};
    while (scanf("%d", &input) != EOF) {
        for (i=0;i<3;i++) {
            if (input == special[i]) rank=1;
            else if (input == first[i]) {
                if (rank>2) rank=2;
            }
            else if ((input-first[i]) % 10000000==0 ||(first[i]-input)%10000000==0) {
                if (rank>3) rank=3;
            }
            else if ((input-first[i]) % 1000000==0 || (first[i]-input)%1000000==0) {
                if (rank>4) rank=4;
            }
            else if ((input-first[i]) % 100000==0 || (first[i]-input)%100000==0) {
                if (rank>5) rank=5;
            }
            else if ((input-first[i]) % 10000==0 || (first[i]-input)%10000==0) {
                if (rank>6) rank=6;
            }
            else if ((input-first[i]) % 1000==0 || (first[i]-input)%1000==0) {
                if (rank>7) rank=7;
            }
        }
//        printf("input= %d, sum= %d\n", input,sum);
        sum+=money[rank];
        rank=8;
    }
    printf("%d\n", sum);
    return 0;
}
