#include "DynamicIntArray.h"

#include <iostream>

void printArray(DynamicIntArray array)
{
	for (size_t i = 0; i < array.getSize(); i++)
	{
		std::cout << array[i] << " ";
	}
}

int main()
{
	//testing default c-tor
	DynamicIntArray arr1;
	std::cout << "(testing default c-tor)\t\t arr1 size: " << arr1.getSize() << std::endl;

	//testing c-tor with size
	DynamicIntArray arr2(3);
	std::cout << "(testing c-tor with size)\t arr2 size: " << arr2.getSize() << std::endl;

	//testing setSize() method
	arr1.setSize(6);
	std::cout << "(testing setSize() method)\t arr1 size: " << arr1.getSize() << std::endl;

	//initializing arr2 elements
	arr2[0] = 5;
	arr2[1] = 8;
	arr2[2] = 3;

	//testing array elements
	std::cout << "(testing array elements)\t arr2 elements: ";
	printArray(arr2);
	std::cout << std::endl;

	//testing push_back method
	arr2.push_back(8);
	std::cout << "(testing push_back method)\t arr2 size: " << arr2.getSize() << std::endl;
	std::cout << "(testing push_back method)\t arr2 elements: ";
	printArray(arr2);
	std::cout << std::endl;

	//testing copy c-tor
	DynamicIntArray arr3(arr2);
	std::cout << "(testing copy c-tor)\t\t arr3 size: " << arr3.getSize() << std::endl;
	std::cout << "(testing copy c-tor)\t\t arr3 elements: ";
	printArray(arr3);
	std::cout << std::endl;

	//testing assignment operator
	DynamicIntArray arr4;
	arr4 = arr2;
	std::cout << "(testing assignment operator)\t arr4 size: " << arr4.getSize() << std::endl;
	std::cout << "(testing assignment operator)\t arr4 elements: ";
	printArray(arr4);
	std::cout << std::endl;

	//testing clear method
	arr4.clear();
	std::cout << "(testing clear method)\t\t arr4 size after clear: " << arr4.getSize() << std::endl;

	//testing exception handling
	try
	{
		std::cout << "(testing out-of-range access)\t arr2[10]: " << arr2[10] << std::endl; 
	}
	catch (const std::out_of_range& e)
	{
		std::cout << "Caught exception: " << e.what() << std::endl;
	}

	//Testing equality and inequality operator
	DynamicIntArray arr5(4);
	arr5[0] = 5;
	arr5[1] = 8;
	arr5[2] = 3;
	arr5[3] = 10;

	std::cout << "(testing equality operator)\t" << (arr2 == arr5 ? "arr2 is equal to arr5" : "arr2 is not equal to arr5") << std::endl;
	std::cout << "(testing inequality operator)\t" << (arr2 != arr5 ? "arr2 is not equal to arr5" : "arr2 is equal to arr5") << std::endl;
}