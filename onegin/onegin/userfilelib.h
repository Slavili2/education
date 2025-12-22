#pragma once

void openTxtFile(FILE **, char *, const char *);
int countOfStrings(char *);
void createOfText(FILE *, char **);
void createArrayOfStrings(char ***,int);
void printArrayOfStrings(char **, int);
void fillArrayOfStrings(char **, char *);
size_t userStrLen(char *);
void swapTwoElementsOfArray(char **, int, int);
void sortOfArray(char **, char *);
int userStrCmp(char *, char *);
void help();
void menu(char *, char **);
void quit(char *, char **);
void printOriginalText(char *);

typedef enum {
    SHOWSORTED = 's',
    SHOWORIGINAL = 'o',
    QUIT = 'q'
} switchOperations;
