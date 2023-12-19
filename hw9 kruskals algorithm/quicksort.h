/**
        @file
        @author Baran Arig <ba646@drexel.edu>
        @date September 1, 2023
        @section DESCRIPTION

        This is the header file for the quicksort algorithm. 
 */

#ifndef _QUICKSORT_H_
#define _QUICKSORT_H_

#include <stdio.h>
#include <stdlib.h>
#include "adjmatrix.h"
#include "kruskal.h"

/**
        Create a partition point in the array to pivot around
        @param A is the array
        @param start is the start of where you want to partition from
        @param end where you want to stop the partition
        @return the partition point
 */
int partition(edge *A, int start, int stop);

/**
        quicksort an array
        @param A is the array
        @param size is the size of the array
 */
void quicksort(edge *A, int size);

/**
        helper function to quicksort the array recursively
        @param A is the array
        @param start is where to start the section to quicksort
        @param stop is where to stop the section to quicksort
 */
void myqsort(edge *A, int start, int stop);

/**
        swaps the values of two indexes in an array
        @param A is the array
        @param i is the first index to swap
        @param j is the second index to swap
 */
void swap(edge *A, int i, int j);

#endif