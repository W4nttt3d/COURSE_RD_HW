#include "recursive_functions.h"
#include <iostream>

void downNumbersRecursion(int count)
{
    if (count == 0)
    {
        return;
    }
    std::cout << count << " ";
    downNumbersRecursion(count - 1);
}

void upNumbersRecursion(int count, int currentNumber)
{
    if (count < currentNumber)
    {
        return;
    }
    std::cout << currentNumber << " ";
    upNumbersRecursion(count, currentNumber + 1);
}

int factorialRecursion(int n)
{
    if (n == 1)
    {
        return 1;
    }

    return n * factorialRecursion(n - 1);
}
