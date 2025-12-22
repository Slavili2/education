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

void createOfText(FILE * fPtrTempFile, char ** cPtrTempArray)
{
    _off64_t sizeOfArray = 0;
    fseeko64(fPtrTempFile, 0, SEEK_END);
    sizeOfArray = ftello64(fPtrTempFile);
    *cPtrTempArray = (char *)calloc(sizeOfArray + 1, sizeof(char));
    if(NULL == *cPtrTempArray){
        printf("Error: unable to allocate memory!\n");
        abort();
    }
    rewind(fPtrTempFile);
    fread(*cPtrTempArray, sizeof(char), sizeOfArray, fPtrTempFile);
}


int countOfStrings(char * tempArray){
    long long int lastSymbolPosition = 0;
    int result = 0;

    size_t stSizeUserArray = strlen(tempArray);

    for(size_t i = 0; i < stSizeUserArray; i++){
        if('\n' == *(tempArray+i) ){
            result++;
            lastSymbolPosition = i;
        }
    }

    if( (stSizeUserArray - lastSymbolPosition) > 1)
        result++;

    return result;
}



void createArrayOfStrings(char *** tempArray, int sizeOfArray)
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
            for(long long int j = 0; *(*(cTempArray+i)+j) != '\n' && *(*(cTempArray+i)+j) != '\0'; j++){
                printf("%c",  *(*(cTempArray+i)+j) );
            }
            putchar('\n');
    }
}

void fillArrayOfStrings(char ** cArrayOfStrings, char * cUserText)
{
    int cArrayOfStringsCount = 0;
    for(long long int i = 0; *(cUserText+i) != '\0'; i++){
        if(0 == i){
            *cArrayOfStrings = cUserText;
            cArrayOfStringsCount++;
        }
        else if(*(cUserText+i) == '\n'){
            *(cArrayOfStrings+cArrayOfStringsCount) = (cUserText+i+1);
            cArrayOfStringsCount++;
        }
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

void sortOfArray(char ** userArray, char * userText)
{
    int countStrtings = countOfStrings(userText);

    for(int i = 0; i < (countStrtings - 1); i++){
        for(int j = (i+1); j < countStrtings; j++){
            if( userStrCmp(*(userArray + i), *(userArray + j)) == 1)
                swapTwoElementsOfArray(userArray + i, userArray + j);
        }
    }
}

void help(){
    printf("\no - вывести оригинальный текст\
           \ns - вывести отсортированный текст\
           \nq - завершение работы программы\n");
}

void quit(char * cUserText, char ** cArrayOfStrings)
{
    free(cUserText);
    free(cArrayOfStrings);
}

void printOriginalText(char * userText)
{
    printf("%s\n", userText);
}

void menu(char * cUserText, char ** cArrayOfStrings)
{
    switchOperations userChoice;

    do{
        help();
        printf("\nВыберите действие: ");
        userChoice = getchar();
        while(getchar() != '\n');

        switch(userChoice){
            case SHOWSORTED:
                 printArrayOfStrings(cArrayOfStrings, countOfStrings(cUserText));
                 break;
            case SHOWORIGINAL:
                 printOriginalText(cUserText);
                 break;
            case QUIT:
                 quit(cUserText, cArrayOfStrings);
                 break;
            default:
                 printf("\nНеизвестное действие!!!\n");
        }
    }while(QUIT != userChoice);
}


