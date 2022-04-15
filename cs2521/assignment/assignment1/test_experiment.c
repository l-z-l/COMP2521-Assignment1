#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "invertedIndex.h"
#include "string_manipulate.h"

FileList newFileListNode(char *str) {
    FileList n = malloc(sizeof(*n));
    // strdup malloc the space for string and copy th
    if (n == NULL) {
        fprintf(stderr, "Insufficient memory!\n");
        exit(EXIT_FAILURE);
    }
    n->filename = new_string(str);
    // Need to care about this later
    n->tf = 0;
    n->next = NULL;
    return n;
}
FileList insertFileListNode(FileList start, char *filename) {
    if (start == NULL) {
        return newFileListNode(filename);
    } 
    if (strcmp(filename, start->filename) < 0) {
        FileList new = newFileListNode(filename);
        new->next = start;
        return new;
    } else if (strcmp(filename, start->filename) == 0) {   
        return start;
    } else if (strcmp(filename, start->filename) > 0) {
        start->next = insertFileListNode(start->next, filename);
        return start;
    }
    return start;
}


int main(void) {
    char filename[BUFSIZ];
    FileList start = NULL;
    start = newFileListNode("d");
    printf("Insert names :\n");
    while (scanf("%s", filename) != EOF) {
        // printf("print %s\n", filename);
        // FileList new_node = newFileListNode(filename);
        start = insertFileListNode(start, filename);
        printf("Insert names :");
    }
    FileList tmp = start;
    printf("\n");
    while (tmp != NULL) {
        printf("%s ", tmp->filename);
        tmp = tmp->next;
    }
}
