#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

#include "statement.h"


int findFirst(char *first)
{
  char *codeString[4] = {"STOP", "IF", "GOTO", "PRINT"};
  for (int i = 0; i < 4; i++)
    if (strcmp(first, codeString[i]) == 0)
      return i;

  return ASSIGN;
}

void processIF(Statement *statement, Variables *variables)
{
  char gotoStr[NAMELENGTH];
  char opd[NAMELENGTH], opr[NAMELENGTH];

  statement->code = IF;
  scanf("%s", opd);
  statement->opd1 = nameToIndex(variables, opd);
  scanf("%s", opr);
  statement->compopr = oprToComp(opr);
  scanf("%s", opd);
  statement->opd2 = nameToIndex(variables, opd);
  scanf("%s", gotoStr);
  assert(strcmp(gotoStr, "GOTO") == 0);
  scanf("%d", &(statement->gotoLine));
}

void processASSIGN(Statement *statement, char *first, Variables *variables)
{
  char opd[NAMELENGTH], opr[NAMELENGTH];

  statement->code = ASSIGN;
  statement->target = nameToIndex(variables, first);

  char assignStr[NAMELENGTH];
  scanf("%s", assignStr);
  assert(strcmp(assignStr, "=") == 0);

  scanf("%s", opd);
  statement->opd1 = nameToIndex(variables, opd);
  scanf("%s", opr);
  statement->compopr = oprToComp(opr);
  scanf("%s", opd);
  statement->opd2 = nameToIndex(variables, opd);
}

void processCode(Statement statements[], Variables *variables)
{
  char first[NAMELENGTH];
  char opd[NAMELENGTH];
  int lineNum = 1;
  Statement *statement = &(statements[1]);

  while (scanf("%s", first) != EOF) {
    switch (findFirst(first)) {
    case GOTO:
      statement->code = GOTO;
      scanf("%d", &(statement->gotoLine));
      break;
    case STOP:
      statement->code = STOP;
      break;
    case IF:
      processIF(statement, variables);
      break;
    case PRINT:
      statement->code = PRINT;
      scanf("%s", opd);
      statement->target = nameToIndex(variables, opd);
      break;
    case ASSIGN:
      processASSIGN(statement, first, variables);
      break;
    }
    lineNum++;
    statement++;
  }
}


void runCode(Statement statements[], Variables *variables)
{
  int line = 1;

  while (statements[line].code != STOP) {
    Statement statement = statements[line]; 
    switch (statement.code) {
    case IF:
      if (compare(getVariableValue(variables, statement.opd1), 
		  getVariableValue(variables, statement.opd2), 
		  statement.compopr))
	line = statement.gotoLine;
      else
	line++;
      break;
    case GOTO:
      line = statement.gotoLine;
      break;
    case ASSIGN:
      setVariableValue(variables, statement.target,  
		       arithemetic(getVariableValue(variables, statement.opd1),
				   getVariableValue(variables, statement.opd2),
				   statement.compopr));
      line++;
      break;
    case PRINT:
      printf("%d\n", getVariableValue(variables, statement.target));
      line++;
      break;
    default:
      printf("invalid code %d\n", statement.code);
      exit(-1);
    }
  }
}
