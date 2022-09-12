// graph.h

#ifndef __GRAPH_H__
#define __GRAPH_H__

#include "list.h"
#include "edge.h"
#include "pq.h"

enum {A, B, C, D, E, F, G, H};
typedef struct __graph
{
  int numV;
  int numE;
  List* vertex;
  int* visitInfo;
  PQueue pq;
} Graph;

void graphInit(Graph* pg, int numV);
void graphDestroy(Graph* pg);
void addEdge(Graph* pg, int from, int to, int weight);
void graphShow(Graph* pg);
void graphDFS(Graph* pg, int startV);
void makeMST(Graph* pg);
void showEdge(Graph* pg);

#endif
