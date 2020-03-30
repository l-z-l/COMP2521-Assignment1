#include "string_manipulate.h"
#include "invertedIndex.h"
#include "InvertedIndexBST.h"
#include "FileList.h"
#include "TfIdfList.h"
#include <ctype.h>
#include <stdio.h>
char *normaliseWord(char *str) {
    // Trimming leading and trailling space
    str = spaceTrim(str);
    // Casting all character to lower case
    str = covertLower(str);
    // Removing the last punctuation char in the string
    str = removePunctuation(str);
    return str;
}
InvertedIndexBST generateInvertedIndex(char *collectionFilename) {
    // breaking all these up into a list of strings and then pass it to the normalizeWord function
    InvertedIndexBST root = NULL;
    FILE *fp = fopen(collectionFilename, "r");
    if (fp == NULL)
    {
        printf("\nUnable to open file.\n");
        printf("Please check if file exists and you have read privilege.\n");

        exit(EXIT_FAILURE);
    }
    char file_name[BUFSIZ];
    // Now I will need to read each individual file
    while (fscanf(fp, "%s", file_name) != EOF) {
        FILE *fp_1 = fopen(file_name, "r");
        FILE *fp_2 = fopen(file_name, "r");
        if (fp_1 == NULL || fp_2 == NULL) {
            printf("\nUnable to open file.\n");
            printf("Please check if file exists and you have read privilege.\n");
            exit(EXIT_FAILURE);
        }
        double word_count = fileWordCount(fp_2);
        char word_name[BUFSIZ];
        while (fscanf(fp_1, "%s", word_name) != EOF) {
            printf("filename: %s\n", file_name);
            fp_2 = fopen(file_name, "r");
            double tf = calculateTf(word_name, word_count, fp_2);
            root = insertNewIndexNode(root, normaliseWord(word_name), file_name, tf);
        }
    }
    return root;
}

void printInvertedIndex(InvertedIndexBST tree) {
    FILE *fp = fopen("invertedIndex.txt", "w");
    printInvertedIndexHelper(tree, fp);
    fclose(fp);
}

TfIdfList calculateTfIdf(InvertedIndexBST tree, char *searchWord, int D) {
    if (tree == NULL) {
        return NULL;
    }
    if (strcmp(searchWord, tree->word) < 0) {
        return calculateTfIdf(tree->left, searchWord, D);
    } else if (strcmp(searchWord, tree->word) > 0) {
        return calculateTfIdf(tree->right, searchWord, D);
    } else {
        // the case where it equals to zero
        FileList tmp = tree->fileList;
        TfIdfList start = NULL;
        int length = lengthFileList(tree->fileList);
        // TfIdfList new = NULL;
        while (tmp != NULL) {
            start = insertTfIdfNode(start, tmp->tf, length, tmp->filename, D);
            tmp = tmp->next;
        }
        // TfIdfList start = NULL;
        // int length = lengthFileList(tree->fileList);
        // TfIdfList new = insertTfIdfNode(start, tree->fileList->tf, length, tree->fileList->filename, D);
        return start;
    }
}


