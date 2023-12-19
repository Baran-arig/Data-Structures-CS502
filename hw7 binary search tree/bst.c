/**
        @file
        @author Baran Arig <ba646@drexel.edu>
        @date August 18, 2022
        @section DESCRIPTION

        This is a the file that implements the functions outlined in bst.h for a
   Binary Search Tree Class.
 */

#include "bst.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/**
        Create a new node.
        @param newVal the value to store in the new node.
        @return the created node.
 */
Node *makeNewNode(int newVal);

BST *newBST() {
  BST *t = malloc(sizeof(BST));
  t->root = NULL;
  return t;
}

void deleteBST(BST *T) { free(T); }

void insert(BST *T, int target) { T->root = insertValue(target, T->root); }

char find(BST *T, int target) { return findValue(target, T->root); }

void deleteFromTree(BST *T, int target) {
  T->root = deleteValue(target, T->root);
}

int min(BST *T) { return findMin(T->root); }

void inorder(BST *T) {
  // printf("Inorder:\n");
  inorderWalker(T->root);
  printf("\n");
}

void preorder(BST *T) {
  // printf("Preorder:\n");
  preorderWalker(T->root);
  printf("\n");
}

void postorder(BST *T) {
  // printf("Postorder:\n");
  postorderWalker(T->root);
  printf("\n");
}

int height(BST *T) { return nodeHeight(T->root); }

void inorderWalker(Node *current) {
  if (current == NULL) {
    return;
  }
  inorderWalker(current->left);
  printf("%d ", current->value);
  inorderWalker(current->right);
}

void preorderWalker(Node *current) {
  if (current == NULL) {
    return;
  }

  printf("%d ", current->value);
  preorderWalker(current->left);
  preorderWalker(current->right);
}

void postorderWalker(Node *current) {
  if (current == NULL) {
    return;
  }
  postorderWalker(current->left);
  postorderWalker(current->right);
  printf("%d ", current->value);
}

Node *makeNewNode(int newVal) {
  Node *newNode = malloc(sizeof(Node));
  newNode->value = newVal;
  newNode->left = NULL;
  newNode->right = NULL;
  return newNode;
}

Node *insertValue(int target, Node *current) {
  if (current == NULL) {
    return makeNewNode(target);
  }
  if (current->value == target) {
    return current;
  }
  if (current->value > target) {
    current->left = insertValue(target, current->left);
  } else {
    current->right = insertValue(target, current->right);
  }
  return current;
}

char findValue(int target, Node *current) {
  if (current == NULL) {
    return false;
  }
  if (current->value == target) {
    return true;
  }
  if (current->value > target) {
    return findValue(target, current->left);
  }
  return findValue(target, current->right);
}

int findMin(Node *current) {
  if (current == NULL) {
    return -1;
  }
  if (current->left == NULL) {
    return current->value;
  }
  return findMin(current->left);
}

int nodeHeight(Node *current) {
  if (current == NULL) {
    return -1;
  }
  int leftHeight = nodeHeight(current->left);
  int rightHeight = nodeHeight(current->right);

  if (leftHeight > rightHeight) {
    return leftHeight + 1;
  } else {
    return rightHeight + 1;
  }
}

Node *deleteValue(int target, Node *current) {
  if (current == NULL) {
    return NULL;
  }
  if (current->value == target) {
    return deleteNode(current);
  }
  if (current->value > target) {
    current->left = deleteValue(target, current->left);
  } else {
    current->right = deleteValue(target, current->right);
  }
  return current;
}

Node *deleteNode(Node *current) {
  if (current->left == NULL) {
    return current->right;
  }
  if (current->right == NULL) {
    return current->left;
  }
  int minVal = findMin(current->right);
  current->value = minVal;
  current->right = deleteValue(minVal, current->right);
  return current;
}
