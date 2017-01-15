#define VAR 100
#define NAMELENGTH 80

typedef struct variable {
	char name[NAMELENGTH];
	int value;
} Variable;

typedef struct variables {
	Variable var[VAR];
	int number;
} Variables;

int nameToIndex(Variables *variables, char *name);
void initVariables(Variables *variables);
void insertVariable(Variables *variables, char *name, int initValue);
int getVariableValue(Variables *variables, int varIndex);
void setVariableValue(Variables *variables, int varIndex, int value);
void readAllVariables(Variables *variables);