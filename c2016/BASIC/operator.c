#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "operator.h"

int oprToComp(char name[])
{
	char *operators[11] = {"+", "-", "*", "/", "%", "==", "!=", "<", ">", "<=", ">="};
	int opNum = 11;

	for (int i = 0; i < opNum; i++)
    	if (strcmp(name, operators[i]) == 0)
      		return i;

  	printf("invalid op %s", name);
  	exit(-1);
}

int compare(int operand1, int operand2, int operator)
{
	switch (operator) {
	case EQL:
		return (operand1 == operand2);
	case NOTEQL:
		return (operand1 != operand2);
	case SMALLER:
		return (operand1 < operand2);
	case LARGER:
		return (operand1 > operand2);
	case SMALLEREQL:
		return (operand1 <= operand2);
	case LARGEREQL:
		return (operand1 >= operand2);
	default:
		printf("invalid comp %d\n", operator);
		exit(-1);
  }
}

int arithemetic(int operand1, int operand2, int operator)
{
	switch (operator) {
	case ADD:
		return (operand1 + operand2);
	case SUB:
		return (operand1 - operand2);
	case MUL:
		return (operand1 * operand2);
	case DIV:
		return (operand1 / operand2);
	case MOD:
		return (operand1 % operand2);
	default:
		printf("invalid comp %d\n", operator);
		exit(-1);
  }
}
