// pq.h

#ifndef __PQ_H__
#define __PQ_H__

#include "heap.h"
#include "edge.h"
typedef Edge PQdata;
typedef Heap PQueue;

void pqInit(PQueue* pq, func_heap rule);
int pqisEmpty(PQueue* pq);
void enQueue(PQueue* pq, PQdata val);
PQdata deQueue(PQueue* pq);

#endif
