#include <iostream>
#include <numbers>
#include "cyclic_functions.h"
#include "recursive_functions.h"

// Task 1 function remains in the main file
void countingNumbers(int number)
{
    int positiveNumber = 0, negativeNumber = 0, zeroes = 0;
    int num;

    std::cout << "Enter " << number << " numbers ";

    for (int i = 0; i < number; i++)
    {
        std::cin >> num;

        if (num > 0)
        {
            positiveNumber += 1;
        }
        else if (num < 0)
        {
            negativeNumber += 1;
        }
        else
        {
            zeroes += 1;
        }
    }

    std::cout << "Positive numbers: " << positiveNumber << std::endl <<
        "Negative numbers: " << negativeNumber << std::endl <<
        "Zeroes: " << zeroes << std::endl;
}

// Task 4 functions remain in the main file
float getArea(float radius)
{
    return std::numbers::pi * radius * radius;
}

float getCircumference(float radius)
{
    return 2 * std::numbers::pi * radius;
}

int main()
{
    // Task 1
    std::cout << "Enter the number of numbers\n";
    int number;
    std::cin >> number;
    countingNumbers(number);

    std::cout << std::endl;

    // Task 2
    int factorialNumber;
    std::cout << "Enter number: ";
    std::cin >> factorialNumber;

    std::cout << "Loop factorial: " << factorialLoop(factorialNumber) << std::endl;
    std::cout << "Recursion factorial: " << factorialRecursion(factorialNumber) << std::endl;

    std::cout << std::endl;

    // Task 3
    int count;
    std::cout << "Enter a natural number: ";
    std::cin >> count;

    downNumbersLoop(count);
    upNumbersLoop(count);

    std::cout << "downNumbersRecursion: ";
    downNumbersRecursion(count);
    std::cout << std::endl;

    std::cout << "upNumbersRecursion: ";
    upNumbersRecursion(count);
    std::cout << std::endl << std::endl;

    // Task 4
    std::cout << "Enter the radius of the circle: ";
    int radius;
    std::cin >> radius;

    while (radius <= 0)
    {
        std::cout << "The radius of the circle cannot be equal to 0 or one" << std::endl <<
            "Try again: ";
        std::cin >> radius;
    }
    std::cout << "Area: " << getArea(radius) << std::endl;
    std::cout << "Circumference: " << getCircumference(radius) << std::endl;

    return 0;
}
