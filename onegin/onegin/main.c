#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <assert.h>
#include "userfilelib.h"

int main( int argc, char **argv)
{
    system("chcp 1251 > nul");

    FILE * fPtrUserFile = openTxtFile("onegin.txt", "r+b");

    char * cUserText;
    char ** cArrayOfStrings;

    cUserText = createOfText(fPtrUserFile);
    fclose(fPtrUserFile);

    cArrayOfStrings = createArrayOfStrings(countOfStrings(cUserText));

    fillArrayOfStrings(cArrayOfStrings, cUserText);

    sortOfArray(cArrayOfStrings, cUserText);

    menu(cUserText, cArrayOfStrings);


    return 0;
}
