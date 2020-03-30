#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "invertedIndex.h"
#include "string_manipulate.h"
// char *covertLower(char *str) {
//     for (int i = 0; str[i] != '\0'; i++) {
//         str[i] = tolower(str[i]);
//     }
//     return str;
// }

// int main(void) {
// //      First experiment
//     char str_1[] = "   HELLO \0";
// //     char *str = str_1;
// //     char *end;
// //     // printf("%lu\n", strlen(str));
// //     /* skip leading whitespace */
// //     while (isspace(*str))
// //     {
// //         str = str + 1;
// //     }
// //     /* remove trailing whitespace */
// //     // printf("%lu\n", strlen(str));
// //     end = str + strlen(str) - 1;
// //     while (end > str && isspace(*end))
// //     {
// //         end = end - 1;
// //     }
// //     /* write null character */
// //     *(end + 1) = '\0';
// //     // printf("%lu\n", strlen(str));
// //     Second Experiment casting all character to lower case
//     printf("%s", covertLower(str_1));
// }
// char *new_string(char *str) {
//     // remmeber to free this when freing the tree
//     char *new_string = malloc(sizeof(strlen(str) * sizeof(char)));
//     if (new_string == NULL) {
//         fprintf(stderr, "Insufficient memory!\n");
//         exit(EXIT_FAILURE);
//     }
//     strcpy(new_string, str);
//     return new_string;
// }

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
    // if (strcmp(filename, start->filename) < 0) {
        
    // } else if (strcmp(filename, start->filename) == 0) {
    //     // change this bit later
    //     start->tf = 0;
    // } else {
    //     start->next = insertFileListNode(start->next, filename);
    // }

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