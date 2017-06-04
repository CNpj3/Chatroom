#include <stdio.h>
#include <string.h>

#define PATH_MAX 1000

int main()
{
	char path[] = "hard1";
	char ins[3 * PATH_MAX];
	strcpy(ins, "find ");
	strcat(ins, ".");
	strcat(ins, " -samefile ");
	strcat(ins, path);

	char newline[256];
	FILE* fp = popen(ins, "r");
	while ((fgets(newline, 256, fp)) != NULL) {
		printf("We've got a newline %s", newline);
	}
	pclose(fp);
	return 0;
}

