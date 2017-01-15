#include <stdio.h>

int gcd(int m, int n) {
    while (n!=0) {
        int r = m%n;
        m=n;
        n=r;
    }
    return m;
}
int lcm(int m, int n) {
    return m*n/gcd(m,n);
}
int main()
{
    int in1, in2;
    scanf("%d%d", &in1, &in2);
    int Lcm = lcm(in1, in2);
    while (scanf("%d", &in2)!=EOF) {
        if (Lcm % in2 !=0) {
            Lcm = lcm(Lcm, in2);
        }
    }
    printf("%d\n", Lcm);
    return 0;
}
