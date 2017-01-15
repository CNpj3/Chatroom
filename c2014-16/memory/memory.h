typedef struct free{
    int start;
    int length;
    struct free *prev;
    struct free *next;
}Free;

typedef struct memory{
    int length;
    Free *set;
} Memory;

void initMemory(Memory *memory, int length);
void printMemory(Memory *memory);
void allocateMemory(Memory *memory, int start, int length);
void freeMemory(Memory *memory, int start, int length);
