#include <stdio.h>

#include "statement.h"

#define LINE 200

#define STOP 0
#define IF 1
#define GOTO 2
#define PRINT 3
#define ASSIGN 4






int findFirst(char *first)
{
  char *codeString[4] = {"STOP", "IF", "GOTO", "PRINT"};
  for (int i = 0; i < 4; i++)
    if (strcmp(first, codeString[i]) == 0)
      return i;

  return ASSIGN;
}

void processIF(int lineNum, char varName[][NAMELENGTH], int varNum, 
	       int code[], int opd1[], int opd2[], int compopr[], 
	       int gotoLine[])
{
  char gotoStr[NAMELENGTH];
  char opd[NAMELENGTH], opr[NAMELENGTH];

  code[lineNum] = IF;
  scanf("%s", opd);
  opd1[lineNum] = nameToIndex(opd, varName, varNum);
  scanf("%s", opr);
  compopr[lineNum] = oprToComp(opr);
  scanf("%s", opd);
  opd2[lineNum] = nameToIndex(opd, varName, varNum);
  scanf("%s", gotoStr);
  assert(strcmp(gotoStr, "GOTO") == 0);
  scanf("%d", &(gotoLine[lineNum]));
}

void processASSIGN(int lineNum, char *first, char varName[][NAMELENGTH], 
		   int varNum, int code[], int opd1[], int opd2[], 
		   int compopr[], int target[])
{
  char opd[NAMELENGTH], opr[NAMELENGTH];
  code[lineNum] = ASSIGN;
  target[lineNum] = nameToIndex(first, varName, varNum);
  char assignStr[NAMELENGTH];
  scanf("%s", assignStr);
  assert(strcmp(assignStr, "=") == 0);
  scanf("%s", opd);
  opd1[lineNum] = nameToIndex(opd, varName, varNum);
  scanf("%s", opr);
  compopr[lineNum] = oprToComp(opr);
  scanf("%s", opd);
  opd2[lineNum] = nameToIndex(opd, varName, varNum);
}

void processCode(char varName[][NAMELENGTH], int varNum, 
		 int code[], int opd1[], int opd2[], int compopr[], 
		 int gotoLine[], int target[])
{
  char first[NAMELENGTH];
  char opd[NAMELENGTH];
  int lineNum = 1;

  while (scanf("%s", first) != EOF) {
    switch (findFirst(first)) {
    case GOTO:
      code[lineNum] = GOTO;
      scanf("%d", &(gotoLine[lineNum]));
      break;
    case STOP:
      code[lineNum] = STOP;
      break;
    case IF:
      processIF(lineNum, varName, varNum, code, opd1, opd2, compopr, gotoLine);
      break;
    case PRINT:
      code[lineNum] = PRINT;
      scanf("%s", opd);
      target[lineNum] = nameToIndex(opd, varName, varNum);
      break;
    case ASSIGN:
      processASSIGN(lineNum, first, varName, varNum, code, opd1, opd2, 
		    compopr, target);
      break;
    }
    lineNum++;
  }
}


void runCode(char varName[][NAMELENGTH], int varValue[], int varNum, 
	     int code[], int opd1[], int opd2[], int compopr[], 
	     int gotoLine[], int target[])
{
  int line = 1;

  while (code[line] != STOP) {
    switch (code[line]) {
    case IF:
      if (compare(varValue[opd1[line]], varValue[opd2[line]], compopr[line]))
	line = gotoLine[line];
      else
	line++;
      break;
    case GOTO:
      line = gotoLine[line];
      break;
    case ASSIGN:
      varValue[target[line]] = 
	arithemetic(varValue[opd1[line]], varValue[opd2[line]], compopr[line]);
      line++;
      break;
    case PRINT:
      printf("%d\n", varValue[target[line]]);
      line++;
      break;
    default:
      printf("invalid code %d\n", code[line]);
      exit(-1);
    }
  }
}



int main ()
{
	/* get all variables */
  	Variables variables;
  	readAllVariables(&variables);

  	/* process code */
  	Statement statements[LINE];
  	processCode(statements, &variables);

  	/* run code */
  	runCode(statements, &variables);

  	return 0;
}