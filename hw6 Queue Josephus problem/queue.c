/**
        @file
        @author Baran Arig <ba646@drexel.edu>
        @date 8/11/23
        @section DESCRIPTION

        implementation of all the functions created in the queue.h file.
 */
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

Queue *newQueue() {
  Queue *myQueue = malloc(2 * sizeof(Node));
  myQueue->head = NULL;
  myQueue->tail = NULL;
  return myQueue;
}

char isEmpty(Queue *Q) { return (Q->head == NULL); }

void enqueue(int v, Queue *Q) {
  Node *newNode = malloc(sizeof(Node));
  newNode->next = NULL;
  newNode->value = v;

  if (Q->head == NULL) {
    Q->head = newNode;
  } else {
    Q->tail->next = newNode;
  }
  Q->tail = newNode;
}

int front(Queue *Q) {
  if (Q->head == NULL) {
    return -1;
  }
  return Q->head->value;
}

void dequeue(Queue *Q) {
  if (Q->head == NULL) {
    return;
  }
  Node *temp = Q->head;
  Q->head = temp->next;
  free(temp);
  if (Q->head == NULL) {
    Q->tail = NULL;
  }
}

void printQueue(Queue *Q) {
  Node *current = Q->tail;
  while (current != NULL) {
    printf("%d", current->value);
    current = current->next;
  }
  free(current);
}

void josephus(int n, int m) {
  Queue *myQueue = newQueue();
  for (int i = 0; i < n; i++) {
    enqueue(i, myQueue);
  }
  // printf("Order Eliminated:\n");

  while (!isEmpty(myQueue)) {
    int temp = 0;
    for (int j = 0; j < m - 1; j++) {
      temp = front(myQueue);
      dequeue(myQueue);
      enqueue(temp, myQueue);
    }
    printf("%d", front(myQueue));
    dequeue(myQueue);
    if (isEmpty(myQueue)) {
      printf("\n");
    } else {
      printf(" ");
    }
  }

  free(myQueue);
  return;
}