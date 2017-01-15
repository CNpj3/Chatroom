#define ADD 0
#define SUB 1
#define MUL 2
#define DIV 3
#define MOD 4

#define EQL 5
#define NOTEQL 6
#define SMALLER 7
#define LARGER 8
#define SMALLEREQL 9
#define LARGEREQL 10

int oprToComp(char name[]);
int compare(int operand1, int operand2, int operator);
int arithemetic(int operand1, int operand2, int operator);