#include <stdio.h>

int main()
{
    double a,b,c, result, pi=3.1415926;
    scanf("%lf%lf%lf", &a,&b,&c);
    result = 0.75*pi*c*c;
    if ((c==a && c==b) ||(c<a && c<b)) ; 
    else if (c<a && c>b) result+= (c-b)*(c-b)*pi*0.25;
    else if (c<b && c>a) result+= (c-a)*(c-a)*pi*0.25;
    else result+= ((c-b)*(c-b)*pi*0.25+(c-a)*(c-a)*pi*0.25);

    printf("%f\n", result);
    return 0;
}
