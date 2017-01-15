#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define S 100

void getAlpha(char *in, char *alpha)
{
    int len=strlen(in);
    for (int i=0;i<len;i++){
        if (isalpha(in[i])) {
            alpha[toupper(in[i]) - 'A']++;
        }
    }
    return;
}

int main()
{
    char in[S];
    char alpha[26]={0};
    scanf("%s", in);
    getAlpha(in, alpha);

    for (int i=0;i<26;i++) printf("%d\n", alpha[i]);
    return 0;
}

