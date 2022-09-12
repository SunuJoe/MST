// heap.h
// define heap using array.

#ifndef __HEAP_H__
#define __HEAP_H__

#define TRUE 1
#define FALSE 0
#include "edge.h"

#define LEN 100

typedef Edge Hdata;
typedef int (*func_heap)(Hdata h1, Hdata h2);
typedef struct __heap
{
  Hdata heapArr[LEN];
  int num;
  func_heap comp;
} Heap;

void heapInit(Heap* ph, func_heap rule);
int heapisEmpty(Heap* ph);
void heapInsert(Heap* ph, Hdata val);
Hdata heapDelete(Heap* ph);

#endif
