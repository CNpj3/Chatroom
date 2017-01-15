#include <stdio.h>

int main()
{
    int a,b;
    scanf("%d%d\n", &a,&b);
//    printf("%d %d\n", a,b);
    char one,zero;
    scanf("%c %c\n", &one,&zero);
//    printf("char = %c %c\n", one,zero);
    unsigned int num;
//    printf("num= %u %u\n",num1,num2);


    int cnt=1, preb=1;
    while (scanf("%u",&num)!=EOF) {
    // 32+4
    for (int i=31;i>=0;i--){
        if (cnt > a*b) break;
        preb = (num >> i) & 1; // bit
//        printf("%d",preb);
        if (preb==1) printf("%c", one);
        if (preb==0) printf("%c", zero);

        if (cnt%a==0) printf("\n");
        cnt++;
    }
    }
    return 0;
}
