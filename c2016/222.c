#include<stdio.h>

long long int bookshelf=0;

void print_book()
{
    long long int tmp = bookshelf;
    printf("%lld", tmp>>56);
    tmp = tmp<<8;

    for (int i=1;i<=7;i++) {
        printf(" %lld", tmp>>56);
        tmp = tmp<<8;
    }
    printf("\n");
    return;
}

int main()
{
    long long int X;
    while (scanf("%lld",&X)!=EOF) {
        int inside=0;
        long long int x = X;
        int i;
        for (i=0;i<8;i++) {  //check
            if ((bookshelf & x )==x) {inside = 1; break;}
            else x = x<<8;
        }
        if (inside) {
            i++;
            printf("inside at i=%d\n",i);
            print_book(); 
            if (i==0) {
                bookshelf = bookshelf<<8;
                bookshelf |= X;
                print_book();
                continue;
            }
            else {
                int tmp = 255 >> (8-i)*8;
                tmp &= bookshelf;
                tmp = tmp << 4;
                tmp |= X;
                int tmp2 = 255 << i*8;
                bookshelf &= tmp2;
                bookshelf |= tmp;
                print_book();
            }
        }
        else {
            printf("not inside\n");
            print_book();
            bookshelf = bookshelf<<8;
            bookshelf |= X;
            printf("%lld\n", X);
            print_book();
        }
    }
    //printf("%lld\n", bookshelf);
    print_book();
    return 0;
}
