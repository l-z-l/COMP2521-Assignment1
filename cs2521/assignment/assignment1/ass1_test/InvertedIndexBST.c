#include "InvertedIndexBST.h"
#include "invertedIndex.h"
#include "FileList.h"
#include "string_manipulate.h"
#include <string.h>
#include <stdlib.h> // this include EXIT_FAILURE

InvertedIndexBST newInvertedIndexNode(char *str, char *fileName, double tf) {
    InvertedIndexBST n = malloc(sizeof(*n));
    // Inspired Lab week04 Treecopy
    if (n == NULL) {
        fprintf(stderr, "Insufficient memory!\n");
        exit(EXIT_FAILURE);
    }
    n->word = new_string(str);
    n->fileList = insertFileListNode(n->fileList, fileName, tf);
    n->left = NULL;
    n->right = NULL;
    return n;
}
InvertedIndexBST insertNewIndexNode(InvertedIndexBST root, char *str, char *fileName, double tf) {
    if (root == NULL) {
        root = newInvertedIndexNode(str, fileName, tf);
        return root;
    }
    // Moving to the left
    if (strcmp(str, root->word) < 0) {
        root->left = insertNewIndexNode(root->left, str, fileName, tf);
    } else if (strcmp(str, root->word) > 0) {
        root->right = insertNewIndexNode(root->right, str, fileName, tf);
    } else {
        // The case where the word is already in the tree
        root->fileList = insertFileListNode(root->fileList, fileName, tf);
    }
    return root;
}

void printInvertedIndexHelper(InvertedIndexBST tree, FILE *fp) {
    if (tree == NULL) {
		return;
    } else {
        printInvertedIndexHelper(tree->left, fp);
		fprintf(fp, "%s ", tree->word);
		// fprintf(fp, "%f ", tree->fileList->tf);
        printFileList(tree->fileList, fp);
        printInvertedIndexHelper(tree->right, fp);
    }
}


