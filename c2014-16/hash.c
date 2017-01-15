#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXS 1000
#define MAXN 10000
#define MAXL 100

int S,N,Q; // table size, num fo string, num of queue
char strs[MAXN][MAXL];

int getIndex(char *strs)
{
    int sum=0;
    int len=strlen(strs);
    for (int i=0;i<len;i++) {
        if (isdigit(strs[i]))
            sum+= strs[i] - '0';
        else 
            sum+= strs[i];
    }
    return sum % S;
}

void hash(int (*hashTable)[MAXN], int *hashCnt)
{
    for (int i=0;i<S;i++) hashCnt[i]=0;
    for (int i=0;i<N;i++) {
        int idx = getIndex(strs[i]);
        hashTable[idx][hashCnt[idx]++] = i;
    }
    return;
}

int isExist(char *input, int *hashTable, int Cnt)
{
    for (int i=0;i<Cnt;i++)
        if (strcmp(strs[hashTable[i]], input) == 0) return 1;
    return 0;
}

int searchHash(char *input, int (*hashTable)[MAXN], int *hashCnt) {
    int idx = getIndex(input);
    if (isExist(input, hashTable[idx], hashCnt[idx]))
        return idx;
    else return -1; 
}

int main()
{
    scanf("%d%d%d", &S,&N,&Q);
    for (int i=0;i<N;i++) scanf("%s", strs[i]); 
    
    int hashCnt[MAXS];
    int hashCnt[MAXS];
    hash(hashTable, hashCnt);

    printf("finish hash\n");

    char input[MAXL];
    for (int i=0;i<Q;i++) {
        scanf("%s", input);
        printf("%d\n", searchHash(input, hashTable, hashCnt));
    }
    return 0;
}
