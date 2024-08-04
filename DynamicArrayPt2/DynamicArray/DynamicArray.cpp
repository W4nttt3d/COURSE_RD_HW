#include "DynamicTArray.h"
#include <iostream>

int main()
{
    // Testing reserve() and getCapacity()
    DynamicArray<int> arr1;
    arr1.reserve(10);
    std::cout << "(testing reserve() method)\t\t arr1 capacity: " << arr1.getCapacity() << std::endl;

    arr1.reserve(5); // Should not change capacity as it's less than current capacity
    std::cout << "(testing reserve() method)\t\t arr1 capacity after reserving less space: " << arr1.getCapacity() << std::endl;

    // Testing setSize()
    arr1.setSize(8);
    std::cout << "(testing setSize() method)\t\t arr1 size: " << arr1.getSize() << std::endl;
    std::cout << "(testing setSize() method)\t\t arr1 capacity: " << arr1.getCapacity() << std::endl;

    // Testing shrinkToFit()
    arr1.shrinkToFit();
    std::cout << "(testing shrinkToFit() method)\t arr1 capacity after shrinkToFit: " << arr1.getCapacity() << std::endl;

    // Testing pop_back()
    arr1.pop_back();
    std::cout << "(testing pop_back() method)\t\t arr1 size after pop_back: " << arr1.getSize() << std::endl;

    // Adding some elements to test pop_back() and back()
    arr1.push_back(1);
    arr1.push_back(2);
    arr1.push_back(3);
    std::cout << "(testing back() method)\t\t\t arr1 last element: " << arr1.back() << std::endl;

    arr1.pop_back();
    std::cout << "(testing pop_back() method)\t\t arr1 size after pop_back: " << arr1.getSize() << std::endl;

    // Testing equality operator (==) and inequality operator (!=)
    DynamicArray<int> arr2;
    arr2.setSize(2);
    arr2[0] = 1;
    arr2[1] = 2;

    std::cout << "(testing equality operator (==))\t" << (arr1 == arr2 ? "arr1 is equal to arr2" : "arr1 is not equal to arr2") << std::endl;

    DynamicArray<char> arr3;
    arr3.setSize(2);
    arr3[0] = '3';
    arr3[1] = '2';
    std::cout << arr3[0] << " " << arr3[1];
}
