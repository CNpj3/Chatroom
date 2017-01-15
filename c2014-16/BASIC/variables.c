#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "variables.h"

int nameToIndex(Variables *variables, char *name)
{
	for (int i = 0; i < variables->number; i++)
    	if (strcmp(variables->var[i].name, name) == 0)
     		return i;

  	printf("undefined variable %s\n", name);
  	exit(-1);
}
void initVariables(Variables *variables)
{
	variables->number = 0;
}
void insertVariable(Variables *variables, char *name, int initValue)
{
	Variable *variable = &(variables->var[variables->number]); //the last postion
	strcpy(variable->name, name);
  	variable->value = initValue;
  	variables->number++;
}
int getVariableValue(Variables *variables, int varIndex)
{
	return (variables->var[varIndex].value);
}
void setVariableValue(Variables *variables, int varIndex, int value)
{
	variables->var[varIndex].value = value;
}
void readAllVariables(Variables *variables)
{
	char name[NAMELENGTH];
	initVariables(variables);
	scanf("%s", name);
  	while (strcmp(name, "END") != 0) {
    	char assignStr[NAMELENGTH];
    	int initValue;
    	strcpy(varName[count], name);
    	scanf("%s", assignStr);
    	assert(strcmp(assignStr, "=") == 0);
    	scanf("%d", &initValue);
    	insertVariable(variables, name, initValue);
    	scanf("%s", name);
  	} 
  	return;
}