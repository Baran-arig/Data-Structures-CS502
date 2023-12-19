/**
@mainpage CS 502 - Homework 08
@section Description

This program works by asking the user for a max value n and then using a heap to calculate and sort and output the cubesum of all the combinations of numbers from the max value given. 

*/

/**
@file
@author Baran Arig <ba646@drexel.edu>
@date August 27, 2023
@section DESCRIPTION

This is the main file that contains the main function and all functions needed
to make the code run.
*/

#include <stdbool.h>
#include <stdio.h>

/* Sorry, You are on your own - Professor Boady */

typedef struct CubeSum CubeSum;
struct CubeSum {
  int sum; /**< result of i^3 + j^3 */
  int i;   /**< First integer in sum */
  int j;   /**< Second integer in sum */
};

typedef struct Heap Heap;
struct Heap {
  int maxSize;
  int currentSize;
  CubeSum **data;
};

/**
 Create a new heap with starting size 10.
 @return the heap that was created.
 */
Heap *newHeap();

/**
 Delete the heap. Free all memory used.
 @param myHeap is the heap to delete
 */
void deleteHeap(Heap *myHeap);

/**
 Determine if the heap is empty.
 @param myHeap is the heap to check
 @return true if the heap is empty and false otherwise
 */
bool isEmpty(Heap *myHeap);

/**
 Insert a new sum into the heap.
 @param myHeap is the heap to insert into
 @param sum is a pointer to the sum to insert
 */
void insert(Heap *myHeap, CubeSum *sum);

/**
Order the contents of the heap as a minHeap after adding a node.
@param myHeap is the heap to organize.
@param i is the index to start organizing the heap at.
**/
void upHeap(Heap *myHeap, int i);

/**
 Remove the minimum from the heap.
 @param myHeap is the heap to remove from
 */
void removeMin(Heap *myHeap);

/**
Order the contents of the heap as a minHeap after deleting a node.
@param myHeap is the heap to organize.
@param i is the index to start organizing the heap at.
**/
void downHeap(Heap *myHeap, int i);

/**
 Get the pointer to the smallest CubeSum.
 @param myHeap is the heap to get the min of
 @return a pointer to the smallest CubeSum
 */
CubeSum *getMin(Heap *myHeap);

/**
   Stores a sum i^3 + j^3 = k
   */

int main(void) {
  printf("Cube Sum Program.\n");
  printf("Computes Cube Sums from 0 ... N\n");
  int n;
  printf("Enter max value of N:\n");
  scanf("%d", &n);

  Heap *myHeap = newHeap();
  for (int i = 0; i <= n; i++) {
    CubeSum *sum = malloc(sizeof(CubeSum));
    sum->sum = i * i * i + 0 * 0 * 0;
    sum->i = i;
    sum->j = 0;
    insert(myHeap, sum);
  }

  while (!isEmpty(myHeap)) {
    CubeSum *minSum = getMin(myHeap);
    printf("%d^3 + %d^3 = %d\n", minSum->i, minSum->j, minSum->sum);
    removeMin(myHeap);

    if (minSum->j < n) {
      CubeSum *newSum = malloc(sizeof(CubeSum));
      newSum->sum = minSum->i * minSum->i * minSum->i +
                    (minSum->j + 1) * (minSum->j + 1) * (minSum->j + 1);
      newSum->i = minSum->i;
      newSum->j = minSum->j + 1;
      insert(myHeap, newSum);
    }
    free(minSum); // Free the memory allocated for minSum


  }
  deleteHeap(myHeap);
  return 0;
}

Heap *newHeap() {
  Heap *myHeap = malloc(sizeof(Heap));
  myHeap->currentSize = 0;
  myHeap->maxSize = 10;
  myHeap->data = malloc(sizeof(CubeSum *) * myHeap->maxSize);
  return myHeap;
}

void deleteHeap(Heap *myHeap) {
  //free(myHeap->data);
  free(myHeap);
}

bool isEmpty(Heap *myHeap) { return myHeap->currentSize == 0; }

void insert(Heap *myHeap, CubeSum *sum) {
  if (myHeap->currentSize >= myHeap->maxSize) {
    myHeap->maxSize *= 2;
    myHeap->data =
        realloc(myHeap->data,
                sizeof(CubeSum *) * myHeap->maxSize); // i hope this works...
  }

  myHeap->data[myHeap->currentSize] = sum; // skill issue if i dereference this?
  myHeap->currentSize += 1;
  upHeap(myHeap, myHeap->currentSize - 1);
}

void upHeap(Heap *myHeap, int i) {
  int p = (i - 1) / 2;
  if (i == 0) {
    return;
  }
  /**
  if(myHeap->data[p]->sum == myHeap->data[i]->sum){
    if(myHeap->data[p]->i < myHeap->data[i]->j){
      CubeSum *temp = myHeap->data[p];
      myHeap->data[p] = myHeap->data[i];
      myHeap->data[i] = temp;
    }
  }
**/
  if (myHeap->data[p]->sum < myHeap->data[i]->sum ||
      (myHeap->data[p]->sum == myHeap->data[i]->sum &&
       myHeap->data[p]->i < myHeap->data[i]->i)) {
    return;
  }

  CubeSum *temp = myHeap->data[p];
  myHeap->data[p] = myHeap->data[i];
  myHeap->data[i] = temp;
  upHeap(myHeap, p);
  return;
}

void removeMin(Heap *myHeap) {
  myHeap->data[0] = myHeap->data[myHeap->currentSize-1];

  myHeap->currentSize -= 1;
  downHeap(myHeap, 0);
}

void downHeap(Heap *myHeap, int i) {
  int leftIndex = (i + 1) * 2 - 1;
  int rightIndex = (i + 1) * 2;

  if (leftIndex >= myHeap->currentSize) {
    return;
  }

  int minIndex = 0;
  if (myHeap->data[leftIndex]->sum > myHeap->data[rightIndex]->sum ||
      myHeap->data[leftIndex]->sum == myHeap->data[rightIndex]->sum &&
        myHeap->data[leftIndex]->i > myHeap->data[rightIndex]->i) {
    minIndex = rightIndex;
  } else {
    minIndex = leftIndex;
  }
  
  if (myHeap->data[i]->sum > myHeap->data[minIndex]->sum || 
      (myHeap->data[i]->sum == myHeap->data[minIndex]->sum &&
       myHeap->data[minIndex]->i < myHeap->data[i]->i)) {
    CubeSum *temp = myHeap->data[minIndex];
    myHeap->data[minIndex] = myHeap->data[i];
    myHeap->data[i] = temp;
    downHeap(myHeap, minIndex);
  }
  return;
}

CubeSum *getMin(Heap *myHeap) { return myHeap->data[0]; }
