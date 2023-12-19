/**
        @file
        @author Baran Arig <ba646@drexel.edu>
        @date September 2, 2023
        @section DESCRIPTION

        This is the implementation of the header file for the adjacency matrix              algorithm.
 */

#include "adjmatrix.h"
#include <stdio.h>
#include <stdlib.h>

AdjMatrix *newAdjMatrix(int size) {
  AdjMatrix *graph = malloc(sizeof(AdjMatrix));
  graph->numNodes = size;
  /* Make a matrix */
  int **matrix = malloc(sizeof(int *) * size);
  for (int i = 0; i < size; i++) {
    matrix[i] = malloc(sizeof(int) * size);
  }
  /* Set the values */
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      if (i == j) {
        matrix[i][j] = 0;
      } else {
        matrix[i][j] = INFINITY;
      }
    }
  }
  /* Set the matrix */
  graph->matrix = matrix;
  return graph;
}
void deleteAdjMatrix(AdjMatrix *graph) {
  /* Free the rows */
  for (int i = 0; i < graph->numNodes; i++) {
    free(graph->matrix[i]);
  }
  /* Free array */
  free(graph->matrix);
  /* Free the graph */
  free(graph);
}

void printGraph(AdjMatrix *graph) {
  printf("Graph Data:\n");
  printf("Number of Nodes: %d\n", graph->numNodes);
  for (int i = 0; i < graph->numNodes; i++) {
    for (int j = 0; j < graph->numNodes; j++) {
      int weight = graph->matrix[i][j];
      if (weight == INFINITY || weight == 0) {
        //printf("Edge From %d to %d has weight infinity.\n", i, j);
      } else {
        printf("Edge From %d to %d has weight %d.\n", i, j, weight);
      }
    }
  }
}

int getEdge(AdjMatrix *graph, int from, int to) {
  if (from < 0 || to < 0 || from >= graph->numNodes || to >= graph->numNodes) {
    return INFINITY;
  }
  return graph->matrix[from][to];
}
void setEdge(AdjMatrix *graph, int from, int to, int weight) {
  if (from < 0 || to < 0 || from >= graph->numNodes || to >= graph->numNodes) {
    return;
  }
  graph->matrix[from][to] = weight;
}
void deleteEdge(AdjMatrix *graph, int from, int to) {
  setEdge(graph, from, to, INFINITY);
}
int getNumNodes(AdjMatrix *graph) { return graph->numNodes; }
