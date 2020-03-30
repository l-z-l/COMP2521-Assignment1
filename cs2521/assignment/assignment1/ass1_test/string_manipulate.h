#define MAX_SIZE 100
#include <stdio.h>
char *new_string(char *str);
// Trim off the space in the beginning and the end of a string
char *spaceTrim(char *str);
// Covert all char to lower case
char *covertLower(char *str);
// Remove the last char if it is a puntuation mark
char *removePunctuation(char *str);
//
double fileWordCount(FILE *fp);
//
double calculateTf(char *wordName, double wordCount, FILE *fp);