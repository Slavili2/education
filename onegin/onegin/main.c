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
    int cnt = 0;

    openTxtFile(&fPtrUserFile, "onegin.txt", "r+b");
    createOfText(fPtrUserFile, &cUserText);

    fclose(fPtrUserFile);

    countOfStrings(cUserText, &cnt);

    createArrayOfStrings(&cArrayOfStrings, cnt);

    fillArrayOfStrings(&cArrayOfStrings, &cUserText, cnt);

    menu(cUserText, cArrayOfStrings, cnt);

    return 0;
}
