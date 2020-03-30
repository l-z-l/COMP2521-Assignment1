#include "string_manipulate.h"
#include "invertedIndex.h"
#include "InvertedIndexBST.h"
#include "FileList.h"
#include <ctype.h>
#include <stdio.h>

double tfIdfSum(double tf, int length, int D);
TfIdfList newTfIdfNode(char *fileName, double tf, int length, int D);
TfIdfList insertTfIdfNode(TfIdfList start, double tfIdfSum, int length, char *fileName, int D);




