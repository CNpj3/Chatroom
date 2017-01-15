#include <stdio.h>

int main()
{
    int input, i = 2, t = 0;
    scanf("%d", &input);

    while (input >= 1) {
        if (input % i == 0) {
            input /= i;
            t++;
        }
        else {
            if (t != 0) {
                printf("%d\n%d\n", i, t);
                if (input == 1)
                    break;
            }
            t = 0;
            i++;
        }
    }

    printf("finished.\n");

    return 0;
}
