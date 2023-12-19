/**
        @file
        @author Mark Boady <mwb33@drexel.edu>
        @date August 9, 2022
        @section DESCRIPTION

        Run three different types of tests on the BST
 */

//---ONLY EDIT FUNCTION heightExperiments---
//---Make no other changes---

#include "bst.h"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"

/**
        Ask user for a list of numbers. Test BST with them.
 */
void inputTest();

/**
        Generate Random Trees and test heights. Print table of resuts.
*/
void heightExperiments();
/**
        Find Minimum in an Array
        @param A is the array to search
        @param size is the array size
        @return The minimum element in array
 */
int minV(int *A, int size);
/**
        Find Maximum in an Array
        @param A is the array to search
        @param size is the array size
        @return The max element in array
 */
int maxV(int *A, int size);
/**
        Read an integer from stdin. Consumes all characters till newline
        @return Integer read
 */
int readNumber();
/**
        Test file for student BST code
        @param argc not used
        @param argv not used
        @return 0 on success and 1 on bad input
 */
int main(int argc, char **argv) {
  // Set random number generator
  srand(time(NULL));
  // Users has two options
  printf("Select Option:\n");
  printf("1.) Enter Tree Values and print tree.\n");
  printf("2.) Run Height Experiments.\n");
  // Read the users answer
  int r = readNumber();
  if (r < 1 || r > 2) {
    printf("Bad Input. Try Again.\n");
    return 1;
  }
  if (r == 1) {
    inputTest();
    return 0;
  }
  if (r == 2) {
    heightExperiments();
    return 0;
  }
  return 0;
}

// Get an array of numbers from user.
// Insert, Find and Delete All of them.
void inputTest() {
  // Ask for Size (assume good input)
  printf("Enter Number of Values to Test:\n");
  int testSize = readNumber();
  // read values
  int *A = malloc(sizeof(int) * testSize);
  for (int i = 0; i < testSize; i++) {
    printf("Enter A[%d] value:\n", i);
    A[i] = readNumber();
  }
  // First, make an empty tree
  BST *B = newBST();
  // Insert some numbers to make an expected tree
  for (int i = 0; i < testSize; i++) {
    insert(B, A[i]);
    printf("Inserted %d into tree\n", A[i]);
    printf("Preorder:\n");
    preorder(B);
    printf("Inorder:\n");
    inorder(B);
    printf("Postorder:\n");
    postorder(B);
  }
  // Check the height
  printf("The Tree Height is %d\n", height(B));
  // Check find
  int smallest = minV(A, testSize);
  int largest = maxV(A, testSize);
  for (int i = smallest - 1; i < largest + 1; i++) {
    printf("Is %d in the tree?\n", i);
    printf("Answer: %d\n", find(B, i));
  }
  // Delete the values in order
  for (int i = 0; i < testSize; i++) {
    deleteFromTree(B, A[i]);
    printf("Delete %d from tree\n", A[i]);
    printf("Preorder:\n");
    preorder(B);
    printf("Inorder:\n");
    inorder(B);
    printf("Postorder:\n");
    postorder(B);
  }

  // Clear Memory
  deleteBST(B);
  return;
}

int minV(int *A, int size) {
  int myMin = 9999;
  for (int i = 0; i < size; i++) {
    if (A[i] < myMin) {
      myMin = A[i];
    }
  }
  return myMin;
}
int maxV(int *A, int size) {
  int myMax = -9999;
  for (int i = 0; i < size; i++) {
    if (A[i] > myMax) {
      myMax = A[i];
    }
  }
  return myMax;
}

// Read a number from STDIN
int readNumber() {
  int number = 0;
  char c = getchar();
  while (c != '\n') {
    number = number * 10 + (c - 48);
    c = getchar();
  }
  return number;
}

// Students must implement this function
void heightExperiments() {
  printf("Experiments (N=Number Element, Table Shows Height)\n");
  printf("| %2s | %2s | %2s | %2s | %2s | %2s | %2s |\n", "N", "T1", "T2", "T3",
         "T4", "T5", "Average");
  // printf("|-------|----------|\n");

  BST *tree1 = newBST();
  BST *tree2 = newBST();
  BST *tree3 = newBST();
  BST *tree4 = newBST();
  BST *tree5 = newBST();

  for (int n = 1; n <= 10; n++) {
    int elements = 1;
    for(int j = 0; j<n; j++){
      elements *= 2;
    }

    for (int i = 0; i < elements; i++) {
      int randomValue = rand(); // % 100;
      insert(tree1, randomValue);
    }

    for (int i = 0; i < elements; i++) {
      int randomValue2 = rand(); // % 100;
      insert(tree2, randomValue2);
    }

    for (int i = 0; i < elements; i++) {
      int randomValue3 = rand(); // % 100;
      insert(tree3, randomValue3);
    }

    for (int i = 0; i < elements; i++) {
      int randomValue4 = rand(); // % 100;
      insert(tree4, randomValue4);
    }

    for (int i = 0; i < elements; i++) {
      int randomValue5 = rand(); // % 100;
      insert(tree5, randomValue5);
    }

    int treeHeight1 = height(tree1);
    int treeHeight2 = height(tree2);
    int treeHeight3 = height(tree3);
    int treeHeight4 = height(tree4);
    int treeHeight5 = height(tree5);

    double averageHeight = (double)(treeHeight1 + treeHeight2 + treeHeight3 +
                                    treeHeight4 + treeHeight5) /
                           5;

    printf("| %2d | %2d | %2d | %2d | %2d | %2d | %2f |\n", elements,
           treeHeight1, treeHeight2, treeHeight3, treeHeight4, treeHeight5,
           averageHeight);
  }
  deleteBST(tree1);
  deleteBST(tree2);
  deleteBST(tree3);
  deleteBST(tree4);
  deleteBST(tree5);
}
