#include <stdio.h>
#include <string.h>

int main()
{
    int n;
    scanf("%d", &n);
    for (int i=0;i<n;i++) {
        char in1[80];
        char in2[80];
        scanf("%s%s", in1, in2);

        int len1=strlen(in1), len2=strlen(in2);
        if (strcmp(in1, in2)==0) printf("yes\n"); 
        else if (len1==len2) {
            char temp[80];
            char tmp;
            strcpy(temp, in1);
            for (int j=0;j<len1-1;j++) {
                tmp = temp[j];
                temp[j] = temp[j+1];
                temp[j+1] = tmp;
                if (strcmp(temp, in2)==0) {
                    printf("yes\n");
                    break;
                }
                strcpy(temp, in1);
                if (j==len1-2) printf("no\n");
            }
        }
        else if (len1==len2-1) {
            char temp[80];
            strcpy(temp, in2);
            for (int i=1;i<=len2;i++) {
                memmove(&temp[i], &temp[i+1], len2-i); 
                if (strcmp(in1, temp)==0) {
                    printf("yes\n");
                    break;
                }
                strcpy(temp, in2);
                if (i==len2) printf("no\n");
            }
        }
        else if (len2==len1-1) {
            char temp[80];
            strcpy(temp, in1);
            for (int i=1;i<=len1;i++) {
                memmove(&temp[i], &temp[i+1], len1-i); 
                if (strcmp(in2, temp)==0) {
                    printf("yes\n");
                    break;
                }
                strcpy(temp, in1);
                if (i==len1) printf("no\n");
            }
        }
        else {
            printf("no\n");
        }
    }
    return 0;
}
