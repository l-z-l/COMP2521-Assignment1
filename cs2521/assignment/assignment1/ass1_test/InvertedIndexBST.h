#include "invertedIndex.h"
#include "FileList.h"
#include "string_manipulate.h"
#include <string.h>
#include <stdlib.h>

// Creating a new node and pointing the left and right to NULL
InvertedIndexBST newInvertedIndexNode(char *str, char *fileName, double tf);
InvertedIndexBST insertNewIndexNode(InvertedIndexBST root, char *str, char *fileName, double tf);
void printInvertedIndexHelper(InvertedIndexBST tree, FILE *fp);