
/**
@mainpage CS 502 - Homework 01A
@section Description

This program works by reading in a user inputed Zip code as a character array. Then it converts the character array to an integer. Afterwards it finds the last digit in the zip code, saves it to a value and then chops off the last digit from the zip code. This process is repeated until the entire zipcode is converted to single digits. AFterwards the digits are all summed up to determine the checksum and that value is recorded as well. Then all of those values are fed to createBarcode where the numeric values are convereted to barcode. 

*/

/**
@file
@author Baran Arig <ba646@drexel.edu>
@date July 5, 2023
@section DESCRIPTION

this is the main file that contains the main function and all functions needed to make the code run. 
*/




#include "stdio.h"
#include "stdlib.h"

/**
read input from user and save it as an input. 
@return character array from user input. 
*/
char* readFromStdin();

/**
verifies that the parameter is an integer and that is it exactly 5 characters long. 
@param str is the character array input from the user. 
@return 1 for success and 0 for failure. 
*/
char isIntegerAndFiveLong(char* str);

/**
converts the string to an integer. 
@param str user input string, which is saved as a character array. 
@return result of string being converted to integer. 
*/
int strToInteger(char* str);

/**
find the last digit in a number
@param x is the integer whose last number is attempting to be found. 
@return last digit in integer. 
*/
int findNthDigit(int x);

/**
chops off the last digit in a number.
@param x is the integer whose last number needs to be chopped
@return integer with last digit removed.  
*/
int chopLastDigit(int x);

/**
sums all the values given and then determines what value needs to be added to the sum to get value to next multiple of 10. 
@param a is digit 1.
@param b is digit 2.
@param c is digit 3.
@param d is digit 4.
@param e is digit 5.
@return integer needed to reach next multiple of 10.  
*/
int findChecksum(int a, int b, int c, int d, int e);

/**
converts input numbers into barcode. 
@param a is digit 1.
@param b is digit 2.
@param c is digit 3.
@param d is digit 4.
@param e is digit 5.
@param checkSum is the integer needed to reach next multiple of 10. 
@return numbers converted to barcode.   
*/
char* createBarcode(int a, int b, int c, int d, int e, int checkSum);
 

int main(int argc, char** argv) {
  
  printf("Enter Zip Code:\n");
  char* test = readFromStdin();
  //int x = getInteger();
  if(!isIntegerAndFiveLong(test)){
    printf("Bad Zip Code \n");
    free(test);
    return 1;
  }

  
  int a = strToInteger(test);
  int digitFive = findNthDigit(a);
  //printf("the fifth digit is: %d\n", digitFive);
  int b = chopLastDigit(a);
  int digitFour = findNthDigit(b);
  //printf("the fourth digit is: %d\n", digitFour);
  int c = chopLastDigit(b);
  int digitThree = findNthDigit(c);
  //printf("the third digit is: %d\n", digitThree);

  int d = chopLastDigit(c);
  int digitTwo = findNthDigit(d);
 // printf("the second digit is: %d\n", digitTwo);

  int e = chopLastDigit(d);
  int digitOne = findNthDigit(e);
 // printf("the first digit is: %d\n", digitOne);

  int checkSum = findChecksum(digitOne, digitTwo, digitThree, digitFour, digitFive);
  //printf("the sum of all digits is: %d\n", digitOne+ digitTwo+ digitThree+ digitFour+ digitFive);
  //printf("the checksum is: %d\n", checkSum);

  char* output = createBarcode(digitOne,digitTwo,digitThree,digitFour,digitFive,checkSum);

  printf("%s\n", output);
  //printf("2 * %d = %d\n",a,2*a);

  free(test);
  free(output);



 // printf("entered number is: %d", myNum);

  
  return 0;
}


char* readFromStdin(){
  int bufferSize = 5;
  char* buffer = malloc(sizeof(char)*bufferSize);
  int position = 0;

  char temp;
  temp = getchar();
  while(temp != EOF && temp != '\n'){
    buffer[position]=temp;
    temp = getchar();
    position++;
  }

  buffer[position]=0;
  position++;

  return buffer;
}

