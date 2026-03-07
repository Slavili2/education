#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <assert.h>
#include "userStructs.h"
#include "userMath.h"

void crateUserStruct(userStruct * uSt)
{
    if(0 != uSt->currentValue)
        free(uSt->arr);
    uSt->currentValue = 0;
    uSt->sizeArray = 2;
    uSt->arr = (int *)calloc(uSt->sizeArray, sizeof(int));
    if(NULL == uSt->arr){
        printf("Error allocation memory\n");
        abort();
    }
}

void quit(userStruct * ust)
{
    free(ust->arr);
}

void reallocSizeArray(userStruct * ust)
{
    ust->sizeArray *= 2;
    ust->arr = (int *)realloc( (void *)ust->arr, ust->sizeArray * sizeof(int) );
    if(NULL == ust->arr){
        printf("Error reallocate memory\n");
        abort();
    }
    printf("Realloc memory %d\n", ust->sizeArray);
}

void fillArray(userStruct * ust)
{
    crateUserStruct(ust);

    printf("Enter numbers separated by spaces, then Enter: ");

    while( scanf("%d", ust->arr + ust->currentValue ) != 0 && getchar() != '\n' ){
        if( ust->currentValue + 1 == ust->sizeArray ){
            reallocSizeArray(ust);
        }
        ust->currentValue++;
    }
}

int calculateLcm(userStruct * ust)
{
    int result;
    if(0 == ust->currentValue)
        return -1;

    result = ust->arr[0];

    for(int i = 1; i <= ust->currentValue; i++){
        result = lcm(result, ust->arr[i]);
    }

    return result;
}

void showLcm(userStruct * ust)
{
    int result = calculateLcm(ust);
    if(-1 != result){
        printf("LCM(");
        for(int i = 0; i <= ust->currentValue; i++){
            if(ust->currentValue == i)
                printf("%d", ust->arr[i]);
            else
                printf("%d;", ust->arr[i]);
        }
        printf(") = %d\n", result);
    }
}


void menu(userStruct * ust)
{
    switchOperations userChoice;

    do{
        printf("\nA - add data\nN - show LCM\nQ - quit\n");
        printf("\npick and choose one action: ");
        userChoice = toupper(getchar());
        while(getchar() != '\n');
        switch(userChoice){
          case FILLARRAY:
               fillArray(ust);
          case SHOWLCM:
               showLcm(ust);
               break;
          case QUIT:
               quit(ust);
               break;
            default: printf("\nUndefined action\n");
        }

    }while(QUIT != userChoice);
}
