#include <iostream>

int main()
{
    //Task 1
    std::cout << "Task 1\n";
    std::cout << "Enter 3 numbers\n";

    float firstElement, step;
    int LastNumberElement;

    std::cout << "First element of an arithmetic progression: ";
    std::cin >> firstElement;
    std::cout << "Step of arithmetic progression: ";
    std::cin >> step;
    std::cout << "Number of the last element of the arithmetic progression: ";
    std::cin >> LastNumberElement;

    int currentNumberElement = 0;
    while (currentNumberElement <= LastNumberElement)
    {
        float currentElement = firstElement + currentNumberElement * step;
        std::cout << currentElement << " ";
        currentNumberElement++;
    }

    std::cout << std::endl << std::endl;

    //Task 2
    std::cout << "Task 2\n";
    std::cout << "Enter the number of the Fibonacci element: ";
    int FibonacciElementNumber;
    std::cin >> FibonacciElementNumber;

    int previousElementFibonacci = 0, currentElementFibonacci = 1, nElementFibonacci = 0;

    if (FibonacciElementNumber == 1)
    {
        nElementFibonacci = 1;
    }

    for (int i = 2; i <= FibonacciElementNumber; i++)
    {
        nElementFibonacci = previousElementFibonacci + currentElementFibonacci;
        previousElementFibonacci = currentElementFibonacci;
        currentElementFibonacci = nElementFibonacci;
    }

    std::cout << FibonacciElementNumber << " element of the Fibonacci sequence: " << nElementFibonacci;

    std::cout << std::endl << std::endl;

    //Task 3
    std::cout << "Task 3\n";
    std::cout << "Enter a single number: ";
    unsigned int number;
    std::cin >> number;

    int factorial = 1;

    for (int i = 0; i < number; i++)
    {
        factorial = factorial * (number - i);
    }
    std::cout << "The factorial of " << number << " is equal to: " << factorial;

    std::cout << std::endl << std::endl;

    //Task 4
    std::cout << "Task 4\n";

    std::cout << "Enter the number of rows and columns for the shape: ";
    unsigned int rows, columns;
    std::cin >> rows >> columns;

    //Task a
    for (int i = 0; i < rows; i++)
    {
        for (int y = columns; y > i; y--)
        {
            std::cout << "*";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    //Task b
    for (int i = 0; i < rows; i++)
    {
        for (int y = 0; y <= i; y++)
        {
            std::cout << "*";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    //Task c
    for (int i = 0; i < rows; i++)
    {
        for (int y = 0; y < columns; y++)
        {
            std::cout << "*";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    //Task d
    for (int i = 0; i < rows; i++)
    {
        int x = 0;
        while (x < i)
        {
            std::cout << " ";
            x++;
        }

        for (int y = 0; y < columns; y++)
        {
            std::cout << "*";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    //Task e
    for (int i = 0; i < rows; i++)
    {
        for (int y = 0; y <= i; y++)
        {
            if ((i + y) % 2 == 0)
            {
                std::cout << "1";
            }
            else
            {
                std::cout << "0";
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    //Task 5
    int sum = 0;
    while (true) 
    {
        std::cout << "Enter a symbol: ";
        char symbol;
        std::cin >> symbol;

        if (std::islower(symbol))
        {
            symbol = std::toupper(symbol);
            std::cout << "Upper case: " << symbol << std::endl;
        }
        else if (std::isdigit(symbol))
        {
            int digitSymbol = int(symbol) - int('0');
            sum = digitSymbol + sum;
            std::cout << "Sum: " << sum << std::endl;
        }
        else if (symbol == '.')
        {
            std::cout << "END" << std::endl;
            break;
        }
        else
        {
            std::cout << "The character is not processed by the program" << std::endl;
        }
    }
}