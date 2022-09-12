// func_graph.c

#include "graph.h"
#include "stack.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int listrule(Ldata v1, Ldata v2)
{
  if(v1 > v2)
    return 1;
  else
    return 0;
}

int edgerule(Edge e1, Edge e2)
{
  return e1.weight - e2.weight;
}

void graphInit(Graph* pg, int numV)
{
  pg->numV = numV;
  pg->numE = 0;
  pg->vertex = (List*)malloc(sizeof(List)*numV);
  
  for(int i=0; i<numV; i++)
  {
    listInit((pg->vertex)+i);
    setRule((pg->vertex)+i, listrule); 
  }
  pqInit(&(pg->pq), edgerule);
  pg->visitInfo = (int*)malloc(sizeof(int)*numV);
  memset(pg->visitInfo, 0, sizeof(int)*numV);
}

void graphDestroy(Graph* pg)
{
  Ldata rval;
  for(int i=0; i<pg->numV; i++)
  {
    if(firstSearch((pg->vertex)+i, &rval))
    {
      printf("Delete %c vertex Node : %c", i+65, (listDelete((pg->vertex)+i))+65);
      while(nextSearch((pg->vertex)+i, &rval))
      {
        printf(", %c", (listDelete((pg->vertex)+i))+65);  
      }
    }
    printf("\n");
  }
  free(pg->vertex);
}

void addEdge(Graph* pg, int from, int to, int weight)
{
  Edge edge = {from, to, weight};
  if(from >= pg->numV && to >= pg->numV)
  {
    printf("out of vertex range\n");
    return;
  }
  else
  {
    listInsert((pg->vertex)+from, to);
    listInsert((pg->vertex)+to, from);
    enQueue(&(pg->pq), edge);
    (pg->numE)++;
  }
}

void graphShow(Graph* pg)
{
  Ldata rval;
  for(int i=0; i<pg->numV; i++)
  {
    if(firstSearch((pg->vertex)+i, &rval))
    {
      printf("%c vertex connect : %c", i+65, rval+65);
      while(nextSearch((pg->vertex)+i, &rval))
        printf(", %c", rval+65);
    }
    printf("\n");
  }
}
//help func.
int checkVisit(Graph* pg, int visitV)
{
  if(pg->visitInfo[visitV] == 0)
  {
    pg->visitInfo[visitV] = 1;
    printf("now visited : %c\n", visitV+65);
    return TRUE;
  }
  else
    return FALSE;
}

void graphDFS(Graph* pg, int startV)
{
  Stack stack;
  int visitV = startV;
  int nextV;
  stackInit(&stack);

  checkVisit(pg, visitV);

  while(firstSearch((pg->vertex)+visitV, &nextV))
  {
    int flag = FALSE;
    if(checkVisit(pg, nextV))
    {
      Push(&stack, visitV);
      visitV = nextV;
      flag = TRUE;
    }
    else
    {
      while(nextSearch((pg->vertex)+visitV, &nextV))
      {
        if(checkVisit(pg, nextV))
        {
          Push(&stack, visitV);
          visitV = nextV;
          flag = TRUE;
          break;
        }
      }
    }
    if(flag == FALSE)
    {
      if(stackisEmpty(&stack))
        break;
      else
        visitV = Pop(&stack);
    }
  }
  memset(pg->visitInfo, 0, sizeof(int)*pg->numV);
}
// helper func.
int checkCycle(Graph* pg, int from, int to)
{
  Stack stack;
  int visitV = from;
  int nextV;
  stackInit(&stack);

  checkVisit(pg, visitV);

  while(firstSearch((pg->vertex)+visitV, &nextV))
  {
    int flag = FALSE;
    if(nextV == to)
    {
      memset(pg->visitInfo, 0, sizeof(int)*pg->numV);
      printf("connect checked ok\n");
      return TRUE;
    }
    if(checkVisit(pg, nextV))
    {
      Push(&stack, visitV);
      visitV = nextV;
      flag = TRUE;
    }
    else
    {
      while(nextSearch((pg->vertex)+visitV, &nextV))
      {
        if(nextV == to)
        {
          memset(pg->visitInfo, 0, sizeof(int)*pg->numV);
          printf("connect checked ok\n");
          return TRUE;
        }
        if(checkVisit(pg, nextV))
        {
          Push(&stack, visitV);
          visitV = nextV;
          flag = TRUE;
          break;
        }
      }
    }
    if(flag == FALSE)
    {
      if(stackisEmpty(&stack))
        break;
      else
        visitV = Pop(&stack);
    }
  }
  memset(pg->visitInfo, 0, sizeof(int)*pg->numV);
  printf("connect checked : no \n");
  return FALSE;
}

void removeWay(Graph* pg, int from, int to)
{
  Ldata rval;
  if(firstSearch((pg->vertex)+from, &rval))
  {
    if(rval == to)
      listDelete((pg->vertex)+from);
      return;
    while(nextSearch((pg->vertex)+from, &rval))
    {
      if(rval == to)
      {
        listDelete((pg->vertex)+from);
        return;
      }
    }
  }
}

void removeEdge(Graph* pg, int from, int to)
{
  removeWay(pg, from, to);
  removeWay(pg, to, from);
  (pg->numE)--;
}

void recoverEdge(Graph* pg, int from, int to)
{
  listInsert((pg->vertex)+from, to);
  listInsert((pg->vertex)+to, from);
  (pg->numE)++;
}

void makeMST(Graph* pg)
{
  Edge edge;
  Edge rcv[20];
  int eidx = 0;
  printf("%d edge num \n", pg->numE+1); 
  printf("%d edge num \n", pg->numV); 
  while(pg->numE+1 > pg->numV)
  {
    printf("edge remove\n");
    edge = deQueue(&(pg->pq));
    removeEdge(pg, edge.v1, edge.v2);
    if(!checkCycle(pg, edge.v1, edge.v2))
    {
      recoverEdge(pg, edge.v1, edge.v2);
      rcv[eidx++] = edge;
    }
  }
  for(int i=0; i<eidx; i++)
  {
    enQueue(&(pg->pq), rcv[i]);
  }
}

void showEdge(Graph* pg)
{
  PQueue backupQ = pg->pq;
  Edge edge;

  while(!pqisEmpty(&backupQ))
  {
    edge = deQueue(&backupQ);
    printf("%c - %c : %d\n", (edge.v1)+65, (edge.v2)+65, edge.weight);
  }
}
