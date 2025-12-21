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

    cUserText = createOfText(fPtrUserFile, cUserText);
    fclose(fPtrUserFile);

    printf("%lld\n", strlen(cUserText));
    printf("%d\n", countOfStrings(cUserText));

    cArrayOfStrings = createArrayOfStrings(countOfStrings(cUserText));

    fillArrayOfStrings(cArrayOfStrings, cUserText);

    sortOfArray(cArrayOfStrings, cUserText);

    printf("********************После сортировки***************************\n");
    printArrayOfStrings(cArrayOfStrings, countOfStrings(cUserText));

    free(cUserText);
    free(cArrayOfStrings);


    system("pause > nul");

    return 0;
}
