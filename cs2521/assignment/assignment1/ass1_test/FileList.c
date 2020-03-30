#include "FileList.h"
#include "invertedIndex.h"
#include "string_manipulate.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h> // this include EXIT_FAILURE
FileList newFileListNode(char *str, double tf) {
    FileList n = malloc(sizeof(*n));
    // strdup malloc the space for string and copy th
    if (n == NULL) {
        fprintf(stderr, "Insufficient memory!\n");
        exit(EXIT_FAILURE);
    }
    n->filename = new_string(str);
    // Need to care about this later
    n->tf = tf;
    n->next = NULL;
    return n;
}

FileList insertFileListNode(FileList start, char *filename, double tf) {
    // two base cases at the starts
    if (start == NULL) {
        return newFileListNode(filename, tf);
    } 
    if (strcmp(filename, start->filename) < 0) {
        FileList new = newFileListNode(filename, tf);
        new->next = start;
        return new;
    } else if (strcmp(filename, start->filename) == 0) {   
        return start;
    } else {
        // recursive statement
        start->next = insertFileListNode(start->next, filename, tf);
        return start;
    }
}


void printFileList(FileList start, FILE *fp) {
    if (start == NULL) {
        return;
    }
    if (start->next == NULL) {
        fprintf(fp, "%s \n", start->filename);
    } else {
        fprintf(fp, "%s ", start->filename);
        printFileList(start->next, fp);       
    }
}

int lengthFileList(FileList start) {
    if (start == NULL) {
        return 0;
    }
    return 1 + lengthFileList(start->next);
}
// how do you do this if your new node does not include insertion