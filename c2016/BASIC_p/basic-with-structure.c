#include <stdio.h>

#include "statement.h"

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
