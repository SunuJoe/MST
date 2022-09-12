// func_stack.c

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

void stackInit(Stack* pstack)
{
  pstack->topidx = -1;
}

int stackisEmpty(Stack* pstack)
{
  if(pstack->topidx == -1)
    return TRUE;
  else
    return FALSE;
}

void Push(Stack* pstack, Sdata val)
{
  if(pstack->topidx >= LEN-1)
    return;
  else
  {
    (pstack->topidx)++;
    pstack->stackArr[pstack->topidx] = val;
  }
}

Sdata Pop(Stack* pstack)
{
  if(pstack->topidx <= -1)
    exit(-1);
  else
  {
    Sdata temp = pstack->stackArr[pstack->topidx];
    (pstack->topidx)--;
    return temp;
  }
}

Sdata Peek(Stack* pstack)
{
  return pstack->stackArr[pstack->topidx];
}
