#include "heap.h"
#include <stdio.h>

/* Heap: int ary[MAXHEAP], int num */
/* max heap */
void initialize(struct Heap *heap)
{
    heap->num=0;
    heap->ary={0};
}
int removeMin(struct Heap *heap)
{
    int min = heap->ary[num-1];
    heap->ary[num-1]=0;
    heap->num--;
    return min;
}
void heap_sort(struct Heap *heap)
{

}
void add(struct Heap *heap, int i)
{
    heap->ary[num++]=i;
    heap_sort(heap);
}
int isFull(struct Heap *heap)
{
    for (int i=0;i<MAXHEAP;i++) 
        if (heap->ary[i]==0) return 0;
    return 1;
}
int isEmpty(struct Heap *heap)
{
    for (int i=0;i<MAXHEAP;i++) 
        if (heap->ary[i]) return 0;
    return 1;
}
