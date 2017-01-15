#include <stdio.h>
#include <string.h>

int min = 100;
int minID[2];
int n;
int len[101];
char _string[101][10];

int dist(char str1[10], char str2[10])
{
    if (strcmp(str1,str2)==0) return 0;
    if (strcmp(str1,"")==0) return strlen(str2);
    if (strcmp(str2,"")==0) return strlen(str1);

    char tmp1[10], tmp2[10];
    memset(tmp1,'\0',sizeof(tmp1));
    memset(tmp2,'\0',sizeof(tmp2));
    strncpy(tmp1,str1,strlen(str1)-1);
    strncpy(tmp2,str2,strlen(str2)-1);

    if (str1[0]==str2[0]) return dist(tmp1,tmp2);
    else return 1+dist(str1, tmp2)+dist(tmp1,str2);

    return 0;
}

int main()
{
    n=1;
    while (scanf("%s",_string[n])!=EOF) n++;
    n--;    // get Number

    for (int i=1;i<=n;i++) {
        for (int j=i+1;j<=n;j++) {
            int d = dist(_string[i],_string[j]);
            if (min<d) {
                min=d;
                minID[0]=i; minID[1]=j;
            }
        }
    }
    printf("%d %d %d\n", d, minID[0], minID[1]);
    return 0;
}
