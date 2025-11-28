#pragma once

typedef struct userStack{ // user stack
    int * data;  // aray of data
    size_t stackCapacity; // maximum stack capacity
    size_t stackSize; // current stack fullness (stackSize <= stackCapcity)
    uint32_t hash;
    void (*pop)(struct userStack * , const uint8_t* key, uint32_t seed);
    void (*push)(struct userStack * , int userValue, const uint8_t* key, uint32_t seed);
} userStack;

typedef enum {
    ADD = 'a',
    DELETE = 'd',
    SHOW = 's',
    QUIT = 'q',
    CORRUPT = 'c'
} switchOperations;

