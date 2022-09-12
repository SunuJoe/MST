// stack.h

#ifndef __STACK_H__
#define __STACK_H__

#define LEN 100

#define TRUE 1
#define FALSE 0

typedef int Sdata;
typedef struct __stack
{
  Sdata stackArr[LEN];
  int topidx;
} Stack;

void stackInit(Stack* pstack);
int stackisEmpty(Stack* pstack);
void Push(Stack* pstack, Sdata val);
Sdata Pop(Stack* pstack);
Sdata Peek(Stack* pstack);

#endif
