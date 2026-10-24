#include <stdio.h>

// p, ptr, pointer
void change(int * ptrA)
{
    *ptrA = 7;
    printf("value of 'ptrA' in change: \t%x\n", ptrA);
}

int main()
{
    int a;
    a = 5;
    printf("address of 'a' in main: \t%x\n", &a);

    // int * pointer;
    // pointer = &a;
    // printf("value of 'pointer': \t%x\n", pointer);

    // printf("value of 'a': %d\n", *pointer);
    // *pointer = 6;
    // printf("value of 'a': %d\n", a);
    
    change(&a);
    printf("value of 'a' in main: %d\n", a);
}

// int 4 байт
// 1 байт - 8 бит
// 1 бит - 2 значения (0/1)
// 2 бита - 4 (00, 01, 10, 11)
// 3 бита - 8 () - 2^3
// N = 2^a

// 2*2*2*2

// 1 байт - 256 значений 2^8
// 4 байта - 4*256 = 1024
// 4 байта - 32 бита - 2^32 - 4'000'000'000

// 2^8 - 2^32 - 

// 1024 байт - 1Кбайт
// 1024 Кбайт - 1Мбайт
// 1024 МБайт - 1Гбайт - 1024*1024 - 2^10 * 2^10 - 2^20 КБайт * 1024 - 2^20 * 2^10 - 2^30 байт

// 2^32 байт - 4 ГБайт

// 2^32 / 2^30 = 2^2 = 4

// x32 - int* 4 байт - 4 Гбайт
// x64 - int* 8 байт - 64 бита - 2^64 - 18 миллиардов ГБайт
