#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXN 50
#define MAXL 20
#define K 3     // nember of groups

int N,L,R;
char strs[MAXN][MAXL+5];

int dist(char *str1, char *str2) {
    int s=0;
    for (int i=0;i<L;i++)
        s+=abs(str1[i]-str2[i]);
    return s;
}

int isSmaller(char *str1, char *str2) {
    return strcmp(str1, str2) < 0;
}

int isCloser(char *curStr, char *oriStr, char *newStr, int oriDist) {
    int newDist = dist(curStr, newStr);
    return newDist != oriDist ? newDist < oriDist : isSmaller(newStr, oriStr);
}

int pickClosest(char *str, int *candidateIds, int numCandidate) {
    int minDist = dist(str, strs[candidateIds[0]]), minId=0;
    for (int i=1;i<numCandidate; i++) {
        char *candidateStr = strs[candidateIds[i]];
        if (isCloser(str, strs[candidateIds[minId]], candidateStr, minDist))
            minDist=dist(str, candidateStr), minId=i;
    }
    return minId;
}

int assignNewLeader(int *memberIds, int memberCnt)
{
    int sum[MAXL+5]={0};
    char meanStr[MAXL+5] = {0};

    for (int i=0;i<L;i++) {
        for (int j=0;j<memberCnt;j++)
            sun[i]+=strs[memberIds[j]][i];
        meanStr[i] = sum[i]/memberCnt;
    }
    return memberIds[pickClosest(meamStr, memberIds, memberCnt)];
}

void sort(int *idx, int cnt){
    int tmp;
    for (int i=0;i<cnt;i++){
        for (int j=i+1;j<cnt;j++){
            if (isSmaller(strs[idx[j]], strs[idx[i]]))
                tmp = idx[i], idx[i] = idx[j], idx[j] = tmp;
        }
    }
    return;
}

void kmeans(int *leaderIds, int (*memberIds)[MAXN], int *memberCnt)
{
    // first time
    for (int i=0;i<K;i++) leaderIds[i]=i;

    for (int r=0;r<R;r++) {
        for (int i=0;i<K;i++) memberCnt[i]=0;
        for (int i=0;i<N;i++) {
            int gid = pickClosest(strs[i], leaderIds, K);
            memberIds[gid][memberCnt[gid]++]=i;
        }
        for (int i=0;i<K;i++)
            leaderIds[i] = assignNewLeader(memberIds[i], memberCnt[i]);
    return;
}

int main()
{
    scanf("%d%d%d", &N,&L,&R);
    for (int i=0;i<N;i++) scanf("%s", strs[i]);

    int leaderIds[K], memberIds[K][MAXN], memberCnt[K];
    kmeans(leaderIds, memberIds, memberCnt);
    sort(leaderIds, K);

    for (int i=0;i<K;i++) printf("%s\n", strs[leaderIds[i]]);
    return 0;
}
