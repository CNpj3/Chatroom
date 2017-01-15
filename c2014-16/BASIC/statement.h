#include "variables.h"
#include "operator.h"

#define LINE 200

#define STOP 0
#define IF 1
#define GOTO 2
#define PRINT 3
#define ASSIGN 4

typedef struct statement {
  int code;    /* code for each line */
  int opd1, compopr, opd2;
  int gotoLine; /* IF */
  int target;  /* both PRINT and ASSIGN use this */
} Statement;

int findFirst(char *first);
void processIF(Statement *statement, Variables *variables);
void processASSIGN(Statement *statement, char *first, Variables *variables);
void processCode(Statement statements[], Variables *variables);
void runCode(Statement statements[], Variables *variables);






w