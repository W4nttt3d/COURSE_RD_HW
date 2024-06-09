#include <iostream>
#include <algorithm>

void enterArray(int arr[], int size)
{
	for (int i = 0; i < size; i++)
	{
		std::cin >> arr[i];
	}
}

void printArray(int arr[], int size)
{
	for (int i = 0; i < size; i++)
	{
		std::cout << arr[i] << " ";
	}
}


//Task 1
void bubbleSort(int arr[], int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = size - 1; j >= 0; j--)
		{
			if (arr[j - 1] > arr[j])
			{
				std::swap(arr[j - 1], arr[j]);
			}
		}
	}
}

const unsigned arraySize = 10;
const unsigned ROWS = 4;
const unsigned COLUMNS = 5;

void printArray_2d(int arr_2d[ROWS][COLUMNS])
{
	for (int j = 0; j < ROWS; j++)
	{
		for (int i = 0; i < COLUMNS; i++)
		{
			std::cout << arr_2d[j][i] << " ";
		}
		std::cout << std::endl;
	}
}

enum class SortingDirection 
{ 
	ByRows, 
	byColumn 
};

//Task 2
void sort(int arr[ROWS][COLUMNS], SortingDirection direction)
{
	if (direction == SortingDirection::ByRows) 
	{
		for (int j = 0; j < ROWS; j++)
		{
			std::sort(arr[j], arr[j] + COLUMNS);
		}
	}
	else if (direction == SortingDirection::byColumn)  
	{
		for (int i = 0; i < COLUMNS; i++)  
		{
			int column[ROWS];
			for (int j = 0; j < ROWS; j++) 
			{
				column[j] = arr[j][i];
			}
			std::sort(column, column + ROWS);
			for (int j = 0; j < ROWS; j++)  
			{
				arr[j][i] = column[j];
			}
		}
	}
}

int main()
{
	//Task 1
	std::cout << "Enter the numbers into the array: ";
	int arr[arraySize] = {};
	enterArray(arr, arraySize);
	bubbleSort(arr, arraySize);
	printArray(arr, arraySize);

	std::cout << std::endl << std::endl;

	//Task 2 
	int arr_2d[ROWS][COLUMNS] =
	{
		14, 12, 32, 75, 87,
		74, 45, 78, 1, 7,
		5, 78, 55, 42, 45,
		17, 20, 4, 55, 9
	};

	std::cout << "Sorting by Rows" << std::endl;
	sort(arr_2d, SortingDirection::ByRows);
	printArray_2d(arr_2d);

	std::cout << std::endl;

	std::cout << "Sorting by Column" << std::endl;
	sort(arr_2d, SortingDirection::byColumn);
	printArray_2d(arr_2d);
}
