#include <stdio.h>
#include <ctype.h>
#include <string.h>

char *string;

void insert(char *pos, char insertChar)
{
    if (isdigit(pos))
    return;
}
void delete(char *pos)
{
    if (isdigit(pos))
    return;
}
int main()
{
    char instruction[8], pos[16];
    char insertChar;
    while (scanf("%s", instruction)!=EOF) {
        scanf("%s", pos);
        if (strcmp(instruction, "insert")==0) {
            scanf("%c", insertChar);
            insert(pos, insertChar);
        }
        else if (strcmp(instruction, "delete")==0) {
            delete(pos);
        }
    }
    return 0;
}
