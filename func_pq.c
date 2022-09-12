// func_pq.c

#include "pq.h"

void pqInit(PQueue* pq, func_heap rule)
{
  heapInit(pq, rule);
}

int pqisEmpty(PQueue* pq)
{
  return heapisEmpty(pq);
}

void enQueue(PQueue* pq, PQdata val)
{
  heapInsert(pq, val);
}

PQdata deQueue(PQueue* pq)
{
  return heapDelete(pq);
}
