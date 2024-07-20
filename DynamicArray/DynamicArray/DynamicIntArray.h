#pragma once
#include <cstdlib>

class DynamicIntArray
{
public:
    //default c-tor
    DynamicIntArray();

    //c-tor with size
    DynamicIntArray(std::size_t size);

    //copy c-tor
    DynamicIntArray(const DynamicIntArray& other);

    //free allocated memory
    ~DynamicIntArray();

    DynamicIntArray& operator=(const DynamicIntArray& other);

    int& operator[](std::size_t index);

    //delete previous memory, create new inner array with updated size
    void setSize(std::size_t newSize);
    std::size_t getSize() const;

    //Clear internal memory, set size to 0
    void clear();

    bool operator==(const DynamicIntArray& other);
    bool operator!=(const DynamicIntArray& other);

    // Allocate new memory for new element
    // Copy old content to new inner array
    // insert element at the last index
    // update size
    void push_back(int element);

private:
    std::size_t size;
    int* array;
};
