/**
@mainpage CS 502 - Homework 03B
@section Description

This program works by asking the user which letter in a sqeuence is the one they
are thinking of and based off Y/N answers builds the word that the user is
thinking.

*/

/**
@file
@author Baran Arig <ba646@drexel.edu>
@date July 20, 2023
@section DESCRIPTION

this is the main file that contains the main function and all functions needed
to make the code run.
*/
#include <math.h>
#include <stdio.h>

/**
read input from user and save it as an input.
@return character array from user input.
*/
char *readFromStdin();

/**
  Do a Binary Search on Sorted Alphabet
  @param h is the array
  @param start is the starting position of the array
  @param stop is the last index to search
  @param word is the character array to hold the finished word
  @param counter is the counter to increment adding words to the word param.
  @return word created through binary search
*/
char *binarySearch(char *h, int start, int stop, char word[100], int counter);

int main(void) {
  char alphabet[29] = " !.abcdefghijklmnopqrstuvwxyz";
  char word[100] = "";
  int maxValue = 29;
  int counter = 0;

  binarySearch(alphabet, 0, maxValue - 1, word, counter);

  printf("You typed:\n");
  printf("%s\n", word);

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

char *binarySearch(char *h, int start, int stop, char word[100], int counter) {
  // printf("binarySearch(%p, %d, %d, %d)\n", h, n, start, stop);

  if (stop < start) {
    // printf("BS: I never found it!!!\n");
    return 0;
  }

  int middle = ceil((start + stop) / 2);

  if (start == stop) {
    printf("Is your letter '%c'? (y/n)\n", h[start]);
  } else {
    printf("Is your letter between '%c' and '%c'? (y/n)\n", h[start],
           h[middle]);
  }

  char *letter = readFromStdin();

  if ((start == stop) && (*letter == 'Y' || *letter == 'y')) {
    if (h[middle] == '!') {
      return word;
    }
    word[counter] = h[middle];
    counter++;
    return binarySearch(h, 0, 28, word, counter);
  } else if (*letter == 'Y' || *letter == 'y') {
    return binarySearch(h, start, middle, word, counter);
  } else {
    return binarySearch(h, middle + 1, stop, word, counter);
  }

  free(letter);
}
