/**
        @file
        @author Baran Arig <ba646@drexel.edu>
        @date September 1, 2023
        @section DESCRIPTION

        This is the implementation of the quicksort algorithm.
 */

#include "quicksort.h"
#include <stdio.h>
#include <stdlib.h>

int partition(edge *A, int start, int stop) {
  int randomIndex = rand() % (stop - start + 1) + start;
  edge temp = A[stop];
  swap(A, stop, randomIndex);

  edge pivot = A[stop];
  int i = start;
  for (int j = start; j < stop; j++) {
    if ((A[j].weight < pivot.weight) ||
        (A[j].weight == pivot.weight && A[j].from < pivot.from) ||
        (A[j].weight == pivot.weight && A[j].from == pivot.from &&
         A[j].to < pivot.to)) {
      swap(A, i, j);
      i++;
    }
  }
  swap(A, i, stop);
  return i;
}

void swap(edge *A, int i, int j) {
  edge temp = A[i];
  A[i] = A[j];
  A[j] = temp;
}

void quicksort(edge *A, int size) { myqsort(A, 0, size - 1); }

void myqsort(edge *A, int start, int stop) {
  if (start < stop) {
    int p = partition(A, start, stop);
    myqsort(A, start, p - 1);
    myqsort(A, p + 1, stop);
  }
}