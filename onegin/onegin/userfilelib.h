#pragma once

#define ASC 1
#define DESC -1
#define DEFAULT_FILE_NAME "onegin.dat"

typedef enum {
    ORDERBYDESCENDING = 'd',
    ORDERBYASCENDING = 'a',
    SHOWORIGINAL = 'o',
    QUIT = 'q'
} switchOperations;

void openTxtFile(FILE **, char *, const char *);
void createOfText(FILE *, char **, char ***, int *);
void createArrayOfStrings(char ***,_off64_t);
void printArrayOfStrings(char **, int);
size_t userStrLen(char *);
void swapTwoElementsOfArray(char **, char **);
void sortOfArray(char **, char *, int, int);
int userStrCmp(char *, char *);
void help();
void menu(char *, char **, int);
void quit(char **, char ***);
void printOriginalText(char *);

