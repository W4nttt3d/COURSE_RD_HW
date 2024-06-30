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

void upNumbersRecursion(int count)
{
    if (count == 0)
    {
        return;
    }
    upNumbersRecursion(count - 1);
    std::cout << count << " ";
}

int factorialRecursion(int n)
{
    if (n == 1)
    {
        return 1;
    }

    return n * factorialRecursion(n - 1);
}