char isIntegerAndFiveLong(char* str){
  int pos=0;
  char c = str[pos];

  while(c != 0){
    if (c<48 || c>57){
      return 0;
    }
    pos++;
    c = str[pos];
  }

  if(pos != 5){
    return 0;
  }
  return 1;
}

int strToInteger(char* str){
  int pos=0;
  int result = 0;

  char c = str[pos];

  while(c!=0){
    int digit = c-48;
    result = result*10 + digit;
    pos++;
    c = str[pos];
  }
  return result;
}


int findNthDigit(int x){
  int num = x;
  int nthDigit = num % 10;

  return nthDigit;
}

int chopLastDigit(int x){
  int num = x;
  num = num/10; 
  return num; 
}

int findChecksum(int a, int b, int c, int d, int e){
  int sum = a+b+c+d+e;
  int lastDigit = sum%10;
  int checkSum = 10 - lastDigit;
  if(checkSum ==10){
    checkSum = 0;
  }

  return checkSum;
}


char* createBarcode(int a, int b, int c, int d, int e, int checkSum){
  int bufferSize = 32; // 6 numbers with 5 charactes each and then a line at start and end. 
  char* barcode = malloc(sizeof(char)*bufferSize);
  int values[6] = {a,b,c,d,e,checkSum};

  int valuePos = 0;
  int pos = 0;

  barcode[0] = '|';
  
  pos++;

  while(pos != bufferSize-1){
    
    switch(values[valuePos]){
      case 1:
        for(int i=0; i<3; i++){
          barcode[pos] = '.';
          pos++;
        }
  
        for(int j =0; j<2; j++){
          barcode[pos] = '|';
          pos++;
        }
        valuePos++;
        break;

      case 2:
        for(int k=0; k<2; k++){
          barcode[pos] = '.';
          pos++;
        }
        
        barcode[pos] = '|';
        pos++;

        barcode[pos] = '.';
        pos++;

        barcode[pos] = '|';
        pos++;

        valuePos++;
        break;

      case 3:
        for(int i=0; i<2; i++){
          barcode[pos] = '.';
          pos++;
        }

        for(int j=0; j<2; j++){
            barcode[pos] = '|';
            pos++;
          }

        barcode[pos] = '.';
        pos++;

        valuePos++;
        break;

      default:
        break;

      case 4:
        barcode[pos] = '.';
        pos++;

        barcode[pos] = '|';
        pos++;
        
        for(int i=0; i<2; i++){
          barcode[pos] = '.';
          pos++;
        }

        barcode[pos] = '|';
        pos++;

        valuePos++;
        break;

      case 5:

        barcode[pos] = '.';
        pos++;

        barcode[pos] = '|';
        pos++;

        barcode[pos] = '.';
        pos++;

        barcode[pos] = '|';
        pos++;

        barcode[pos] = '.';
        pos++;

        valuePos++;
        break;

      case 6:

        barcode[pos] = '.';
        pos++;

        for(int j=0; j<2; j++){
            barcode[pos] = '|';
            pos++;
          }

        for(int i=0; i<2; i++){
          barcode[pos] = '.';
          pos++;
        }

        valuePos++;
        break;      
        

      case 7:
        
        barcode[pos] = '|';
        pos++;
        
        for(int i=0; i<3; i++){
          barcode[pos] = '.';
          pos++;
        }

        barcode[pos] = '|';
        pos++;

        valuePos++;
        break;    

      case 8:
        
        barcode[pos] = '|';
        pos++;

        for(int i=0; i<2; i++){
          barcode[pos] = '.';
          pos++;
        }

        barcode[pos] = '|';
        pos++;

        barcode[pos] = '.';
        pos++;

        valuePos++;
        break; 

      case 9:

        barcode[pos] = '|';
        pos++;

        barcode[pos] = '.';
        pos++;

        barcode[pos] = '|';
        pos++;

        for(int i=0; i<2; i++){
          barcode[pos] = '.';
          pos++;
        }

        valuePos++;
        break; 

      case 0:

        for(int i=0; i<2; i++){
          barcode[pos] = '|';
          pos++;
        }

        for(int j=0; j<3; j++){
          barcode[pos] = '.';
          pos++;
        }
      
        valuePos++;
        break; 
      
    }
  }

  barcode[bufferSize-1] = '|';
  
    return barcode;
}

