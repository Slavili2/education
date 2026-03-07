#pragma once
#include "userStructs.h"

typedef struct {
    int * arr;
    int sizeArray;
    int currentValue;
} userStruct;

typedef enum {
    FILLARRAY = 'A',
    SHOWLCM = 'N',
    QUIT = 'Q'

} switchOperations;
