#include <stdio.h>
#include <string.h>

#define MAXN 50
#define MAXM 100

char authorTable[MAXM][MAXN];
int authorBookNum[MAXM]={0};
char bookTable[MAXM][MAXN];
int authorN=0, bookN=0;

int authorIsExist(char *author)
{
    if (authorN==0) return -1;
    else {
        for (int i=0;i<authorN;i++) 
            if (strcmp(authorTable[i], author)==0) return i;
        return -1;
    }
}
void createAuthor(char *author)
{
    strcpy(authorTable[authorN], author);
    return;
}
void insertBook(int idx, char *book, int (*inputTable)[MAXM])
{
    strcpy(bookTable[bookN], book);
    inputTable[idx][authorBookNum[idx]]=bookN;
    authorBookNum[idx]++;
    bookN++;
    return;
}
void setIndex(int (*inputTable)[MAXM], char *author, char *book)
{
    int idx = authorIsExist(author);
    if (idx != -1) {
        insertBook(idx, book, inputTable);
    } else {
        createAuthor(author);
        insertBook(authorN, book, inputTable);
        authorN++;
    }
    return;
}

int findAuthor(int (*inputTable)[MAXM], char *book)
{
    for (int i=0;i<authorN;i++) {
        for (int j=0;j<authorBookNum[i];j++) 
            if (strcmp(book, bookTable[inputTable[i][j]])) return i;
    }
    return -1;
}

void setSellNum(int (*inputTable)[MAXM], int *sellNumTable, char *book, int sellNum)
{
    int author = findAuthor(inputTable, book);
    sellNumTable[author] += sellNum;
    return;
}

int isBigger(int aid, int bid) {
    return strcmp(authorTable[aid], authorTable[bid]);
}
int findMostAuthor(int *sellNumTable) {
    int max=sellNumTable[0], maxId=0;
    for (int i=1;i<authorN;i++) {
        if (sellNumTable[i]>max) {
            max = sellNumTable[i];
            maxId = i;
        }
        else if (sellNumTable[i] == max) {
            if (isBigger(i, maxId)) {
                max = sellNumTable[i];
                maxId = i;
            }
        }
    }
    return maxId;
}

int main()
{
    int inputTable[MAXM][MAXM];
    int M; scanf("%d", &M);
    char author[MAXN], book[MAXN];
    int sellNumTable[MAXM]={0};
    int sellNum;
    for (int i=0;i<M;i++) {
        scanf("%s", author);
        scanf("%s", book);
        setIndex(inputTable, author, book);
    }

    for (int i=0;i<authorN;i++) {
        printf("%s\n", authorTable[i]);
        for (int j=0;j<authorBookNum[i]; j++) {
            printf("%s\n", bookTable[inputTable[i][j]]);
        }
    }
    for (int i=0;i<M;i++) {
        scanf("%s", book);
        scanf("%d", &sellNum);
        setSellNum(inputTable, sellNumTable, book, sellNum);
    }
    int mostAuthor = findMostAuthor(sellNumTable);
    printf("%s %d\n", authorTable[mostAuthor], sellNumTable[mostAuthor]);

    return 0;
}
