// func_heap.c

#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

void heapInit(Heap* ph, func_heap rule)
{
  ph->num = 0;
  ph->comp = rule;
}

int heapisEmpty(Heap* ph)
{
  if(ph->num <= 0)
    return TRUE;
  else
    return FALSE; 
}

//helper func.
int getParentIdx(int idx)
{
  return idx/2;
}

int getLtChildIdx(int idx)
{
  return idx*2;
}

int getRtChildIdx(int idx)
{
  return (idx*2)+1;
}

int getHighPrChildIdx(Heap* ph, int idx)
{
  if(getLtChildIdx(idx) > ph->num)
    return 0;
  else if(getLtChildIdx(idx) == ph->num)
    return getLtChildIdx(idx);
  else
  {
    if(ph->comp(ph->heapArr[getLtChildIdx(idx)], ph->heapArr[getRtChildIdx(idx)]) >= 0)
      return getLtChildIdx(idx);
    else
      return getRtChildIdx(idx);
  }
}

void heapInsert(Heap* ph, Hdata val)
{
  if(ph->num >= LEN-1)
    return;
  else
  {
    int idx = ph->num+1;
    while(idx != 1)
    {
      if(ph->comp(val, ph->heapArr[getParentIdx(idx)]) > 0)
      {
        ph->heapArr[idx] = ph->heapArr[getParentIdx(idx)];
        idx = getParentIdx(idx);
      }
      else
        break;
    }
    ph->heapArr[idx] = val;
    (ph->num)++;
  }
}

Hdata heapDelete(Heap* ph)
{
  if(ph->num == 0)
    exit(-1);
  else
  {
    int idx = 1;
    int cidx;
    Hdata temp = ph->heapArr[1];
    Hdata comp_val = ph->heapArr[ph->num];
    
    while((cidx = getHighPrChildIdx(ph, idx))) 
    {
      if(ph->comp(comp_val, ph->heapArr[cidx]) < 0)
      {
        ph->heapArr[idx] = ph->heapArr[cidx];
        idx = cidx;
      }
      else  break;
    }
    ph->heapArr[idx] = comp_val;
    (ph->num)--;
    return temp;
  }
}
