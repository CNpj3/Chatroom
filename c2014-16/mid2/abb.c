#include <stdio.h>
#include <string.h>
#include <ctype.h> //

#define MAX 128

int main()
{
    char input[MAX];
    /* of and the at*/
    while (scanf("%s", input) != EOF) {
        if (strcmp(input, "of") == 0 ||
            strcmp(input, "and") == 0 ||
            strcmp(input, "the") == 0 ||
            strcmp(input, "at") == 0)
            continue; 
        else
            printf("%c", input[0]-32);    
        if (input[strlen(input) - 1] == '.')
            printf("\n");  
    }        
    return 0;
}
