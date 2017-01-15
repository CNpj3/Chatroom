#include "memory.h"
#include <stdio.h>
#include <stdlib.h>

/*
typedef struct memory{
    int start;
    int length;
    struct memory *prev;
    struct memory *next;
} Memory;
*/
void initMemory(Memory *memory, int n) {
    memory->length = n;
    Free *root;
    root->start=0;
    root->length=n;
    root->prev=NULL;
    root->next=NULL;
    return;
}
void allocateMemory(Memory *memory, int start, int length) {

    Memory *tmp = (Memory*)malloc(sizeof(Memory));
    tmp->start = start+length;
        
    if (memory->prev==NULL && memory->next--NULL) {
        memory->next==tmp;
        memory->length=start;
        return;
    }
    else {
        Memory *cur = memory;
        while (cur->start > start || cur->length < length) cur=cur->next;
        cur->
    }

}
void print_memory(Memory *memory) {
    f
}
