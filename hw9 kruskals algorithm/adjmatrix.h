/**
        @file
        @author Baran Arig <ba646@drexel.edu>
        @date September 2, 2023
        @section DESCRIPTION

        This is the header file for the adjacency matrix algorithm.
 */

#ifndef _ADJ_MATRIX_H_
#define _ADJ_MATRIX_H_

#define INFINITY 999999

/**
        A structure to represent an adjacency matrix.
 */
struct AdjacencyMatrix {
  int **matrix; /**< the 2d array of values.*/
  int numNodes; /**< the number of nodes in the graph.*/
};
typedef struct AdjacencyMatrix AdjMatrix;
/**
        create a new adjacency matrix
        @param size is the number of nodes in the graph
        @return an adjacency matrix
 */
AdjMatrix *newAdjMatrix(int size);

/**
        delete an adjacency matrix
        @param graph is the adjacency matrix
 */
void deleteAdjMatrix(AdjMatrix *graph);

/**
        print an adjacency matrix
        @param graph is the adjacency matrix
 */
void printGraph(AdjMatrix *graph);

/**
        get edge weight from the adjacency matrix
        @param graph is the adjacency matrix
        @param from is the from node
        @param to is the to node
        @return the edge weight
 */
int getEdge(AdjMatrix *graph, int from, int to);

/**
        set edge weight in the adjacency matrix
        @param graph is the adjacency matrix
        @param from is the from node
        @param to is the to node
        @param weight is the weight
 */
void setEdge(AdjMatrix *graph, int from, int to, int weight);

/**
        delete edge weight from the adjacency matrix
        @param graph is the adjacency matrix
        @param from is the from node
        @param to is the to node
 */
void deleteEdge(AdjMatrix *graph, int from, int to);

/**
        get the number of nodes in an adjacency matrix
        @param graph is the adjacency matrix
        @return the number of nodes in the matrix
 */
int getNumNodes(AdjMatrix *graph);

#endif