/* –еализаци€ пользовательского стэка:
    push - добавить элемент в верх стэка (в top)
    pop - удалить элемент из верха стэка (из top'а)
https://en.cppreference.com/w/cpp/container/stack.html
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h>
#include "murmurhash.h"
//#include "stacklib.h"

#define START_VALUE 2

struct userStack{ // пользовательских стэк
    int * data;  // массив данных
    size_t stackCapacity; // максимальна€ вместимость стека
    size_t stackSize; // заполненность stackSize < stackCapcity
    uint32_t hash;
    void (*pop)();
    void (*push)();
    uint32_t (*murmur3_32)(const uint8_t* key, size_t len, uint32_t seed);
};

void pop();
void push(int userValue);
void select();
void menu();
void quite();
uint32_t seedValue(uint32_t seed);
void corruptData(); // Ёмул€ци€ повреждени€ данных в пам€ти
int * allocateMemory(); // ѕервоначальное выделение пам€ти

struct userStack uStack;
const uint8_t key = 98; // дл€ murmurhash3
uint32_t seed = 0;

int main()
{
    uStack.pop = pop;
    uStack.push = push;
    uStack.murmur3_32 = murmur3_32;

    menu();

    return 0;
}

void menu()
{


    int userChoice, userValue = 0;
    printf("Enter the capacity: ");
    fflush(stdin);
    scanf(" %Iu", &uStack.stackCapacity);
    uStack.data = allocateMemory();
    uStack.stackSize = uStack.stackCapacity;
    uStack.hash = uStack.murmur3_32(&key, uStack.stackCapacity - uStack.stackSize,seedValue(seed));;

    while(1){
        printf("\nA - add value into stack\
               \nD - delete top element\
               \nS - display on screen\
               \nQ - quit program\
               \nC - corrupt data\n");
        printf("\nYour choice: ");
        fflush(stdin);
        userChoice = getchar();
        userChoice = toupper(userChoice);

        switch(userChoice){
            case 'A': printf("\nEnter value: ");
                      fflush(stdin);
                      scanf(" %d", &userValue);
                      uStack.push(userValue);
                      break;
            case 'D': uStack.pop();
                      break;
            case 'S': putchar('\n');
                      select();
                      break;
            case 'Q': quite();
                      break;
            case 'C': corruptData();
                      break;
            default: printf("Unknown choice\n");
        }
    }
}

void select()
{
    if(uStack.murmur3_32(&key, uStack.stackCapacity - uStack.stackSize,seedValue(seed)) != uStack.hash)
        exit(10);
    for(int i = uStack.stackSize; uStack.stackSize != uStack.stackCapacity && i < uStack.stackCapacity ; i++)
        printf("%Iu -> %d \n", uStack.stackCapacity - i, *(uStack.data + i));
    printf("uStack.stackCapacity = %Iu\nuStack.stackSize = %Iu\n", uStack.stackCapacity, uStack.stackSize);
}

void pop()
{
    if(uStack.murmur3_32(&key, uStack.stackCapacity - uStack.stackSize,seedValue(seed)) != uStack.hash)
        exit(10);
    if(uStack.stackSize >= 0 && uStack.stackSize != uStack.stackCapacity){
        *(uStack.data + uStack.stackSize) = 0; // Ёто действие под сомнением
        uStack.stackSize++;
        uStack.hash = uStack.murmur3_32(&key, uStack.stackCapacity - uStack.stackSize,seedValue(seed));
    }else
        printf("\nStack is empty.\n");
}

void push(int userValue)
{
    int tempStackSize = 0, i = 1;
    int tempValue;
    if(uStack.murmur3_32(&key, uStack.stackCapacity - uStack.stackSize,seedValue(seed)) != uStack.hash)
        exit(10);
    if(uStack.stackCapacity - uStack.stackSize < uStack.stackCapacity && uStack.stackSize >= 0){
        uStack.stackSize--;
        *(uStack.data + uStack.stackSize) = userValue;
        uStack.hash = uStack.murmur3_32(&key, uStack.stackCapacity - uStack.stackSize,seedValue(seed));
    } else if(uStack.stackCapacity - uStack.stackSize == uStack.stackCapacity){
        uStack.data = (int *)realloc( (void *)uStack.data, (uStack.stackCapacity * 2) * sizeof(int) );
        printf("tempStackSize  = %d, %Iu\n", tempStackSize, uStack.stackCapacity);
        for(tempStackSize = uStack.stackCapacity - 1;tempStackSize >= 0;tempStackSize--, i++){
            tempValue = *(uStack.data + tempStackSize);
            *(uStack.data + (uStack.stackCapacity * 2 - i)) = tempValue;
            printf("tempStackSize = %d, tempValue = %d, i = %d\n", tempStackSize, tempValue, i);
        }
        uStack.stackCapacity = uStack.stackCapacity * 2;
        uStack.stackSize = uStack.stackCapacity - i;
        *(uStack.data + uStack.stackSize) = userValue;
        uStack.hash = uStack.murmur3_32(&key, uStack.stackCapacity - uStack.stackSize,seedValue(seed));
        printf("tempStackSize  = %d, %Iu\n", tempStackSize, uStack.stackCapacity);
    }
}

void quite()
{
    free(uStack.data);
    exit(EXIT_SUCCESS);
}
uint32_t seedValue(uint32_t seed)
{
    for(size_t i = uStack.stackCapacity - uStack.stackSize; i > 0; i-- ){
        seed^= *(uStack.data+ (uStack.stackCapacity - i));
        seed = seed << 2;
    }
    return seed;
}

void corruptData()
{
    if(uStack.stackCapacity - uStack.stackSize > 0)
        *(uStack.data + uStack.stackSize) = -1;

}

int * allocateMemory()
{
    int * tempData = NULL;
    tempData = (int *)calloc(uStack.stackCapacity, sizeof(int));
    if(!tempData)
        exit(1);
    return tempData;
}
