#pragma once

FILE * openTxtFile(char *, const char *);
int countOfStrings(char *);
char * createOfText(FILE *, char *);
char ** createArrayOfStrings(int);
void printArrayOfStrings(char **, int);
void fillArrayOfStrings(char **, char *);
size_t userStrLen(char *);
void swapTwoElementsOfArray(char **, int, int);
void sortOfArray(char **, char *);
int userStrCmp(char *, char *);
