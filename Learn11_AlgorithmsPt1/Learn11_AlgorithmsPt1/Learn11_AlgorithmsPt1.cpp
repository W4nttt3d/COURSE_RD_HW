#include <iostream>

const int ROWS = 4;
const int COLUMNS = 4;

void enterArray(int* arr, int sizeArray)
{
    for (int i = 0; i < sizeArray; i++)
    {
        std::cin >> arr[i];
    }
}

//Task 1
bool find(int arr_2d[ROWS][COLUMNS], int toFind)
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLUMNS; j++)
        {
            if (arr_2d[i][j] == toFind)
            {
                return true;
            }
        }
    }
    return false;
}

enum class SortingDirection
{
    ascending, 
    descending
};

bool isSorted(const int* arr, int sizeArray, SortingDirection direction)
{
    if (direction == SortingDirection::ascending)
    {
        for (int i = 1; i < sizeArray; i++)
        {
            if (arr[i-1] > arr[i])
            {
                return false;
            }
        }
    }
    else if (direction == SortingDirection::descending)
    {
        for (int i = 1; i < sizeArray; i++)
        {
            if (arr[i - 1] < arr[i])
            {
                return false;
            }
        }
    }

    return true;
}

//Method 1
void traversalArr_2dM1(int arr_2d[ROWS][COLUMNS])
{
    std::cout << std::endl;
    for (int j = COLUMNS - 1; j >= 0; j--)
    {
        for (int i = 0; i < ROWS; i++)
        {
            std::cout << arr_2d[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

//Method 2
void traversalArr_2dM2(int arr_2d[ROWS][COLUMNS])
{
    std::cout << std::endl;
    for (int i = ROWS - 1; i >= 0; i--)
    {
        if (i % 2 == 1)
        {
            for (int j = 0; j < COLUMNS; j++)
            {
                std::cout << arr_2d[i][j] << " ";
            }
        }
        else
        {
            for (int j = COLUMNS - 1; j >= 0; j--)
            {
                std::cout << arr_2d[i][j] << " ";
            }
        }
        std::cout << std::endl;
    }
}

const int SIZE = 8;


int main()
{
    //Task 1
    int arr_2d[ROWS][COLUMNS] = {
        12, 13, 14, 15, 
        16, 17, 18, 19,
        20, 21, 22, 23,
        24, 25, 26, 27
    };

    int toFind;
    std::cout << "Enter a number to search for: ";
    std::cin >> toFind;

    if (find(arr_2d, toFind))
    {
        std::cout << "Such a number is in the array";
    }
    else
    {
        std::cout << "There is no such number in the array";
    }

    std::cout << std::endl << std::endl;

    //Task 2
    int arr[SIZE] = {};

    std::cout << "Enter 8 numbers in the array: ";
    enterArray(arr, SIZE);

    if (isSorted(arr, SIZE, SortingDirection::ascending))
    {
        std::cout << "The array is sorted in ascending order";
    }
    else if (isSorted(arr, SIZE, SortingDirection::descending))
    {
        std::cout << "The array is sorted in descending order";
    }
    else
    {
        std::cout << "The array is not sorted";
    }

    //Task 3
    traversalArr_2dM1(arr_2d);
    std::cout << std::endl << std::endl;
    traversalArr_2dM2(arr_2d);
}
