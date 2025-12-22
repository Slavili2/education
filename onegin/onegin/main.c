#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <assert.h>
#include "userfilelib.h"

int main( int argc, char **argv)
{
    system("chcp 1251 > nul");

    char * cUserText;
    char ** cArrayOfStrings;
    FILE * fPtrUserFile;

    openTxtFile(&fPtrUserFile, "onegin.txt", "r+b");
    createOfText(fPtrUserFile, &cUserText);

    fclose(fPtrUserFile);

    createArrayOfStrings(&cArrayOfStrings, countOfStrings(cUserText));

    fillArrayOfStrings(cArrayOfStrings, cUserText);

    sortOfArray(cArrayOfStrings, cUserText);

    menu(cUserText, cArrayOfStrings);

    return 0;
}
