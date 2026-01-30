#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "userfilelib.h"

void openTxtFile(FILE ** ptrFile, char * cNameFile, const char * param)
{
    *ptrFile = fopen64(cNameFile, param);
    if(NULL == *ptrFile){
        printf("File don't open!\n");
        abort();
    }
}

void createOfText(FILE * fPtrTempFile, char ** cPtrTempArray, char *** cArrayOfStrings, int * cnt)
{
    _off64_t sizeOfArray = 0;
    char cBuffer = 0;
    fseeko64(fPtrTempFile, 0, SEEK_END);
    sizeOfArray = ftello64(fPtrTempFile);

    createArrayOfStrings(cArrayOfStrings, sizeOfArray);
    createArrayOfOriginalText(cPtrTempArray, sizeOfArray + 1);

    rewind(fPtrTempFile);

    for(_off64_t i = 0, j = (sizeOfArray + 1); i < j && 1 == fread(&cBuffer, sizeof(char), 1, fPtrTempFile) ; i++){
        *(*cPtrTempArray+i) = cBuffer;
        if(0 == i)
            *(*cArrayOfStrings + ((*cnt)++)) = (*cPtrTempArray+i);
        else if('\n' == cBuffer){
            *(*cArrayOfStrings + ((*cnt)++)) = (*cPtrTempArray+i+1);
            *(*cPtrTempArray+i) = '\0';
        }
    }

    reallocArray(cArrayOfStrings, *cnt);
}


void reallocArray(char *** tempArray, int sizeOfArray)
{
    *tempArray=(char **)realloc( (void **)*tempArray, sizeOfArray * sizeof(char *));
    if(NULL == *tempArray){
        printf("Error: unable to allocate memory!\n");
        abort();
    }
}


void createArrayOfOriginalText(char ** tempText, _off64_t sizeOfArray)

{
    *tempText = (char *)calloc(sizeOfArray, sizeof(char ));
    if(NULL == *tempText){
        printf("Error: unable to allocate memory!\n");
        abort();
    }
}


void createArrayOfStrings(char *** tempArray, _off64_t sizeOfArray)
{
    *tempArray = (char **)calloc(sizeOfArray, sizeof(char *));
    if(NULL == *tempArray){
        printf("Error: unable to allocate memory!\n");
        abort();
    }
}

size_t userStrLen(char * userString)
{
    size_t temp = 0;
    for(size_t i = 0; *(userString + i) != '\0' && *(userString + i) != '\n'; temp++, i++);
    return temp;
}


void printArrayOfStrings(char ** cTempArray, int sizeOfArray)
{
    for(long long int i = 0; i < sizeOfArray; i++){
        printf("%s\n",  *(cTempArray+i) );
    }
}

void swapTwoElementsOfArray(char ** firstElement, char ** secondElement)
{
    char * swap = *firstElement;
    *firstElement = *secondElement;
    *secondElement = swap;
}


int userStrCmp(char * str1, char * str2)
{
    size_t i = 0;
    int result = 0;
    while( *(str1+i)!='\0' && *(str1+i)!='\n' && *(str2+i)!='\0' && *(str2+i)!='\n'){
        if(*(str1+i) < *(str2+i)){
            result = -1;
            break;
        }
        else if(*(str1+i) > *(str2+i)){
            result = 1;
            break;
        }
        i++;
    }

    if(0 == result){
        if( userStrLen(str2) > userStrLen(str1))
            result = -1;
        else if( userStrLen(str2) < userStrLen(str1) )
            result = 1;
    }

    return result;
}

void sortOfArray(char ** userArray, char * userText, int iOrderBy, int cnt)
{
    for(int i = 0; i < (cnt - 1); i++){
        for(int j = (i+1); j < cnt; j++){
            if( userStrCmp(*(userArray + i), *(userArray + j)) == iOrderBy)
                swapTwoElementsOfArray(userArray + i, userArray + j);
        }
    }
}

void help(){
    printf("\no - вывести оригинальный текст\
           \nd - вывести отсортированный текст по убыванию\
           \na - вывести отсортированный текст по возрастанию\
           \nq - завершение работы программы\n");
}

void quit(char ** cUserText, char ** fileNamePath, char *** cArrayOfStrings)
{
    free(*cUserText);
    free(*cArrayOfStrings);
    free(*fileNamePath);
}

void printOriginalText(char * userText, int sizeOfArray)
{
    int nItems = 0;
    for(int i = 0; i < sizeOfArray; i++){
        nItems = nItems + printf("%s", (userText + nItems + i) );
        printf("\n");
    }
}

void createFileNamePath(char ** fileNamePath, char *** argv, int argc)
{
    *fileNamePath = (char *)calloc(SIZE_FILE_NAME_PATH, sizeof(char));
    if(NULL == *fileNamePath){
        printf("Error: unable to allocate memory!\n");
        abort();
    }
    if(argc == 1)
        strcat(*fileNamePath, DEFAULT_FILE_NAME);
    else if(argc == 2)
        strcat(*fileNamePath, *(*argv + 1));
}


void menu(char * cUserText, char ** cArrayOfStrings, char ** fileNamePath, int cnt)
{
    switchOperations userChoice;

    do{
        help();
        printf("\nВыберите действие: ");
        userChoice = getchar();
        while(getchar() != '\n');

        switch(userChoice){
            case ORDERBYDESCENDING:
                 sortOfArray(cArrayOfStrings, cUserText, ASC, cnt);
                 printArrayOfStrings(cArrayOfStrings, cnt);
                 break;
            case ORDERBYASCENDING:
                 sortOfArray(cArrayOfStrings, cUserText, DESC, cnt);
                 printArrayOfStrings(cArrayOfStrings, cnt);
                 break;
            case SHOWORIGINAL:
                 printOriginalText(cUserText, cnt);
                 break;
            case QUIT:
                 quit(&cUserText, fileNamePath, &cArrayOfStrings);
                 break;
            default:
                 printf("\nНеизвестное действие!!!\n");
        }
    }while(QUIT != userChoice);
}


