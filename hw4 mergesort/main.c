/**
@mainpage CS 502 - Homework 04
@section Description

This program works by asking the user for a filename and then using mergesort to
sort the contents of the files.

*/

/**
@file
@author Baran Arig <ba646@drexel.edu>
@date July 31, 2023
@section DESCRIPTION

this is the main file that contains the main function and all functions needed
to make the code run.
*/

#include <stdio.h>

#define wordLength 200
#define numLines 109583
#define FALSE (1 == 0)
#define TRUE (1 == 1)

/**
Merge Sort an array of strings
@param wordList is the list of words to sort
@param size is the number of words to sort
*/
void msort(char **wordList, int size);

/**
Recursive implemenation of merge sort
@param wordList is the array to sort
@param start is the first index to sort
@param stop is the last index to sort
*/
void msortRec(char **wordList, int start, int stop);

/**
Merge two sections of the array together
@param wordList is the array to merge
@param start is the start of the first half
@param middle is the break point, the last value of the first half
@param stop is the end of the second half
*/
void merge(char **wordList, int start, int middle, int stop);

/**
Copy parts of a larger array
@param wordList is the larger array
@param start is the start of the section
@param middle is the end of the section
@return a 2d character array
*/
char **copyParts(char **wordList, int start, int middle);

/**
compare 2 strings
@param word1 is the 2d array containing the first word
@param word2 is the 2d array containing the second word
@param firstLine is the line index for the word in the word1 array
@param secondLine is the line index for the word in the word2 array
@return true if word1 < word2 else return false.
*/
int lessThan(char **word1, char **word2, int firstLine, int secondLine);

/**
read input from user and save it as an input.
@return character array from user input.
*/
char *readFromStdin();

/**
prints a 2d array
@param wordList is a 2d array containing all the words
@param rows is the number of rows in the 2d array
@param columns is the number of columns in the array
@return character array from user input.
*/
void printArray(char **wordList, int rows, int columns);

int main(void) {

  FILE *fptr;
  char ch;

  printf("Enter File Name:\n");
  char *filename = readFromStdin();
  // char singleLine[150];
  // int wordLength = 200;
  // int numLines = 109583;
  // char **wordList[numLines][wordLength];
  // char word[wordLength];
  char **wordList = NULL;
  wordList = malloc(numLines * sizeof(char *));

  for (int i = 0; i < numLines; i++) {
    wordList[i] = malloc(wordLength * sizeof(char));
  }

  printf("Opening File: %s\n", filename);
  fptr = fopen(filename, "r");

  int line = 0;

  while (!feof(fptr) && !ferror(fptr)) {
    if (fgets(wordList[line], wordLength, fptr) != NULL) {
      line++;
    }
  }

  fclose(fptr);
  msort(wordList, line);

  printArray(wordList, line, wordLength);

  free(wordList);
  free(filename);
  return 0;
}

void msort(char **wordList, int size) { msortRec(wordList, 0, size - 1); }

void msortRec(char **wordList, int start, int stop) {
  if (start >= stop) {
    return;
  }

  int middle = start + (stop - start) / 2;
  msortRec(wordList, start, middle);
  // printf("I make 1st recursion");
  msortRec(wordList, middle + 1, stop);
  // printf("I make second recursion");
  merge(wordList, start, middle, stop);
}

void merge(char **wordList, int start, int middle, int stop) {

  char **first = copyParts(wordList, start, middle);
  char **second = copyParts(wordList, middle + 1, stop);

  int sizeF = middle - start + 1;
  int sizeS = stop - (middle + 1) + 1;

  int letterIter = 0, firstLine = 0, secondLine = 0;
  for (int line = start; line <= stop; line++) {
    if (firstLine >= sizeF) {
      // for(letterIter = 0; letterIter < wordLength; letterIter++ ){
      wordList[line] = second[secondLine];
      // while (second[secondLine][letterIter] != '\n') {
      //   wordList[line][letterIter] = second[secondLine][letterIter];
      //   letterIter++;
      // }
      secondLine++;
      // letterIter = 0;
    } else if (secondLine >= sizeS) {
      // for(letterIter = 0; letterIter < wordLength; letterIter++ ){
      wordList[line] = first[firstLine];

      // while (first[firstLine][letterIter] != '\n') {
      //   wordList[line][letterIter] = first[firstLine][letterIter];
      //   letterIter++;
      // }
      firstLine++;
      // letterIter = 0;
    } else if (lessThan(first, second, firstLine, secondLine)) {
      wordList[line] = first[firstLine];
      // for(letterIter = 0; letterIter < wordLength; letterIter++ ){
      // while (first[firstLine][letterIter] != '\n') {
      //   wordList[line][letterIter] = first[firstLine][letterIter];
      //   letterIter++;
      // }
      firstLine++;
      // letterIter = 0;
    } else {
      wordList[line] = second[secondLine];
      // for(letterIter = 0; letterIter < wordLength; letterIter++ ){
      // while (second[secondLine][letterIter] != '\n') {
      //   wordList[line][letterIter] = second[secondLine][letterIter];
      //   letterIter++;
      // }
      secondLine++;
      // letterIter = 0;
    }

    // if(lessThan(first, second, line, int row)){
    // if (i >= sizeF) {
  }
  free(first);
  free(second);
  // free(first);
  // free(second);
  //  printArray(wordList, stop, wordLength);
}

char **copyParts(char **wordList, int start, int middle) {
  int size = middle - start + 1;
  int i, j;

  char **segment;
  segment = malloc(size * sizeof(char *));

  for (i = 0; i < size; i++) {
    segment[i] = malloc(wordLength * sizeof(char));
  }

  for (i = 0; i < size; i++) {
    segment[i] = wordList[start + i];
  }

  return segment;
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

int lessThan(char **word1, char **word2, int firstLine, int secondLine) {
  int row = 0;
  while ((word1[firstLine][row] != '\n') && (word2[secondLine][row] != '\n')) {
    if (word1[firstLine][row] < word2[secondLine][row]) {
      return TRUE;
    }
    if (word1[firstLine][row] > word2[secondLine][row]) {
      return FALSE;
    }
    row++;
  }
  if (word1[firstLine][row] == '\n') {
    return TRUE;
  } else {
    return FALSE;
  }
}

void printArray(char **wordList, int rows, int columns) {

  for (int i = 0; i < rows; i++) {
    printf("%d: %s", i, wordList[i]);
  }

  // int i, j;

  // for (i = 0; i < rows; i++) {
  //   // if (wordList[i][j] == '\0') {
  //   //   return;
  //   // }
  //   printf("%d: ", i);
  //   for (j = 0; j < columns; j++) {
  //     printf("%s", wordList[i]);
  //   }
  //   printf("\n");
  // }
}
// minimize time complexity by not using 2 loops, similar to line 272.
// tux drexel linux server or use gcc on local system