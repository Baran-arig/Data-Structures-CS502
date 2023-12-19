/**
@mainpage CS 502 - Homework 01B
@section Description

This program takes a user name and calculates the various numerology values such
as Heart's Desire, Personality, and Power number.
*/

/**
@file
@author Baran Arig <ba646@drexel.edu>
@date July 7, 2022
@section DESCRIPTION

this is the main file that contains the main function and all required functions
to make this file run.
*/

#include "stdio.h"
#include <ctype.h>

/**
read input from user and save it as an input.
@return character array from user input.
*/
char *readFromStdin();

/**
converts a string to lowercase letters.
@param str is the string to convert.
@return lowercase string.
*/
char *convertToLower(char *str);

/**
calculates values for all vowels in a string.
@param str is the string to calculate.
@return sum of all vowels as a value less than 10.
*/
int heartsDesire(char *str);

/**
calculates values for all consonents in a string.
@param str is the string to calculate.
@return sum of all consonents as a value less than 10.
*/
int powerNumberFun(char *str);

/**
condenses the value of integer if total sum is greater than 10.
@param i is the integer to condense.
@return condensed value less than 10.
*/
int powerNumberFun2electricBoogaloo(int i);

/**
calculates values for all letters in a string.
@param str is the string to calculate.
@return sum of all letters as a value less than 10.
*/
int personalityNumberFun(char *str);

/**
determines if character is a vowel.
@param c is a character.
@return 0 for failure and 1 for success.
*/
int isVowel(char c);

int main(int argc, char **argv) {

  printf("Enter Your Name:\n");
  char *test = readFromStdin();

  char *lowerCase = convertToLower(test);
  // printf("lowercase is: %s\n", lowerCase);

  int heatNum = heartsDesire(lowerCase);
  printf("Heart's Desire Number: %d\n", heatNum);
  int peersonalityNum = personalityNumberFun(lowerCase);
  printf("Personality Number: %d\n", peersonalityNum);
  int powerfulNumber = powerNumberFun(lowerCase);
  printf("Power Number: %d\n", powerfulNumber);

  free(lowerCase);
  free(test);
  return 0;
}

char *readFromStdin() {
  int bufferSize = 20;
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

char *convertToLower(char *str) {
  int bufferSize = 20;
  char *buffer = malloc(sizeof(char) * bufferSize);
  int pos = 0;

  char c = str[pos];
  while (c != 0) {
    buffer[pos] = tolower(c);
    pos++;
    c = str[pos];
  }

  buffer[pos] = 0;
  pos++;

  return buffer;
}

int heartsDesire(char *str) {
  int pos = 0;
  char c = str[pos];
  int powerNumber = 0;

  int vFlag = 0;
  while (c != 0) {
    if (isVowel(c)) {
      powerNumber += (c - 96) % 9;
      vFlag = 1;
    } else if (c == 'y' && vFlag == 0 && isVowel(str[pos + 1]) == 0) {
      powerNumber += (c - 96) % 9;
    } else {
      vFlag = 0;
    }
    pos++;
    c = str[pos];
  }

  powerNumber = powerNumberFun2electricBoogaloo(powerNumber);

  return powerNumber;
}

int powerNumberFun(char *str) {
  int pos = 0;
  char c = str[pos];
  int powerNumber = 0;

  while (c != 0) {
    powerNumber += (c - 96) % 9;
    pos++;
    c = str[pos];
  }

  powerNumber = powerNumberFun2electricBoogaloo(powerNumber);

  return powerNumber;
}

int personalityNumberFun(char *str) {
  int pos = 0;
  char c = str[pos];
  int powerNumber = 0;

  int vFlag = 0;
  while (c != 0) {
    if (isVowel(c)) {
      vFlag = 1;
    } else if (c == 'y' && vFlag == 0 && isVowel(str[pos + 1]) == 0) {

    } else {
      powerNumber += (c - 96) % 9;
      vFlag = 0;
    }
    pos++;
    c = str[pos];
  }

  powerNumber = powerNumberFun2electricBoogaloo(powerNumber);

  return powerNumber;
}

int powerNumberFun2electricBoogaloo(int i) {
  int ret = 0;
  while (i > 0) {
    ret += i % 10;
    i = i / 10;
  }
  if (ret >= 10) {
    ret = powerNumberFun2electricBoogaloo(ret);
  }

  return ret;
}

int isVowel(char c) {
  if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
    return 1;
  }
  return 0;
}