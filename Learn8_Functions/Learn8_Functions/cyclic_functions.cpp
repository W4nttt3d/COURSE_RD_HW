#include "cyclic_functions.h"
#include <iostream>

void downNumbersLoop(int count)
{
    std::cout << "downNumbersLoop: ";
    for (int i = count; i >= 0; i--)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

void upNumbersLoop(int count)
{
    std::cout << "upNumbersLoop: ";
    for (int i = 0; i <= count; i++)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

int factorialLoop(int factorialNumber)
{
    int factorial = 1;

    for (int i = 2; i <= factorialNumber; i++)
    {
        factorial = factorial * i;
    }

    return factorial;
}
