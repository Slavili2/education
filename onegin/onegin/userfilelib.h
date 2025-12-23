#pragma once

#define ASC 1
#define DESC -1

typedef enum {
    ORDERBYDESCENDING = 'd',
    ORDERBYASCENDING = 'a',
    SHOWORIGINAL = 'o',
    QUIT = 'q'
} switchOperations;

void openTxtFile(FILE **, char *, const char *);
void countOfStrings(char *, int *);
void createOfText(FILE *, char **);
void createArrayOfStrings(char ***,int);
void printArrayOfStrings(char **, int);
void fillArrayOfStrings(char ***, char **, int);
size_t userStrLen(char *);
void swapTwoElementsOfArray(char **, char **);
void sortOfArray(char **, char *, int, int);
int userStrCmp(char *, char *);
void help();
void menu(char *, char **, int);
void quit(char **, char ***);
void printOriginalText(char *);

