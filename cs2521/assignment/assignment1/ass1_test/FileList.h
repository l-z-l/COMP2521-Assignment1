#include "invertedIndex.h"
#include <stdio.h>
// Create a new file_list node
FileList newFileListNode(char *str, double tf);

// insertFileListNode inorder
FileList insertFileListNode(FileList start, char *filename, double tf);
// Print the linked list out recursively
void printFileList(FileList start, FILE *fp);
// give the length of the list
int lengthFileList(FileList start);