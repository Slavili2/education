#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <assert.h>
#include "userfilelib.h"

int main( int argc, char **argv)
{
    system("chcp 1251 > nul");
    // доделать!!!
    char * fileNamePath = (char *)calloc(512, sizeof(char));

    if(argc == 1)
        strcat(fileNamePath, DEFAULT_FILE_NAME);
    else if(argc == 2)
        strcat(fileNamePath, *(argv + 1));

    char * param = "r+b";
    char * cUserText;
    char ** cArrayOfStrings;
    FILE * fPtrUserFile;
    int cnt = 0;

    openTxtFile(&fPtrUserFile, fileNamePath, param);
    createOfText(fPtrUserFile, &cUserText, &cArrayOfStrings, &cnt);

    fclose(fPtrUserFile);

    menu(cUserText, cArrayOfStrings, cnt);

    return 0;
}
