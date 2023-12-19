/**
@mainpage CS 502 - Homework 03A
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

#include <stdio.h>

/**
read input from user and save it as an input.
@return character array from user input.
*/
char *readFromStdin();

int main(void) {
  char word[100] = "";
  int counter = 0;
  char *letter;
  char alphabet[] = " !.abcdefghijklmnopqrstuvwxyz";
  int reader = 0;
  int done = 0;

  while (done == 0) {
    printf("Are you thinking of the letter '%c'?\n", alphabet[reader]);
    letter = readFromStdin();
    if ((*letter == 'Y' || *letter == 'y') && alphabet[reader] == '!') {
      done = 1;
    } else if (*letter == 'Y' || *letter == 'y') {
      word[counter] = alphabet[reader];
      counter++;
      reader = 0;
    } else {
      reader++;
    }
  }

  printf("You typed:\n");
  printf("%s\n", word);
  free(letter);
  return 0;
}

char *readFromStdin() {
  int bufferSize = 5;
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