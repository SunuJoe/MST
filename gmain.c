// gmain.c

#include <stdio.h>
#include "graph.h"

int main(int argc, char* argv[])
{
  Graph graph;
  graphInit(&graph, 4);

  addEdge(&graph, A, B, 4);
  addEdge(&graph, B, C, 1);
  addEdge(&graph, C, D, 5);
  addEdge(&graph, D, A, 9);

  graphShow(&graph);
  graphDFS(&graph, A);
  makeMST(&graph);
  graphShow(&graph);
  showEdge(&graph);

  return 0;
}
