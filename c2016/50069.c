#include "hangman.h"
#include <stdio.h>
#include <string.h>

int main()
{
    int N,times;
    char answer[MAXL], str[MAXGL];
    scanf("%d",&N);

    for (int i=0;i<N;i++) {
        scanf("%s",answer);
        scanf("%d",&times);
        scanf("%s",str);
        
        Hangman *game = newGame(answer, times);
        int len = strlen(str);
        for (int j=0;j<len;j++) {
            int ans = guess(game, str[j]);
            printf("%d ", ans);
            printStatus(game);

            if (solved(game)) {
                printf("You Win\n");
                break;
            }
            if (ans==-1) {
                printf("You Lose\n");
                break;
            }
            if (j==len-1)
                printf("You Quit\n");
        }
    }
    return 0;
}
