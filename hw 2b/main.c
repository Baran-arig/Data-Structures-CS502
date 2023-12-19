/**
@mainpage CS 502 - Homework 02B
@section Description

This program works by reading in a file name from the user and then reading the
file character by character and indicating the position by column number and
line number. It will tell the user what kind of character is at each location.

*/

/**
@file
@author Baran Arig <ba646@drexel.edu>
@date July 14, 2023
@section DESCRIPTION

this is the main file that contains the main function and all functions needed
to make the code run.
*/

#include <ctype.h>
#include <stdio.h>

/**
read input from user and save it as an input.
@return character array from user input.
*/
char *readFromStdin();

int main(void) {

  FILE *fptr;
  char ch;
  int lineNumber = 1;
  int colNumber = 1;

  printf("Enter File Name:\n");
  char *filename = readFromStdin();
  char singleLine[150];
  printf("Opening File: %s\n", filename);
  fptr = fopen(filename, "r");

  while ((ch = fgetc(fptr)) != EOF) {
    printf("Line %d Col %d has ASCII Code %d which is a ", lineNumber,
           colNumber, ch);

    if (isupper(ch)) {
      printf("Upper Case Letter.\n");
    } else if (islower(ch)) {
      printf("Lower Case Letter.\n");
    } else if (ch >= 48 && ch <= 57) {
      printf("Digit.\n");
    } else if (ch == ' ') {
      printf("Space.\n");
    } else if (ch == '\n') {
      printf("Newline.\n");
      lineNumber++;
      colNumber = 0;
    } else {
      printf("Symbol.\n");
    }
    colNumber++;
  }

  fclose(fptr);
  free(filename);
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