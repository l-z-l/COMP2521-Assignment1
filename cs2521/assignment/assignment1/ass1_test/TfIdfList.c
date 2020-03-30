#include "string_manipulate.h"
#include "invertedIndex.h"
#include "InvertedIndexBST.h"
#include "FileList.h"
#include <ctype.h>
#include <stdio.h>
#include <math.h>
// This function returns an ordered list where each node contains a filename and the corresponding tf-idf value for a given searchWord.
// You only need to include documents (files) that contain the given searchWord. The list must be in descending order of tf-idf value.
// If there are multple files with same tf-idf value, order them by their filename in ascending order.

// struct TfIdfNode {
// 	char *filename;
// 	double tfIdfSum; // tfidf sum value
// 	struct TfIdfNode *next;
// };
// I will tf and the length list and then the D
double tfIdfSum(double tf, int length, int D) {
    double Idf = log10(((double)D/ (double)length));
    return tf * Idf;
}

TfIdfList newTfIdfNode(char *fileName, double tf, int length, int D) {
    TfIdfList n = malloc(sizeof(*n));
    // strdup malloc the space for string and copy th
    if (n == NULL) {
        fprintf(stderr, "Insufficient memory!\n");
        exit(EXIT_FAILURE);
    }
    n->filename = new_string(fileName);
    // Need to care about this later
    n->tfIdfSum = tfIdfSum(tf, length, D);
    n->next = NULL;
    return n;
}
// maybe change passing in the length of the filelist instead of the start of the filelist
TfIdfList insertTfIdfNode(TfIdfList start, double tf, int length, char *fileName, int D) {
    // printf("filename: %s\n", fileName);
    TfIdfList new = newTfIdfNode(fileName, tf, length, D);
    if (start == NULL) {
        // printf("1\n");
        return new;
    }
    double newTfIdfSum = tfIdfSum(tf, length, D);
    if (start->tfIdfSum < newTfIdfSum) {
        // printf("2\n");
        new->next = start;
        return new;
    } else if (newTfIdfSum == start->tfIdfSum) {
        // printf("3\n");
        // didn't check the equal case cuase it shouldn't exist
        // No filelist node should have the same filename
        if (strcmp(fileName, start->filename) < 0) {
            // printf("A\n");
            new->next = start;
            return new;
        } else {
            // printf("B\n");
            start->next = insertTfIdfNode(start->next, tf, length, fileName, D);
            return start;
        }
    } else {
        // printf("4\n");
        start->next = insertTfIdfNode(start->next, tf, length, fileName, D);
        return start;
    }
}
// Remember to free the new n=node before recurrsion