#include <stdio.h>
#include <string.h>

#define MAX 1024
#define base 4

long long int decimal(char input[MAX])
{
    long long int sum=0;
    int len=strlen(input);
    for (int i=0;i<len;i++)
        sum+= power(base,len-i-1)*atoi(input[i]);
    return sum;
}
int main()
{
    char input[MAX];
    printf("please input your quaternary representation number: (the length should less than 1024)");
    scanf("%s",input);
    printf("\nthe decimal repersentation: %ld\n", decimal(input));
    return 0;
}
