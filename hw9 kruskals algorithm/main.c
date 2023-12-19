/**
@mainpage CS 502 - Homework 09
@section Description

This program works by asking the user for a file path. That file will contain
values used in a graph. From there an adjacency matrix will be created to store
those values and kruskals algorithm will be implemented to solve for the Minimum
Spanning Tree (MST).

*/

/**
@file
@author Baran Arig <ba646@drexel.edu>
@date September 2, 2023
@section DESCRIPTION

This is the main file that contains the functions for reading user input and
reading from a text file and setting those values into an adjacency matrix and
then running Kruskals algorithm on it.
*/

#include "adjmatrix.h"
#include "kruskal.h"
#include "quicksort.h"
#include <stdio.h>

/**
read input from user and save it as an input.
@return character array from user input.
*/
char *readFromStdin();

/* No Help :-) Just the files */
int main(void) {
  printf("Enter File Containing Graph:\n");
  printf("Running Kruskal's Algorithm\n");
  FILE *fptr;
  int number;
  int lineNumber = 1;
  int colNumber = 1;

  char *filename = readFromStdin();
  char singleLine[150];
  printf("Input File: %s\n", filename);
  fptr = fopen(filename, "r");
  AdjMatrix *graph = NULL;

  while (fscanf(fptr, "%d", &number) == 1) {
    int numNodes, fromNode, toNode, weight;
    if (lineNumber == 1) {
      numNodes = number;
      graph = newAdjMatrix(numNodes);
      lineNumber++;
    } else {
      if (colNumber == 1) {
        fromNode = number;
        colNumber++;
      } else if (colNumber == 2) {
        toNode = number;
        colNumber++;
      } else if (colNumber == 3) {
        weight = number;
        setEdge(graph, fromNode, toNode, weight);
        colNumber = 1;
      }
    }
  }
  fclose(fptr);

  AdjMatrix *MST = Kruskal(graph);

  deleteAdjMatrix(MST);
  deleteAdjMatrix(graph);
  return 0;
}

char *readFromStdin() {
  int bufferSize = 200;
  char *buffer = malloc(sizeof(char) * bufferSize);
  int position = 0;

  char temp;
  temp = getchar();
  while (temp != EOF && temp != '\n') {
    buffer[position] = temp;
    temp = getchar();
    position++;
  }

  buffer[position] = 0;
  position++;

  return buffer;
}