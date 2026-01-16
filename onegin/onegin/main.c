#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <assert.h>
#include "userfilelib.h"

int main( int argc, char **argv)
{
    system("chcp 1251 > nul");

    char * fileNamePath = NULL;
    char * param = "r+b";
    char * cUserText;
    char ** cArrayOfStrings;
    FILE * fPtrUserFile;
    int cnt = 0;

    createFileNamePath(&fileNamePath, &argv, argc);

    openTxtFile(&fPtrUserFile, fileNamePath, param);
    createOfText(fPtrUserFile, &cUserText, &cArrayOfStrings, &cnt);
    fclose(fPtrUserFile);

    menu(cUserText, cArrayOfStrings, &fileNamePath, cnt);

    return 0;
}
