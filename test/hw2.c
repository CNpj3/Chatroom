#include <stdio.h>
#include <stdlib.h>

int main(void)
{
        double coef[10][11],b;
            int a,i,j,h;
                printf("Please input the number of equations(1~10, 0 to exit):");
                    scanf("%d",&a);
                        for(i=0;i<a;i++)
                                {
                                            printf("\nPlease input the coefficients of equation %d:",i+1);
                                                    for(j=0;j<a+1;j++)
                                                                {
                                                                                scanf("%f", &coef[i][j]);
                                                                                        }
                                                                                            }
                                                                                                for(h=0;h<a;h++)
                                                                                                        {
                                                                                                                    for(i=0;i<a;i++)
                                                                                                                                {
                                                                                                                                                if(h!=i)
                                                                                                                                                                {
                                                                                                                                                                                b=coef[i][h]/coef[h][h];
                                                                                                                                                                                            for(j=0;j<=a;j++)
                                                                                                                                                                                                            {
                                                                                                                                                                                                                                coef[i][j]=coef[i][j]-b*coef[h][j];
                                                                                                                                                                                                                                            }
                                                                                                                                                                                                                                                        }
                                                                                                                                                                                                                                                                }
                                                                                                                                                                                                                                                                    }
                                                                                                                                                                                                                                                                        for(i=0;i<a;i++)
                                                                                                                                                                                                                                                                                {
                                                                                                                                                                                                                                                                                            printf("%f\n",coef[i][a-1]/coef[i][i]);
                                                                                                                                                                                                                                                                                                }
                                                                                                                                                                                                                                                                                                    system("pause");
                                                                                                                                                                                                                                                                                                        return 0;
                                                                                                                                                                                                                                                                                                         }
