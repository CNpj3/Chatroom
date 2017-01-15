#include <stdio.h>
#include <string.h>

#define MAX 10
//#define DEBUG 0

void iszero(int w, int h, int i)
{
	int j, mid;
	mid = (h-1) / 2;
	if (i == 0 || i == h-1) {
		for (j = 0; j < w; j++)	{
			if (j == 0 || j >= w-2)
				printf(" ");
			else
				printf("0");
		}
	}
	else if (i == mid) {
		for (j = 0; j < w; j++)	printf(" ");
	}
	else {
		for (j = 0; j < w; j++) {
			if (j == 0 || j == w-2)	printf("0");
			else 	printf(" ");
		}
	}
	return;
}
void isone(int w, int h, int i)
{
#ifdef DEBUG
	printf("in isone\n");
#endif	
	int j, mid;
	mid = (h-1) / 2;
	if (i == 0 || i == h-1 || i == mid)	{
		for (j = 0; j < w; j++)	printf(" ");
	}
	else {
		for (j = 0; j < w; j++) {
			if (j == w-2)	printf("1");
			else 	printf(" ");
		}
	}
	return;
}
void istwo(int w, int h, int i)
{
	int j, mid;
	mid = (h-1) / 2;
	if (i == 0 || i == h-1 || i == mid)	{
		for (j = 0; j < w; j++)	{
			if (j == 0 || j >= w-2)
				printf(" ");
			else
				printf("2");
		}
	}
	else if (i < mid) {
		for (j = 0; j < w; j++) {
			if (j == w-2)	printf("2");
			else 	printf(" ");
		}
	}
	else {
		for (j = 0; j < w; j++) {
			if (j == 0)	printf("2");
			else 	printf(" ");
		}
	}
	return;
}
void isthree(int w, int h, int i)
{
	int j, mid;
	mid = (h-1) / 2;
	if (i == 0 || i == h-1 || i == mid)	{
		for (j = 0; j < w; j++)	{
			if (j == 0 || j >= w-2)
				printf(" ");
			else
				printf("3");
		}
	}
	else {
		for (j = 0; j < w; j++) {
			if (j == w-2)	printf("3");
			else 	printf(" ");
		}
	}
	return;
}
void isfour(int w, int h, int i)
{
	int j, mid;
	mid = (h-1) / 2;
	if (i == 0 || i == h-1) {
		for (j = 0; j < w; j++)	printf(" ");
	} 
	else if (i == mid)	{
		for (j = 0; j < w; j++)	{
			if (j == 0 || j >= w-2)
				printf(" ");
			else
				printf("4");
		}
	}
	else if (i < mid) {
		for (j = 0; j < w; j++) {
			if (j == 0 || j == w-2)	printf("4");
			else 	printf(" ");
		}
	}
	else {
		for (j = 0; j < w; j++) {
			if (j == w-2)	printf("4");
			else 	printf(" ");
		}
	}
	return;
}
void isfive(int w, int h, int i)
{
	int j, mid;
	mid = (h-1) / 2;
	if (i == 0 || i == h-1 || i == mid)	{
		for (j = 0; j < w; j++)	{
			if (j == 0 || j >= w-2)
				printf(" ");
			else
				printf("5");
		}
	}
	else if (i > mid) {
		for (j = 0; j < w; j++) {
			if (j == w-2)	printf("5");
			else 	printf(" ");
		}
	}
	else {
		for (j = 0; j < w; j++) {
			if (j == 0)	printf("5");
			else 	printf(" ");
		}
	}
	return;
}
void issix(int w, int h, int i)
{
	int j, mid;
	mid = (h-1) / 2;
	if (i == 0 || i == h-1 || i == mid)	{
		for (j = 0; j < w; j++)	{
			if (j == 0 || j >= w-2)
				printf(" ");
			else
				printf("6");
		}
	}
	else if (i > mid) {
		for (j = 0; j < w; j++) {
			if (j == 0 || j == w-2)	printf("6");
			else 	printf(" ");
		}
	}
	else {
		for (j = 0; j < w; j++) {
			if (j == 0)	printf("6");
			else 	printf(" ");
		}
	}
	return;
}
void isseven(int w, int h, int i)
{
	int j, mid;
	mid = (h-1) / 2;
	if (i == 0)	{
		for (j = 0; j < w; j++)	{
			if (j == 0 || j >= w-2)
				printf(" ");
			else
				printf("7");
		}
	}
	else if (i == h-1 || i == mid) {
		for (j = 0; j < w; j++)	printf(" ");
	}
	else if (i > mid) {
		for (j = 0; j < w; j++) {
			if (j == w-2)	printf("7");
			else 	printf(" ");
		}
	}
	else {
		for (j = 0; j < w; j++) {
			if (j == 0 || j == w-2)	printf("7");
			else 	printf(" ");
		}
	}
	return;
}
void iseight(int w, int h, int i)
{
	int j, mid;
	mid = (h-1) / 2;
	if (i == 0 || i == h-1 || i == mid)	{
		for (j = 0; j < w; j++)	{
			if (j == 0 || j >= w-2)
				printf(" ");
			else
				printf("8");
		}
	}
	else {
		for (j = 0; j < w; j++) {
			if (j == 0 || j == w-2)	printf("8");
			else 	printf(" ");
		}
	}
	return;
}
void isnine(int w, int h, int i)
{
	int j, mid;
	mid = (h-1) / 2;
	if (i == 0 || i == mid)	{
		for (j = 0; j < w; j++)	{
			if (j == 0 || j >= w-2)
				printf(" ");
			else
				printf("9");
		}
	}
	else if (i == h-1) {
		for (j = 0; j < w; j++)	printf(" ");
	}
	else if (i > mid) {
		for (j = 0; j < w; j++) {
			if (j == w-2)	printf("9");
			else 	printf(" ");
		}
	}
	else {
		for (j = 0; j < w; j++) {
			if (j == 0 || j == w-2)	printf("9");
			else 	printf(" ");
		}
	}
	return;
}
void whichnumber(int number, int w, int h, int i)
{
#ifdef DEBUG
	printf("in whichnumber\n");
#endif

	switch (number) {
		case 0:
			iszero(w, h, i);	break;
		case 1:
			isone(w, h, i);	break;
		case 2:
			istwo(w, h, i);	break;
		case 3:
			isthree(w, h, i);	break;
		case 4:
			isfour(w, h, i);	break;
		case 5:
			isfive(w, h, i);	break;
		case 6:
			issix(w, h, i);	break;
		case 7:
			isseven(w, h, i);	break;
		case 8:
			iseight(w, h, i);	break;
		case 9:	
			isnine(w, h, i);	break;
	}
	return;
}

void dig(int input[MAX], int w, int h, int len)
{
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < len; j++) {

#ifdef DEBUG
			printf("the first number is %d\n", input[j]);
#endif			
			whichnumber(input[j], w, h, i);
		}
		printf("\n");
	}
	return;
}

int main()
{
#ifdef DEBUG
	printf("start\n");
#endif 

	char in[MAX];
	int input[MAX], w, h, len = 0;
	scanf("%s", in);

#ifdef DEBUG
	printf("%s\n", in);
#endif

	for (int i = 0; i < strlen(in); i++) {
		len++;

#ifdef DEBUG
		printf("len = %d\n", len);
#endif
		input[i] = in[i] - 48;
	}
	scanf("%d%d", &w, &h);
	printf(">>>\n");

	dig(input, w, h, len);
	printf("\n");
	return 0;
}