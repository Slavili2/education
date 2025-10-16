/* Реализация пользовательского стэка:
    push - добавить элемент в верх стэка (в top)
    pop - удалить элемент из верха стэка (из top'а)
https://en.cppreference.com/w/cpp/container/stack.html
*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include "murmurhash.h"



void pop();
void push(int userValue);
void select();
void menu();
void quite();

struct userStack{ // пользовательских стэк
    int * data;  // массив данных
    int stackCapacity; // максимальная вместимость стека
    int stackSize; // заполненность stackSize <= stackCapcity
    void (*pop)();
    void (*push)();
    void (*select)();
};

struct userStack uStack;

int main()
{
    uStack.pop = pop;
    uStack.push = push;
    uStack.select = select;

    menu();

    return 0;
}

void menu()
{
    int userChoice, userValue = 0;
    printf("Enter the capacity: ");
    fflush(stdin);
    scanf(" %d", &uStack.stackCapacity);
    uStack.data = (int *)calloc(uStack.stackCapacity, sizeof(int));
    uStack.stackSize = uStack.stackCapacity - 1;

    while(1){
        printf("\nA - add value into stack\
               \nD - delete top element\
               \nS - display on screen\
               \nQ - quit program\n");
        printf("\nYour choice: ");
        userChoice = getch();
        userChoice = toupper(userChoice);
        //putch(userChoice);

        switch(userChoice){
            case 'A': putch(userChoice);
                      printf("\nEnter value: ");
                      fflush(stdin);
                      scanf(" %d", &userValue);
                      uStack.push(userValue);
                      break;
            case 'D': putch(userChoice);
                      uStack.pop();
                      break;
            case 'S': putch(userChoice);
                      putch('\n');
                      uStack.select();
                      break;
            case 'Q': putch(userChoice);
                      quite();
                      break;
        }
    }
}

void pop()
{
    //printf("\nPreved Medved!\n");
    if(uStack.stackSize+1>=0 && uStack.stackSize+1 < uStack.stackCapacity){
        *(uStack.data + uStack.stackSize+1) = 0; // Это действие под сомнением
        uStack.stackSize++;
    }else
        printf("\nStack is empty.\n");
}
void push(int userValue)
{
    if(uStack.stackSize >= 0){
        *(uStack.data + uStack.stackSize) = userValue;
        uStack.stackSize--;
    }
    else
        printf("\nStack overflow\n");
}
void select()
{
    for(int i = uStack.stackSize + 1; i < uStack.stackCapacity ; i++)
        printf("%d -> %d\n", i, *(uStack.data + i));
}
void quite()
{
    free(uStack.data);
    exit(EXIT_SUCCESS);
}
