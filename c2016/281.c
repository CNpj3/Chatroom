#include <stdio.h>

int main()
{
    int input;
    while (scanf("%d", &input)!=EOF) {
        int count=0;
        while (input!=0) {
            if (input%2!=0) count++;
            input = input >> 1;
        }
        printf("%d\n", count);
    }
    return 0;
}
