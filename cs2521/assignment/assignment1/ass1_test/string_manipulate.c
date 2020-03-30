#include "string_manipulate.h"
#include "InvertedIndexBST.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

char *new_string(char *str) {
    // remmeber to free this when freeing the tree
    // printf("%lu\n", strlen(str) * sizeof(char));
    char *new_string = malloc(sizeof(strlen(str) * sizeof(char)));
    if (new_string == NULL) {
        fprintf(stderr, "Insufficient memory!\n");
        exit(EXIT_FAILURE);
    }
    strcpy(new_string, str);
    return new_string;
}

char *spaceTrim(char *str) {
    char *end;
    /* skip leading whitespace */
    while (isspace(*str))
    {
        str = str + 1;
    }
    /* remove trailing whitespace */
    end = str + strlen(str) - 1;
    while (end > str && isspace(*end))
    {
        end = end - 1;
    }
    /* write null character */
    *(end + 1) = '\0';
    return str;
}

char *covertLower(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = tolower(str[i]);
    }
    return str;
}

char *removePunctuation(char *str) {
    int length = strlen(str);
    if (str[length - 1] == '.' || str[length - 1] == ',' || str[length - 1] == ';' || str[length - 1] == '?') {
        str[length - 1] = '\0';
    }
    return str;
}
double fileWordCount(FILE *fp) {
    int ch = 0;
    int characters = 0;
    double words = 0;
    while ((ch = fgetc(fp)) != EOF)
    {
        characters++;
        /* Check words */
        if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\0')
            words++;
    }
    /* Increment words and lines for last word */
    if (characters > 0)
    {
        words++;
    }
    return words;
}

double calculateTf(char *wordName, double wordCount, FILE *fp) {
    char tempWord[BUFSIZ];
    // printf("wordCount: %f\n", wordCount);
    double sameCount = 0;
    double totalCount = 0;
    // FILE *fpp = fopen("hello.txt", "a");
    while (fscanf(fp, "%s", tempWord) != EOF) {
        // fprintf(fpp ,"%s %s\n", tempWord, wordName);
        if (strcmp(normaliseWord(tempWord), normaliseWord(wordName)) == 0) {
            sameCount++;
        }
        totalCount++;
        // printf("totalCount: %f, tempWord: %s, target_word: %s, sameCount: %f\n", totalCount, tempWord, wordName, sameCount);
        // fprintf(fpp, "%f\n", sameCount);
    }
    // printf("%f\n", sameCount/totalCount);
    return sameCount/totalCount;
}