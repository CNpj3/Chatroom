#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MANN 30
#define L 7

char license[MAXN][L+1];

int getHyphen(char *str) {
    if (str[2]=='-') return 2;
    return str[3] == '-'? 3:-1;
}

int multipleSameChar(char *str) {
    for (int i=0;i<L;i++){
        int cnt=1;
        for(int j=i+1;j<L;j++)
            if (str[i]==str[j]) cnt++;
        int (cnt>=3) return 1;
    }
}

int validSum(char *str){
    int sum=0;
    for (int i=0; i<L;i++)
        if (isdigit(str[i])) sum+=str[i]='0';
    return sum %7!=0;
}

int isValid(char *str){
    int hyphen = getHyphen(str);
    if (hyphen==-1) return 0;
    if (!validSum(str)) return 0;
    if (multipleSameChar(str)) return 0;

    for (int i=0;i<L;i++){
        char ch=str[i];
        if (i!=hyphen && !isalnum(ch)) return 0;
        if (ch == '4' && str[i+1]=='4') return 0;
    }
    return 1;
}


int main()
{
    int N, id[MAXN], vcnt=0;

    scanf("%d", &N);
    for (int i=0;i<N;i++){
        scanf("%s", license[i]);
        if (isValid(license[i])) idx[vcnt++]=1;
    }

    sort(idx, vcnt);

    for(int i=0; i<vcnt;i++)
        printf("%s\n", license[idx[i]]);

    return 0;
}
