#include <iostream>

//Task 1
void swap(int* numberA, int* numberB)
{
    int temp = *numberA;
    *numberA = *numberB;
    *numberB = temp;
}

void swap(int& numberA, int& numberB)
{
    int temp = numberA;
    numberA = numberB;
    numberB = temp;
}

void enterArray(double* arr, int sizeArray)
{
    for (int i = 0; i < sizeArray; i++)
    {
        std::cin >> arr[i];
    }
}

void enterArray(int* arr, int sizeArray)
{
    for (int i = 0; i < sizeArray; i++)
    {
        std::cin >> arr[i];
    }
}

//Task 2
bool calculateSum1(const double* arr, int arrSize, double& sum)
{
    sum = 0;

    for (int i = 0; i < arrSize; i++)
    {
        sum += arr[i];
    }

    return arrSize > 0;
}

//Task 3
bool find(const int* arr, int size, int elem)
{
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == elem)
        {
            std::cout << "Your item has been found";
            return true;
        }
    }

    std::cout << "Your item was not found";
    return false;
}

//Task 4
bool calculateSum2(double* arr, int arrSize, double& sum)
{
    sum = 0;

    for (double* pointer = arr; pointer < arr + arrSize; pointer++)
    {
        sum += *pointer;
    }

    return arrSize > 0;
}

int main()
{
    //Task 1
    int numberA;
    int numberB;

    std::cout << "Enter two numbers: ";
    std::cin >> numberA >> numberB;
    swap(numberA, numberB);
    std::cout << "Using the link: " << numberA << " " << numberB << std::endl;

    std::cout << "Enter two numbers: ";
    std::cin >> numberA >> numberB;
    swap(&numberA, &numberB);
    std::cout << "Using the pointer: " << numberA << " " << numberB << std::endl;

    //Task 2
    int sizeArray;
    double sum;

    std::cout << "Enter size array: ";
    std::cin >> sizeArray;
    double* arrayForCalculate1 = new double[sizeArray];

    std::cout << "Enter the numbers in the array: ";
    enterArray(arrayForCalculate1, sizeArray);

    calculateSum1(arrayForCalculate1, sizeArray, sum);
    std::cout << "The sum of the numbers from the array: " << sum << std::endl;
    
    delete[] arrayForCalculate1;

    //Task 3
    int elem = 0;

    std::cout << "Enter size array: ";
    std::cin >> sizeArray;
    int* arrayForFind = new int[sizeArray];

    std::cout << "Enter the numbers in the array: ";
    enterArray(arrayForFind, sizeArray);

    std::cout << "Enter the item you are looking for: ";
    std::cin >> elem;
    find(arrayForFind, sizeArray, elem);

    delete[] arrayForFind;

    std::cout << std::endl;

    //Task 4
    std::cout << "Enter size array: ";
    std::cin >> sizeArray;
    double* arrayForCalculate2 = new double[sizeArray];

    std::cout << "Enter the numbers in the array: ";
    enterArray(arrayForCalculate2, sizeArray);

    calculateSum2(arrayForCalculate2, sizeArray, sum);
    std::cout << "The sum of the numbers from the array: " << sum << std::endl;
    delete[] arrayForCalculate2;
}

