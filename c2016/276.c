#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define PASS 1

/* of and the at */
int check(char input[128])
{
    if (strcmp(input, "of")==0) return 0;
    else if (strcmp(input, "of.")==0) return 0;
    else if (strcmp(input, "and")==0) return 0;
    else if (strcmp(input, "and.")==0) return 0;
    else if (strcmp(input, "the")==0) return 0;
    else if (strcmp(input, "the.")==0) return 0;
    else if (strcmp(input, "at")==0) return 0;
    else if (strcmp(input, "at.")==0) return 0;
    else return 1;
}
void abbre(char input[128]) 
{
    int len = strlen(input);
    if (check(input) == PASS) {
        printf("%c", toupper(input[0]));
    }
    if (strcmp(&input[len-1], ".")==0) printf("\n");
    return;
}

int main()
{
    char input[128];
    while (scanf("%s", input) != EOF) {
#ifdef DEBUG
        printf("input=%s\n", input);
#endif
        abbre(input);
    }
    return 0;
}
