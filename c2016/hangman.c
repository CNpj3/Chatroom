#include "hangman.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Hangman{
    int life, guess, len;
    char answer[MAXL];
    char status[26];
    // -1: not in answer, 0: in answer, not guessed, 1: in answer, guessed
};

Hangman* newGame(char *answer, int G)
{
    Hangman *hangman = (Hangman*)malloc(sizeof(Hangman));
    hangman->life=G, hangman->guess=0;
    strcpy(hangman->answer, answer);
    hangman->len = strlen(answer);
    for (int i=0;i<26;i++)
        hangman->status[i]=-1;
    for (int i=0;i<hangman->len;i++)
        hangman->status[answer[i]-'a'] =0;
    return hangman;
}
int guess(Hangman* hangman, char ch)
{
    int status = hangman->status[ch-'a'];
    if (status==-1) {
        hangman->guess++; 
        if (hangman->guess == hangman->life) return -1;
        return 0;
    }
    hangman->status[ch-'a']=1;
    return 1;
}
void printStatus(Hangman* hangman)
{
    for (int i=0;i<hangman->len;i++) {
        if (hangman->status[hangman->answer[i]-'a']==1)
            printf("%c",hangman->answer[i]);
        else printf("*");
    }
    printf("\n");
}
int solved(Hangman* hangman)
{
    for (int i=0;i<26;i++)
        if (hangman->status[i]==0) return 0;
    return 1;
}
