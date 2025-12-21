#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <assert.h>
#include "userfilelib.h"

int main( int argc, char **argv)
{
    system("chcp 1251 > nul");
    printf("Передно %d параметров\n", argc);
    printf("%s \n", *(argv+0) );
    printf("%s \n", *(argv+1) );
    _off64_t lFileLong = 0;
    int Increment = 1, i = 0;
    _off64_t Razmer = 0;
    char * cUserArrayOnegin = NULL;
    char cLastSymbol = 0;
    size_t iCount = 0;
    FILE * fPtrOnegin = openTxtFile(*(argv+1), "r+b");
    //FILE * fPtrOnegin = fopen64(*(argv+1), "r+b");

    printf("fPtrOnegin = %p\n", fPtrOnegin);
    FILE * fPtrResult = fopen64("result.txt", "r+b");
    if(fPtrResult == NULL)
        fPtrResult = fopen64("result.txt", "w+b");
    fseeko64(fPtrResult, 0, SEEK_END);
    Razmer = ftello64(fPtrResult);
    rewind(fPtrResult);
    if(0 == Razmer){
        printf("11111 - %zu\n", sizeof(_off64_t));
        fwrite(&Increment, sizeof(int), 1, fPtrResult);
    } else{
        fread(&Increment, sizeof(int), 1, fPtrResult);
        printf("файл на = %ld байте\n", ftello64(fPtrResult));
        //rewind(fPtrResult);
        fseeko64(fPtrResult, -sizeof(Increment), SEEK_CUR);
        Increment++;
        fwrite(&Increment, sizeof(int), 1, fPtrResult);
        printf("2222 - %zu\n", sizeof(_off64_t));
    }
    Increment = -1;
    rewind(fPtrResult);
    fread(&Increment, sizeof(int), 1, fPtrResult);

    printf("Программа была запущена %d раз\n", Increment);

    fclose(fPtrResult);



    fseeko64(fPtrOnegin, 0, SEEK_END);
    lFileLong = ftello64(fPtrOnegin);
    cUserArrayOnegin = (char *)calloc(lFileLong+1, sizeof(char));
    //cUserArrayOnegin = (char *)malloc(lFileLong* sizeof(char));
    rewind(fPtrOnegin);
    fread(cUserArrayOnegin, sizeof(char), lFileLong, fPtrOnegin);
    assert(lFileLong == strlen(cUserArrayOnegin));

    printf("Длина файла = %ld байт\n", lFileLong);
    //printf("%s", cUserArrayOnegin);

    fseeko64(fPtrOnegin, 0, SEEK_END);
    printf("здесь1 - %lld\n",ftello64(fPtrOnegin));
    fseeko64(fPtrOnegin, -sizeof(char), SEEK_CUR);
    printf("здесь2 - %lld\n",ftello64(fPtrOnegin));
    iCount = fread(&cLastSymbol, sizeof(char),1, fPtrOnegin);
    printf("Последний символ в файле \"%c\" - %u\n", cLastSymbol, iCount);
    printf("здесь3 - %lld\n",ftello64(fPtrOnegin));
    cLastSymbol = 0;
    i = fseeko64(fPtrOnegin, 0, SEEK_END);
    iCount = fread(&cLastSymbol, sizeof(char),1, fPtrOnegin);
    printf("Последний символ в файле \"%c\" - %lld  - %d\n", cLastSymbol, ftello64(fPtrOnegin), i);
    i = fseeko64(fPtrOnegin, -100, SEEK_CUR);
    fread(&cLastSymbol, sizeof(char),1, fPtrOnegin);
    printf(" %d - %lld - %c\n", i, ftello64(fPtrOnegin), cLastSymbol);

    i = fseeko64(fPtrOnegin, -1, SEEK_END);
    fread(&cLastSymbol, sizeof(char),1 , fPtrOnegin);
    printf(" %d - %lld - %c\n", i, ftello64(fPtrOnegin), cLastSymbol);


    fclose(fPtrOnegin);

    //system("pause");

    return 0;
}
