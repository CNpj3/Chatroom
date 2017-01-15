#include <stdio.h>
#include <string.h>
#define MAX 10

void isone(int w, int h)
{
	int i, j, mid;
	mid = (h+1) / 2;
	for (j = 0; j < h; j++) {
		if (j == 0 || j == h-1 || j = mid)
			printf("\n");
		else{
			for (i = 0; i < w; i++) {
				if (i == w-2)
					printf("1");
				else 
					printf(" ");
			}
		}
	}
	return;
}



void whichnumber(char inupt[MAX], int w, int h)
{
	int i;
	for (i = 0; i <= strlen(input); i++) {
		switch (input[i]) {
			case '0':
				iszero(w, h);	break;
			case '1':
				isone(w, h);	break;
			case '2':
				istwo(w, h);	break;
			case '3':
				isthree(w, h);	break;
			case '4':
				isfour(w, h);	break;
			case '5':
				isfive(w, h);	break;
			case '6':
				issix(w, h);	break;
			case '7':
				isseven(w, h);	break;
			case '8':
				iseight(w, h);	break;
			case '9':	
				isnine(w, h);	break;
		}

	}
	return;
}

int main()
{
    char input[MAX];
    int w, h;
    scanf("%s%d%d", input, &w, &h);
    whichnumber(input, w, h);
    return 0;
}
